#include "../Scene.h"
#include "Poker.h"
#include "PokerSections.h"
#include "../Code/ConstVal.h"

#include "Btn.h"
#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"
#include "PokerFontData.h"

#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"

#include <algorithm>
#include <deque>
#include <typeinfo>
#include <string>

Cmp_BetActionRecord::Action ActionDecision(Cmp_CPUBetLogic* betLogic) { //入れられたbetLogicによってraiseすべきかcallすべきか返す
	return betLogic->GetSelfRaise() ? Cmp_BetActionRecord::Action::raise : Cmp_BetActionRecord::Action::call;
}

bool BetIgnore(Cmp_BetActionRecord* record) { //キャラのアクション記録を渡す事でそのキャラのベットをスキップすべきか否か返す、trueでスキップ
	return record->GetActionRecord(Cmp_BetActionRecord::Action::allIn) || record->GetActionRecord(Cmp_BetActionRecord::Action::fold) || record->GetIsLose(); //allIn、Fold、敗北済みの場合ベットをスキップ
}

bool IsFold(Cmp_BetActionRecord& record) { //recordのキャラがアクションを終わらせた又はfoldで除外された等そのフェーズ中干渉できなくなっていればtrueを返す
	return record.GetActionRecord(Cmp_BetActionRecord::Action::fold) || record.GetIsLose() || record.GetIsAction(); //foldしている、敗北済み、アクション実行済みでtrueを返す
}

int FoldCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //ゲームから抜けたキャラ数を返す、centerにrecordへ使用する添え字を入れるとそのキャラを中心にチェックする
	int dropCount = 1; //このラウンドから抜けたキャラを記録する

	for (int i = 1; i < (int)Poker::Character::length; ++i) {
		Cmp_BetActionRecord current = *actionRecord[(center + i) % (int)Poker::Character::length]; //今回チェックするキャラ、そのアクセスショートカット
		dropCount += current.GetActionRecord(Cmp_BetActionRecord::Action::fold) || current.GetIsLose(); //飛ばし条件の何れかに掛かっていれば+1する
	}
	return dropCount;
}

int ActionEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //アクション終了済みキャラ数を返す、centerにrecordへ使用する添え字を入れるとそのキャラを中心に終了済みキャラ数をチェックする
	int endCount = 1; //アクションが終わったキャラ数を記録する
	for (endCount; endCount < (int)Poker::Character::length; ++endCount) {
		Cmp_BetActionRecord current = *actionRecord[(center + endCount) % (int)Poker::Character::length]; //今回チェックするキャラ、そのアクセスショートカット
		if (!(BetIgnore(&current) || current.GetIsAction())) { break; } //チェックキャラが終了条件の1つにも引っかからなかった場合中断
	}
	return endCount;
}

int RaiseCalculation(const std::deque<int>& split, int& runCount, int oldPay, int betRequest, int BB, int coin) {
	//ラウンド中での総支払額と分割レイズを何処まで使うかを返す、splitに分割レイズデータ、runCountにsplit読み出し開始位置を(編集される、次の読み出し開始位置まで移動される)、oldPayに前回までの支払額、betRequestに現在最大ベットを、BBに現在BBを、coinに所持金を入れる
	for (runCount; runCount < split.size();) { //支払額が現在ベットを上回るよう分割レイズを調整使用する処理
		int nowPayMent = split[runCount] * BB; //今回のsplit支払額
		if (coin - (oldPay + nowPayMent) < 0) { break; } //レイズで所持金を0未満にしてしまう場合今回分は使わず終了

		oldPay += nowPayMent; //今回分の支払額を加える
		++runCount; //runCountを進める、このタイミングで実行する事に意味がある
		if (oldPay > betRequest) { break; } //現在の分割数でベット最大を超えたら終了
	}
	return oldPay - betRequest; //レイズによる増加額を返す
}

void SequenceNextReset(const std::deque<Cmp_BetActionRecord*>& chara) { //次シーケンスへ移行する際実行するアクション記録リセット用関数
	for (auto itr : chara) {
		itr->SetActionRecord(Cmp_BetActionRecord::Action::check, false); //allInとLoose以外のアクションをリセット
		itr->SetActionRecord(Cmp_BetActionRecord::Action::call, false);
		itr->SetActionRecord(Cmp_BetActionRecord::Action::raise, false);
		itr->SetIsAction(false); //アクション未実行状態に戻す
	}
}

//未完成
void BBSBLevy(int BBpos, std::deque<Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord, Pot& pot, PK_Dealer& dealer) { //BB、SBポジションキャラからBB、SBを回収

	for (int i = 0; i < 2; ++i) { //BB、SBの2回徴収が必要なのでi<2
		int levy = (BBpos + i) % chara.size(); //今回のキャラチェック位置

		for (int j = 0; j < chara.size(); ++j) { //今回キャラを中心に対象キャラが敗北しているか調べる
			if (!IsFold(*actionRecord[levy + j])) { break; } //対象が未敗北の場合敗北チェック終了
			levy = (levy + 1) % chara.size(); //1つキャラを進める
		}
		int coin = chara[levy]->GetCoint(); //現在所持金
		int pay = dealer.GetBB() / (i + 1); //支払額
		chara[levy]->SetBBView((Chara::BBView)i); //支払額に応じてBB支払いかSB支払いか表示を設定する

		if (coin - pay <= 0) { //支払額が所持金を上回っていた場合
			actionRecord[i]->SetActionRecord(Cmp_BetActionRecord::Action::allIn, true); //強制allIn
			actionRecord[i]->SetIsAction(true); //アクション済みにされる
			pot.SetSidePot(coin, *chara[levy]); //持ってる分だけ支払ってもらう
			chara[levy]->SetCoin(0); //空にする

			//parent->dealer->SetActionChara((pos + 1) % parent->chara.size()); //位置更新に合わせて初めにアクションを開始するキャラを更新する



			continue; //このキャラに対する操作終わり
		}

		pot.SetMainPot(pay, *chara[levy]); //BB、SBの支払い
		chara[levy]->SetCoin(coin - pay); //支払い分所持金から差し引く

	}
}

void LoseSet(const std::deque<Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord) { //現在所持金に合わせて敗北設定を行う
	for (int i = 0; i < chara.size(); ++i) { actionRecord[i]->SetIsLose(chara[i]->GetCoint() <= 0); } //所持金が0以下になったら敗北に設定する
}

Poker::Section GameEndCheck(const std::deque<Chara*>& chara, const std::deque<Cmp_BetActionRecord*>& actionRecord) { //現在の敗北状況から向かうべきシーンを返す
	int loseCount = 0; //敗北キャラ数のカウント
	for (auto itr : actionRecord) { loseCount += itr->GetIsLose(); } //全キャラをチェックし敗北キャラ数をカウントしてゆく
	
	Poker::Section val = Poker::Section::ini; //返す値、ゲームを続行すべきならiniを返す
	if (loseCount >= (int)Poker::Character::length - 1) { val = Poker::Section::gameclear; } //1キャラ以外全てが敗北していた場合ゲームクリアを設定
	if (actionRecord[(int)Poker::Character::player]->GetIsLose()) { val = Poker::Section::gameover; } //プレイヤーが敗北していた場合ゲームオーバーを設定、クリアとオーバーではオーバーが優先

	return val;
}

void FullReset(std::deque<Chara*>& chara, Pot& pot, PK_Dealer& dealer, CardDealer& cardDealer) { //各種fullResetを実行しPreから新しいゲームを始められるようにする
	pot.Reset();
	dealer.FullReset();
	cardDealer.Reset();
	for (auto chara : chara) { chara->FullReset(); }
}





Poker::Ini::Ini(Poker& set) :parent(&set), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}

void Poker::Ini::Update() {
	parent->pot->Reset();
	parent->dealer->Reset();
	parent->cardDealer->Reset();
	for (auto chara : parent->chara) { chara->Reset(); }

	//未デバッグ
	//int pos = parent->dealer->ReadBtn()->GetBtnPos(); //敗北済みキャラを飛ばしてポジション決定から
	//for (int i = 0; i < parent->chara.size(); ++i) { //全キャラ調べ
	//	if (!IsFold(*actionRecord[pos])) { break; } //現在キャラが勝負可能ならループ抜け
	//	pos = (pos + 1) % parent->chara.size(); //1つキャラを進める
	//}
	//parent->dealer->EditBtn()->SetBtnPos(pos); //勝負可能な最短のキャラ位置に設定する
	//parent->dealer->SetActionChara((pos + 1) % parent->chara.size()); //位置更新に合わせて初めにアクションを開始するキャラを更新する

	parent->run = parent->list[(int)Poker::Section::pre];
}

Poker::Pre::Pre(Poker& set) :parent(&set), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}

void Poker::Pre::Update() {
	//未デバッグ
	//BBSBLevy(parent->dealer->ReadBtn()->GetBtnPos(), parent->chara, actionRecord, *parent->pot, *parent->dealer); //BB、SBの徴収


	for (auto itr : parent->chara) {

		//デバッグ用
		//for (auto card : *itr->EditCard()) { card->SetDrawMode(PK_Card::DrawMode::front); } //カードを可視化しておく 

		for (auto card : *itr->EditCard()) { card->SetCard(parent->cardDealer->DeckDraw()); } //山札から引いてきたカードを手札に設定
		if (typeid(*itr) == typeid(CPU)) { //このキャラがcpuだった場合
			(itr->EditCmp<Cmp_CPUBetLogic>())->RaiseVolDecision(*itr, true); //現在手札からレイズ数と分割、自主レイズするかどうかを決定する
		}
		else { //プレイヤーだった場合
			for (auto card : *itr->EditCard()) { card->SetDrawMode(PK_Card::DrawMode::front); } //カードを可視化しておく 
		}
	}
	//デバッグ用
	//parent->run = parent->list[(int)Poker::Section::change];

	parent->run = parent->list[(int)Poker::Section::main];
	((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(0); //ダウンキャストだが中身がハッキリしてるから許して……
}

void PlayerButtonAnalyze(const std::deque<Button*>& button, Button** action, Button** fold) { //buttonにplayerのボタンをいれるとactionにアクション用ボタン、foldにfold用ボタンを入れて返してくれる
	for (auto itr : button) {
		if ((itr->EditAlwaysCmp<Cmp_Image>())->GetAnimeLength() == 1) { *fold = itr; } //分割画像枚数が1ならfoldボタン
		else { *action = itr; } //違うならアクションボタン
	}
}

Poker::Main::Main(Poker& set) :parent(&set), phase(0), count(0), cpuWait(30), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), betLogic(std::deque<Cmp_CPUBetLogic*>(3)), playerButton(std::deque<Button*>()), actionButton(nullptr), foldButton(nullptr), playerGage(nullptr), playerGageBorder(nullptr), gageControl(nullptr), actionButtonImage(nullptr) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
	for (int i = 0; i < betLogic.size(); ++i) { betLogic[i] = parent->chara[i]->EditCmp<Cmp_CPUBetLogic>(); } //ベットロジック取り出し、chara配列の並び順がplayer最後になってるのでこれで動く、不安ならif文でplayerチェックしてもいい
	parent->chara[(int)Poker::Character::player]->EditCmpMulti<Button>(playerButton); //ボタン取り出し
	PlayerButtonAnalyze(playerButton, &actionButton, &foldButton); //ボタン配列をactionとfoldに分解格納
	actionButtonImage = actionButton->EditAlwaysCmp<Cmp_Image>(); //アクション用ボタンの画像を取り出す


	playerGage = parent->chara[(int)Poker::Character::player]->EditCmp<Gage>(); //ゲージ取り出し
	playerGageBorder = playerGage->EditCmp<Cmp_Gage_Border>(); //ゲージから各種機能を取り出す
	gageControl = playerGage->EditCmp<Cmp_Gage_MouseControl>();
}

void Poker::Main::Update() {
	++count;
	int access = parent->dealer->GetActionCharaSub(); //今回アクションを行うキャラへの添え字を記録するアクセスショートカット
	if (typeid(*parent->chara[access]) == typeid(CPU)) { //アクションキャラがcpuの場合

		if (count > cpuWait) { //指定待機時間を超えた場合実行アクションを決定する
			count = 0; //カウントリセット

			Cmp_BetActionRecord* record= actionRecord[access]; //このキャラのベット記録を取得
			Cmp_CPUBetLogic* betData = betLogic[access]; //cpuのベット判断機能の取得
			int raise = 0; //このキャラのレイズ可能回数
			for (auto itr : *betData->ReadRaiseSplit()) { raise += itr; } //分割されたレイズ可能回数を一つに纏める
			raise *= parent->dealer->GetBB(); //現在BBをレイズ可能回数に掛けてレイズ可能額に変更する

			int betRequest = parent->pot->GetCurrentMaxBet(); //現在最大ベット金額
			int oldPay = parent->pot->Inquiry(*parent->chara[access]); //このキャラの前回までの支払額
			int pay = betRequest - oldPay; //支払金額


			Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::fold; //実行すべきアクションを格納
			if (raise > betRequest) { action = ActionDecision(betData); } //現在最大ベットがレイズ可能額を超えていなければレイズ、コールする
			if (record->GetRaiseRunCount() > 0 && raise * 5 > parent->pot->GetCurrentMaxBet()) { action = ActionDecision(betData); } //1度レイズしたことがある場合レイズ可能額の5倍まではレイズを受ける
			if (parent->chara[access]->GetCoint() - betRequest <= 0) { action = Cmp_BetActionRecord::Action::allIn; } //コールすらできない所持金ならオールインになる

			if (action == Cmp_BetActionRecord::Action::raise) { //レイズの例外を弾く処理
				//if (raise <= parent->pot->GetCurrentMaxBet()) { action = Cmp_BetActionRecord::Action::call; } //レイズ扱いの場合でも要求額がレイズ可能回数を超えていた場合コールになる
				if (record->GetRaiseRunCount() >= betData->ReadRaiseSplit()->size()) { action = Cmp_BetActionRecord::Action::call; } //レイズ可能額全てを使い切っていた場合コールになる
			}
			
			if (action == Cmp_BetActionRecord::Action::raise) { //レイズ額出し処理
				int runCount = record->GetRaiseRunCount(); //今回のsplit読み出し開始位置を入れる
				int raiseAdd=RaiseCalculation(*betData->ReadRaiseSplit(), runCount, oldPay, betRequest, parent->dealer->GetBB(), parent->chara[access]->GetCoint()); //レイズによる増分を得る

				record->SetRaiseRunCount(runCount); //使用済み分割数を記録する
				if (raiseAdd <= 0) { action = Cmp_BetActionRecord::Action::call; } //レイズしても届かなかったり所持金の問題で指定分レイズできなかった場合callにする
				else { pay += raiseAdd; } //普通にレイズできれば増分を加える
			}
			if (action == Cmp_BetActionRecord::Action::call && pay == 0) { action = Cmp_BetActionRecord::Action::check; } //指定アクションがcallで金額支払いが不要の場合チェックになる


			record->SetActionRecord(action, true); //該当アクションを動作済みにする
			record->SetIsAction(true); //アクション済みに設定

			if (action == Cmp_BetActionRecord::Action::call || action == Cmp_BetActionRecord::Action::raise) { parent->pot->SetMainPot(pay, *parent->chara[access]); } //call、raiseの場合メインポットへ
			if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent->chara[access]); } //allInの場合サイドポットへ
			if (action != Cmp_BetActionRecord::Action::fold) { parent->chara[access]->SetCoin(parent->chara[access]->GetCoint() - pay); } //fold以外の場合所持金から支払額を減算する(checkの場合payは0なので弾く必要なし)

			if (action == Cmp_BetActionRecord::Action::raise) { //レイズしていた場合全員のアクション状況の見直しを行う
				for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allInをしていない場合未アクション状態に更新する
				playerGageBorder->SetBorder(((pay + oldPay) / parent->dealer->GetBB()) * parent->dealer->GetMaxBet()); //ゲージの最低値を更新
				record->SetIsAction(true); //レイズしたキャラのアクションは終了済みに設定する
			}

			
			
			int endCount = ActionEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
			if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
				SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
				if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //ファーストベットだった場合次実行するシーケンスはカード交換
				else { parent->run = parent->list[(int)Poker::Section::showdown]; } //セカンドベットならショーダウンへ移行する
			}
			if (action == Cmp_BetActionRecord::Action::fold) { //フォールドした場合ラウンド中断チェックを行う
				for (auto itr : *parent->chara[access]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //手札をfold表示へ変更
				
				if (FoldCount(actionRecord, access) >= (int)Poker::Character::length - 1) { //1キャラ以外全てキャラが抜けた場合ノーコンテストへ
					SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
					parent->run = parent->list[(int)Poker::Section::nocontest];
				}
			}
			parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す
		}
		return;
	}
	
	//プレイヤーの場合
	if (count == 1) { //プレイヤーに操作が移った瞬間ならば各種ボタンを有効化する
		for (auto itr : playerButton) { //ボタンのクリック検知開始と表示許可を出す 
			itr->SetRunUpdate(true);
			itr->SetRunDraw(true);
		}
		gageControl->SetRunUpdate(true); //ゲージの操作受け付けを開始する
	}
	Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::check; //今回のアクションを記録する、取り敢えずcheckを入れる
	Cmp_BetActionRecord* record = actionRecord[access]; //このキャラのベット記録を取得
	int pay = playerGage->GetVol() * parent->dealer->GetMaxBet() * parent->dealer->GetBB(); //現在ゲージに合わせた支払額
	int oldPay = parent->pot->Inquiry(*parent->chara[access]); //前回までの支払額

	if (pay == parent->pot->GetCurrentMaxBet() && pay - oldPay != 0) { action = Cmp_BetActionRecord::Action::call; } //支払額が現在最大ベットと同値だった場合アクションはcall、但し最終支払額が0になる場合check
	if (pay > parent->pot->GetCurrentMaxBet()) { action = Cmp_BetActionRecord::Action::raise; } //支払額が現在最大ベットを超えていた場合アクションはraise
	pay -= oldPay; //支払状況を加味した額に変更
	
	if (parent->chara[access]->GetCoint() - pay < 0) { action = Cmp_BetActionRecord::Action::allIn; } //支払額が所持金を超えていた場合AllIn

	actionButtonImage->SetAnimeSub((int)action); //ボタン画像を現在のアクションの物に変更
	for (auto itr : playerButton) { //ボタンをチェックし押されたボタンがあった場合ボタン押し共通機能を実行する
		if (itr->GetRunDrawClick()) {
			record->SetIsAction(true); //アクション済みに設定
			break; //どれか1つでも押されたたら再実行する必要はないのでループ抜け
		}
	}
	if (!record->GetIsAction()) { return; } //アクション済みにされてない場合ボタンを押されてないので以降の処理は飛ばす
	int endCount = ActionEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う

	if (actionButton->GetRunUpdateClick()) { //アクションボタンが押された場合の処理
		if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent->chara[access]); } //allInの場合サイドポットへ
		else if (action != Cmp_BetActionRecord::Action::check) { parent->pot->SetMainPot(pay, *parent->chara[access]); } //call,raiseだった場合メインポットへ
		parent->chara[access]->SetCoin(parent->chara[access]->GetCoint() - pay); //所持金から支払額を減算する

		if (action == Cmp_BetActionRecord::Action::raise) { //レイズしていた場合全員のアクション状況の見直しを行う
			playerGageBorder->SetBorder((pay + oldPay) / parent->dealer->GetBB() * parent->dealer->GetMaxBet()); //ゲージの最低値を更新
			for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allInをしていない場合未アクション状態に更新する
		}
		record->SetActionRecord(action, true); //該当アクションを動作済みにする
		record->SetIsAction(true); //レイズしたプレイヤーのアクションは終了済みに設定する
		endCount = ActionEndCount(actionRecord, access); //endcountの更新

		if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
			SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
			if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //ファーストベットだった場合次実行するシーケンスはカード交換
			else { parent->run = parent->list[(int)Poker::Section::showdown]; } //セカンドベットならショーダウンへ移行する
		}
	}

	if (foldButton->GetRunUpdateClick()) { //foldボタンが押された場合の処理
		for (auto itr : *parent->chara[access]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //手札をfold表示へ変更
		record->SetActionRecord(Cmp_BetActionRecord::Action::fold, true); //foldを動作済みにする

		if (FoldCount(actionRecord, access) >= (int)Poker::Character::length - 1) { //1キャラ以外全てキャラが抜けた場合ノーコンテストへ
			SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
			parent->run = parent->list[(int)Poker::Section::nocontest];
		}
	}

	for (auto itr : playerButton) { //ボタンのクリック検知終了と表示隠し、クリック情報の削除を行う
		itr->SetRunUpdate(false); //クリック検知終了
		itr->SetRunDraw(false); //非表示化
		itr->SetRunUpdateClick(false); //クリック状態のリセット
		itr->SetRunDrawClick(false);
	}

	parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す
	gageControl->SetRunUpdate(false); //ゲージの操作受け付けを終了する
	count = 0; //カウントリセット
}

Poker::Change::Change(Poker& set) :parent(&set), count(0), cpuWait(30), moveY(-48), border(CardDealer::CardPower::ten), isClick(std::deque<bool>()), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), actionButton(nullptr), cardButton(std::deque<Button*>()), cardPos(std::deque<Vector3*>()){
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
	
	std::deque<Button*> playerButton = std::deque<Button*>();
	Button* fold = nullptr; //ボタン分解の際のfoldボタン格納用、今回はfoldは使わないのでローカル変数
	parent->chara[(int)Poker::Character::player]->EditCmpMulti<Button>(playerButton); //ボタン取り出し
	PlayerButtonAnalyze(playerButton, &actionButton, &fold); //ボタン配列をactionとfoldに分解格納
	actionButtonImage = actionButton->EditAlwaysCmp<Cmp_Image>(); //アクション用ボタンの画像を取り出す

	for (auto itr : *parent->chara[(int)Poker::Character::player]->EditCard()) { 
		cardButton.push_back(itr->EditCmp<Button>()); //プレイヤーのカードから入力受付用ボタンを取得
		cardPos.push_back(&itr->EditTransform()->EditPos()); //各カードのTransformから位置情報を抜き出しておく
	}
	
	originalY = (*parent->chara[(int)Poker::Character::player]->EditCard())[0]->ReadTransform()->ReadPos().GetY(); //カードの元yを記憶しておく
}

void Poker::Change::Update() {
	++count;
	int access = parent->dealer->GetActionCharaSub(); //今回アクションを行うキャラへの添え字を記録するアクセスショートカット
	if (typeid(*parent->chara[access]) == typeid(CPU)) { //アクションキャラがcpuの場合
		if (count > cpuWait) {
			count = 0; //カウントリセット

			actionRecord[access]->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //アクション済みに設定する
			actionRecord[access]->SetIsAction(true);

			int endCount = ActionEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
			if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
				SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
				parent->run = parent->list[(int)Poker::Section::main]; //セカンドベットへ
				((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);
			}
			parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す

			std::deque<int> hand = parent->cardDealer->HandCheck(*parent->chara[access]); //手札評価を得る
			if (hand[0] <= (int)CardDealer::HandRank::OnePair * (int)CardDealer::CardPower::max) { //ワンペア以下だった場合リーチチェックを行う
				int change = parent->cardDealer->ReachCheck(*parent->chara[access]); //ストレート、フラッシュに不要なカード
				if (change != -1) { //changeに有効なカードが入った場合チェックを行う
					for (auto itr : *parent->chara[access]->EditCard()) {
						if (itr->GetCard() == change) { 
							itr->SetCard(parent->cardDealer->DeckDraw()); //不要カードを交換
							itr->SetMarking(true); //交換したカードをマーキング
							return;  //終わり
						}
					}
				}
			}

			std::deque<PK_Card*> changeList = std::deque<PK_Card*>(); //交換を行う手札の参照を入れてゆく
			int start = 1; //hand評価から交換カード取り出しを始める位置
			switch ((CardDealer::HandRank)(hand[0] / (int)CardDealer::CardPower::max)) {
			case CardDealer::HandRank::No: start = 1; break;
			case CardDealer::HandRank::OnePair: start = 2; break;
			case CardDealer::HandRank::TwoPair: start = 3; break;
			case CardDealer::HandRank::ThreeCard: start = 2; break;
			case CardDealer::HandRank::FourCard: start = 2; break;
			default: start = hand.size(); break; //上記ハンドでない場合交換はしない
			}

			//交換ロジックにミスを感じる
			//922qqの様な状況で9を交換しなかった
			for (int i = start; i < hand.size(); ++i) {
				if (i == start && hand[start] >= (int)border) { continue; } //開始位置(役以外で一番強いカード)が指定以上の強さを持ってた場合そのカードは取っておく
				for (auto itr : *parent->chara[access]->EditCard()) {
					if (itr->GetCard() % (int)CardDealer::CardPower::max == hand[i]) { changeList.push_back(itr); break; } //handと一致するカードを交換カードとしてリストに加える処理
				}
			}
			for (auto itr : changeList) { 
				itr->SetCard(parent->cardDealer->DeckDraw()); //交換指定のあるカードを交換
				itr->SetMarking(true); //交換したカードをマーキング
			}
		}
		return; //終わり
	}

	//以下プレイヤーの場合の処理
	if (count == 1) {
		actionButton->SetRunUpdate(true); //交換用ボタンの有効化
		actionButton->SetRunDraw(true);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(true); } //クリック検知を開始する
	}
	actionButtonImage->SetAnimeSub((int)Cmp_BetActionRecord::Action::change); //ボタン画像を交換に変更


	for (int i = 0; i < cardButton.size(); ++i) { //各カードのクリックチェック
		if (cardButton[i]->GetRunUpdateClick()) { //クリックされた場合
			int y = cardPos[i]->GetY() - moveY * (1 - 2 * (cardPos[i]->GetY() == originalY)); //カードが元位置と同じならmoveY分動かし、違っていればmoveY分戻す
			cardPos[i]->SetY(y); //カード位置変更
			cardButton[i]->EditTransform()->EditPos().SetY(y); //ボタンの位置もカード位置に合わせる

			cardButton[i]->SetRunUpdateClick(false); //クリックしてない扱いに戻す
		}
	}


	if (actionButton->GetRunUpdateClick()) { //アクションボタンが押された場合の処理
		for (int i = 0; i < cardButton.size(); ++i) { //各カードの交換チェック
			std::deque<PK_Card*>* card = parent->chara[access]->EditCard(); //カード配列を保持
			if (cardPos[i]->GetY() != originalY) { //カードが元位置にない場合交換するとして扱う
				(*card)[i]->SetCard(parent->cardDealer->DeckDraw()); //交換指定のあるカードを交換

				cardPos[i]->SetY(originalY); //位置を元に戻す処理
				cardButton[i]->EditTransform()->EditPos().SetY(originalY);
			}
		}

		actionRecord[access]->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //アクション済みに設定する
		actionRecord[access]->SetIsAction(true);

		int endCount = ActionEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
		if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
			SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
			parent->run = parent->list[(int)Poker::Section::main]; //セカンドベットへ
			((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);
		}
		parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す

		actionButton->SetRunUpdate(false); //ボタン無効化
		actionButton->SetRunDraw(false);
		actionButton->SetRunUpdateClick(false); //クリック状態のリセット
		actionButton->SetRunDrawClick(false);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(false); } //クリック検知を無効化

		count = 0; //カウントリセット
	}


}


std::string Hand2String(const std::deque<int>& hand) {
	switch ((CardDealer::HandRank)(hand[0] / (int)CardDealer::CardPower::max)) {
	case CardDealer::HandRank::No: return "ハイカード"; break;
	case CardDealer::HandRank::OnePair: return "ワンペア"; break;
	case CardDealer::HandRank::TwoPair: return "ツーペア"; break;
	case CardDealer::HandRank::ThreeCard: return "スリーカード"; break;
	case CardDealer::HandRank::Straight: return "ストレート!"; break;
	case CardDealer::HandRank::Flash: return "フラッシュ!"; break;
	case CardDealer::HandRank::FullHause: return "フルハウス!"; break;
	case CardDealer::HandRank::FourCard: return "フォーカード!!"; break;
	case CardDealer::HandRank::StraightFlash: return "ストレートフラッシュ!!"; break;
	case CardDealer::HandRank::RoyalStraightFlash: return "ロイヤルストレートフラッシュ!!!"; break;
	}

}

void FoldMemberPayOut(std::deque<Chara*>& chara, Pot& pot) { //foldキャラへPayOut
	Chara* maxChara = chara[0]; //最大支払額を持つキャラ
	int max = pot.Inquiry(*maxChara); //最大支払額
	for (int i = 1; i < chara.size(); ++i) {
		int current = pot.Inquiry(*chara[i]); //今回キャラの支払額
		if (max < current) { //今回キャラが最大ベット額を持っていればmax系の中身を交換
			max = current;
			maxChara = chara[i];
		}
	}
	max = pot.PayOut(*maxChara) / chara.size(); //最大支払額を持つキャラでポットから金額取り出し
	for (int i = 0; i < chara.size(); ++i) { chara[i]->SetCoin(chara[i]->GetCoint() + max); } //残りを分配
}


Poker::ShowDown::ShowDown(Poker& set) :parent(&set), count(0), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), hand(std::deque<std::deque<int>>(4, std::deque<int>(5))), handPos(std::deque<Vector3>(4)), handString(std::deque<std::string>(4)) {
	titlePos.SetXYZ(513, 189, 0); //ショーダウンである事を示すメッセージの位置設定

	//手札役を表示する為の位置設定
	handPos[0].SetXYZ(108, 382, 0);
	handPos[1].SetXYZ(776, 31, 0);
	handPos[2].SetXYZ(1039, 377, 0);
	handPos[3].SetXYZ(497, 400, 0);

	

	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}






void Poker::ShowDown::Update() {
	
	if (count == 60) {
		for (int i = 0; i < actionRecord.size(); ++i) { //各キャラをチェックし持ち札を公開する処理
			if (IsFold(*actionRecord[i])) { continue; } //ゲームから除外されていた場合以下処理は実行しない
			for (auto itr : *parent->chara[i]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::front); } //ここまでこれたキャラはカードを表側表示化
		}
	}

	if (count == 120) {
		for (int i = 0; i < parent->chara.size(); ++i) { //ハンド評価を行う
			hand[i] = CardDealer::HandCheck(*parent->chara[i]); //各キャラの手札評価を入れる
			handString[i] = Hand2String(hand[i]); //各キャラの完成役を文字列化した物を格納
		}
	}

	if (count == 180) {
		std::deque<Chara*> enableChara= std::deque<Chara*>(); //勝負を行うキャラ纏め
		std::deque<Chara*> foldChara = std::deque<Chara*>(); //フォールドしたキャラ纏め(敗北済みは除く)

		std::deque<std::deque<int>> enableHand = std::deque<std::deque<int>>(); //勝負を行うキャラのハンド評価纏め

		for (int i = 0; i < parent->chara.size(); ++i) { //キャラを勝負をするキャラ、foldキャラ、除外キャラに仕分ける
			if (actionRecord[i]->GetIsLose()) { continue; } //敗北済みの場合何もせず次キャラへ移行
			if (actionRecord[i]->GetActionRecord(Cmp_BetActionRecord::Action::fold)) { foldChara.push_back(parent->chara[i]); continue; } //foldしてる場合foldCaraへ格納し次キャラへ移行
			enableChara.push_back(parent->chara[i]); //現在キャラをenableCharaへ格納
			enableHand.push_back(hand[i]); //現在キャラのハンド評価格納
		}


		while (enableChara.size() > 0) { //enableChara全てに支払い終えるまで実行
			std::deque<int> max = std::deque<int>(1, 0); //今回支払を行うキャラの添え字集、取り敢えず要素数1で格納値は0

			for (int i = 1; i < enableChara.size(); ++i) { //一番強い役を持つキャラを決定する
				if (enableHand[max[0]][0] < enableHand[i][0]) { max = std::deque<int>(1, i); continue; } //今回の役の方が強い場合支払を行うキャラを今回の物に変更
				if (enableHand[max[0]][0] == enableHand[i][0]) { max.push_back(i); } //強さが同じなら今回キャラも支払い対象として配列に追加する
			}

			//デバッグ用
			//std::deque<int> max = std::deque<int>(); //今回支払を行うキャラの添え字集、取り敢えず要素数1で格納値は0
			//for (int i = 0; i < enableChara.size(); ++i) { max.push_back(i); }

			std::deque<int> copy = max; //maxを編集する為のコピー
			if (copy.size() == 1) { //要素が1つしかない場合
				enableChara[copy[0]]->SetCoin(enableChara[copy[0]]->GetCoint() + parent->pot->PayOut(*enableChara[copy[0]])); //受取金額総取り
				copy.erase(copy.begin()); //要素消し
			}
			else { std::sort(copy.begin(), copy.end(), [=](int a, int b) { return parent->pot->Inquiry(*enableChara[copy[a]]) < parent->pot->Inquiry(*enableChara[copy[b]]); }); } //支払額の昇順ソート

			while (copy.size() > 0) { //copyが空になるまで続ける
				std::deque<Chara*> same = std::deque<Chara*>(1, enableChara[copy[0]]); //支払額同一のキャラまとめ
				int pay = parent->pot->Inquiry(*same[0]); //今回の支払額
				for (int i = 1; i < copy.size(); ++i) { //今回支払額と同一のキャラ探し
					if (pay == parent->pot->Inquiry(*enableChara[copy[i]])) { same.push_back(enableChara[copy[i]]); } //同一なら配列へ格納
				}

				pay = parent->pot->PayOut(*same[0]) / same.size(); //支払いを実行、同一支払額キャラの数だけ金額総を等分
				for (int i = 0; i < same.size(); ++i) { //同一支払額の各キャラへ支払い
					same[i]->SetCoin(same[i]->GetCoint() + pay); //同一支払額のキャラへ配分
					for (int j = 0; j < copy.size(); ++j) { //支払ったキャラをcopyから除外する為のループ
						if (enableChara[copy[j]] == same[i]) { copy.erase(copy.cbegin() + j); break; } //今回支払ったキャラをcopyから除外
					}
				}

			}

			if (parent->pot->TotalAmount() <= 0) { ++count; return; } //支払いの結果ポット内金額が0になった場合その時点で終わり

			std::deque<Chara*> maxChara = std::deque<Chara*>(); //maxを基にenableCharaから取り出した物を保持する配列
			for (int i = 0; i < max.size(); ++i) { maxChara.push_back(enableChara[max[i]]); } //maxCharaへ対応Chara参照を格納


			for (int i = 0; i < maxChara.size(); ++i) { //同一支払額の各キャラへ支払い
				for (int j = 0; j < enableChara.size(); ++j) { //支払ったキャラをcopyから除外する為のループ
					if (enableChara[j] == maxChara[i]) { //enableChara内のどの要素を使ったか特定する
						enableChara.erase(enableChara.begin() + j); //対応要素をenableから除外
						enableHand.erase(enableHand.begin() + j); //handの方も消しておく
						break; 
					}
				}
			}
			FoldMemberPayOut(foldChara, *parent->pot); //余ったpotはfoldキャラへ分配
		}
		
	}

	if (count == 240) {
		parent->run = parent->list[(int)Poker::Section::ini]; //最初の状態に戻る
		count = -1; //カウントリセット
	}

	++count;
}

void Poker::ShowDown::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "ショーダウン!!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));

	if (count >= 120) {
		for (int i = 0; i < actionRecord.size(); ++i) { //勝負に挑んだキャラのハンドを表示する
			if (IsFold(*actionRecord[i])) { continue; } //ゲームから除外されていた場合以下処理は実行しない
			DrawStringToHandle(handPos[i].GetX(), handPos[i].GetY(), handString[i].c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal)); //ハンド表示
		}
	}


}


Poker::NoContest::NoContest(Poker& set) :parent(&set), count(0), payOutTime(60), clickStartTime(120), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	titlePos.SetXYZ(513, 189, 0); //ノーコンテストである事を示すメッセージの位置設定
	explainPos.SetXYZ(484, 312, 0); //ボタン説明配置位置

	nextButton.SetClick(new Cmp_Button_ClickCheck()); //クリックチェック用コンポーネント追加

	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}

void Poker::NoContest::Update() {
	nextButton.Update(); //ボタンUpdate実行

	if (count == payOutTime) {
		Chara* enableChara = nullptr; //降りなかったキャラが入る
		std::deque<Chara*> foldChara = std::deque<Chara*>(); //フォールドしたキャラ纏め(敗北済みは除く)

		for (int i = 0; i < parent->chara.size(); ++i) { //キャラを勝負をするキャラ、foldキャラ、除外キャラに仕分ける
			if (actionRecord[i]->GetIsLose()) { continue; } //敗北済みの場合何もせず次キャラへ移行
			if (actionRecord[i]->GetActionRecord(Cmp_BetActionRecord::Action::fold)) { foldChara.push_back(parent->chara[i]); continue; } //foldしてる場合foldCaraへ格納し次キャラへ移行
			enableChara = parent->chara[i]; //現在キャラをenableCharaへ格納
			break; //有効キャラは1人だけなのでここまでこれたら終わり
		}
		enableChara->SetCoin(enableChara->GetCoint() + parent->pot->PayOut(*enableChara)); //金額総取り
		if (parent->pot->TotalAmount() <= 0) { ++count; return; } //金額がなくなれば終わり
		FoldMemberPayOut(foldChara, *parent->pot); //余っていればfoldキャラへ分配

	}

	if (count == clickStartTime) { //クリック検知開始タイミングになったら

		//未デバッグ
		//LoseSet(parent->chara, actionRecord); //敗北状況の設定
		//Poker::Section next = GameEndCheck(parent->chara, actionRecord); //敗北状況から次向かうべきシーンを取得

		//if (next != Poker::Section::ini) { //ini(続行すべき)以外が入った場合
		//	parent->run = parent->list[(int)next]; //そのシーンに移行
		//	count = -1; //カウントリセット
		//	return; //終わり
		//}

		nextButton.SetRunClickMonitor(true); //クリック検知開始
	}

	if (nextButton.GetRunUpdateClick()) { //クリックされた場合
		parent->run = parent->list[(int)Poker::Section::ini]; //最初の状態に戻る

		nextButton.SetRunUpdate(false); //クリック状態を戻す
		nextButton.SetRunDraw(false); //念の為Drawも戻す
		nextButton.SetRunClickMonitor(false); //クリック検知の無効化
		count = -1; //カウントリセット
	}

	++count;
}

void Poker::NoContest::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "ノーコンテスト!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "画面をクリックで次ゲームへ", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}


Poker::GameOver::GameOver(Poker& set) :parent(&set), count(0), clickStartTime(60), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false) {
	titlePos.SetXYZ(513, 189, 0); //ノーコンテストである事を示すメッセージの位置設定
	explainPos.SetXYZ(432, 312, 0); //ボタン説明配置位置

	nextButton.SetClick(new Cmp_Button_ClickCheck()); //クリックチェック用コンポーネント追加
}

void Poker::GameOver::Update() {
	nextButton.Update(); //ボタンUpdate実行
	if (count == clickStartTime) { nextButton.SetRunClickMonitor(true); } //開始タイミングになったらクリック検知開始

	if (nextButton.GetRunUpdateClick()) { //クリックされた場合
		FullReset(parent->chara, *parent->pot, *parent->dealer, *parent->cardDealer); //新しいゲームの準備をする
		parent->run = parent->list[(int)Poker::Section::pre]; //最初の状態に戻る

		nextButton.SetRunUpdate(false); //クリック状態を戻す
		nextButton.SetRunDraw(false); //念の為Drawも戻す
		nextButton.SetRunClickMonitor(false); //クリック検知の無効化
		count = -1; //カウントリセット
	}

	++count;
}

void Poker::GameOver::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "ゲームオーバー!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "画面をクリックで新しく始める", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}
#include "../Scene.h"
#include "Poker.h"
#include "PokerSections.h"

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
#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"

#include <deque>
#include <typeinfo>

void Poker::Ini::Update() {
	parent->pot->Reset();
	parent->dealer->Reset();
	parent->cardDealer->Reset();
	for (auto chara : parent->chara) { chara->Reset(); }

	parent->run = parent->list[(int)Poker::Section::pre];
}

void Poker::Pre::Update() {
	for (auto itr : parent->chara) {
		for (auto card : *itr->EditCard()) { card->SetCard(parent->cardDealer->DeckDraw()); } //山札から引いてきたカードを手札に設定
		if (typeid(*itr) == typeid(CPU)) { //このキャラがcpuだった場合
			(itr->EditCmp<Cmp_CPUBetLogic>())->RaiseVolDecision(*itr, true); //現在手札からレイズ数と分割、自主レイズするかどうかを決定する
		}
		else { //プレイヤーだった場合
			for (auto card : *itr->EditCard()) { card->SetVisible(true); } //カードを可視化しておく 
		}
	}
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
	playerGagePayDraw = parent->chara[(int)Poker::Character::player]->EditCmp<Cmp_PlayerRaiseDraw>(); //


	playerGage = parent->chara[(int)Poker::Character::player]->EditCmp<Gage>(); //ゲージ取り出し
	playerGageBorder = playerGage->EditCmp<Cmp_Gage_Border>(); //ゲージから各種機能を取り出す
	gageControl = playerGage->EditCmp<Cmp_Gage_MouseControl>();
}

Cmp_BetActionRecord::Action ActionDecision(Cmp_CPUBetLogic* betLogic) { //入れられたbetLogicによってraiseすべきかcallすべきか返す
	return betLogic->GetSelfRaise() ? Cmp_BetActionRecord::Action::raise : Cmp_BetActionRecord::Action::call;
}

bool BetIgnore(Cmp_BetActionRecord* record) { //キャラのアクション記録を渡す事でそのキャラのベットをスキップすべきか否か返す、trueでスキップ
	return record->GetActionRecord(Cmp_BetActionRecord::Action::allIn) || record->GetActionRecord(Cmp_BetActionRecord::Action::fold) || record->GetIsLoose(); //allIn、Fold、敗北済みの場合ベットをスキップ
}

int FoldCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //ゲームから抜けたキャラ数を返す、centerにrecordへ使用する添え字を入れるとそのキャラを中心にチェックする
	int dropCount = 1; //このラウンドから抜けたキャラを記録する
	for (dropCount; dropCount < (int)Poker::Character::length; ++dropCount) {
		Cmp_BetActionRecord current = *actionRecord[(center + dropCount) % (int)Poker::Character::length]; //今回チェックするキャラ、そのアクセスショートカット
		if (!(current.GetActionRecord(Cmp_BetActionRecord::Action::fold) || current.GetIsLoose() || current.GetIsAction())) { break; } //チェックキャラが終了条件の1つにも引っかからなかった場合中断
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

void RaiseCalculation(const std::deque<int>& split, int& runCount, int& pay, int betRequest, int BB, int coin) {
	//ラウンド中での総支払額と分割レイズを何処まで使うかを返す、splitに分割レイズデータ、runCountにsplit読み出し開始位置を(編集される、次の読み出し開始位置まで移動される)、payに支払総額、betRequestに現在最大ベットを、BBに現在BBを、coinに所持金を入れる
	for (runCount; runCount < split.size();) { //支払額が現在ベットを上回るよう分割レイズを調整使用する処理
		int nowPayMent = split[runCount] * BB; //今回のsplit支払額
		if (coin - (pay + nowPayMent) < 0) { break; } //レイズで所持金を0未満にしてしまう場合今回分は使わず終了

		pay += nowPayMent; //今回分の支払額を加える
		++runCount; //runCountを進める、このタイミングで実行する事に意味がある
		if (pay > betRequest) { break; } //現在の分割数でベット最大を超えたら終了
	}
}

void SequenceNextReset(const std::deque<Cmp_BetActionRecord*>& chara) { //次シーケンスへ移行する際実行するアクション記録リセット用関数
	for (auto itr : chara) {
		itr->SetActionRecord(Cmp_BetActionRecord::Action::check, false); //allInとLoose以外のアクションをリセット
		itr->SetActionRecord(Cmp_BetActionRecord::Action::call, false);
		itr->SetActionRecord(Cmp_BetActionRecord::Action::raise, false);
		itr->SetIsAction(false); //アクション未実行状態に戻す
	}
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


			int betRequest = parent->dealer->GetCurrentMaxBet() * parent->dealer->GetBB(); //現在最大ベット金額
			int oldPay = parent->pot->Inquiry(*parent->chara[access]); //このキャラの前回までの支払額
			int pay = betRequest - oldPay; //支払金額


			Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::fold; //実行すべきアクションを格納
			if (raise > parent->dealer->GetCurrentMaxBet()) { action = ActionDecision(betData); } //現在最大ベットがレイズ可能額を超えていなければレイズ、コールする
			if (record->GetRaiseRunCount() > 0 && raise * 5 > parent->dealer->GetCurrentMaxBet()) { action = ActionDecision(betData); } //1度レイズしたことがある場合レイズ可能額の5倍まではレイズを受ける
			if (parent->chara[access]->GetCoint() - betRequest < 0) { action = Cmp_BetActionRecord::Action::allIn; } //コールすらできない所持金ならオールインになる

			if (action == Cmp_BetActionRecord::Action::raise) { //レイズの例外を弾く処理
				if (raise <= parent->dealer->GetCurrentMaxBet()) { action == Cmp_BetActionRecord::Action::call; } //レイズ扱いの場合でも要求額がレイズ可能回数を超えていた場合コールになる
				if (record->GetRaiseRunCount() >= betData->ReadRaiseSplit()->size()) { action == Cmp_BetActionRecord::Action::call; } //レイズ可能額全てを使い切っていた場合コールになる
			}
			
			if (action == Cmp_BetActionRecord::Action::raise) { //レイズ額出し処理
				int runCount = record->GetRaiseRunCount(); //今回のsplit読み出し開始位置を入れる
				RaiseCalculation(*betData->ReadRaiseSplit(), runCount, pay, betRequest, parent->dealer->GetBB(), parent->chara[access]->GetCoint());

				record->SetRaiseRunCount(runCount); //使用済み分割数を記録する
				if (pay <= betRequest) { //所持金の都合で現在ベットを超えたベットをできない場合callにする
					action == Cmp_BetActionRecord::Action::call; //callにする
					pay = betRequest - oldPay; //支払分をコール額に合わせる
				} else { pay -= oldPay; } //普通にレイズできれば前回分を取り除いてレイズ額とする
			}
			if (action == Cmp_BetActionRecord::Action::call && pay == 0) { action = Cmp_BetActionRecord::Action::check; } //指定アクションがcallで金額支払いが不要の場合チェックになる


			record->SetActionRecord(action, true); //該当アクションを動作済みにする
			record->SetIsAction(true); //アクション済みに設定
			if (action == Cmp_BetActionRecord::Action::call || action == Cmp_BetActionRecord::Action::raise) { parent->pot->SetMainPot(pay, *parent->chara[access]); } //call、raiseの場合メインポットへ
			if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent->chara[access]); } //allInの場合サイドポットへ
			parent->chara[access]->SetCoin(parent->chara[access]->GetCoint() - pay); //所持金から支払額を減算する

			if (action == Cmp_BetActionRecord::Action::raise) { //レイズしていた場合全員のアクション状況の見直しを行う
				for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allInをしていない場合未アクション状態に更新する
				playerGageBorder->SetBorder(((pay + oldPay) / parent->dealer->GetBB()) / parent->dealer->GetMaxBet()); //ゲージの最低値を更新
			}

			
			
			int endCount = ActionEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
			if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
				SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
				if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //ファーストベットだった場合次実行するシーケンスはカード交換
				else { parent->run = parent->list[(int)Poker::Section::showdown]; } //セカンドベットならショーダウンへ移行する
			}
			if (action == Cmp_BetActionRecord::Action::fold) { //フォールドした場合ラウンド中断チェックを行う
				if (FoldCount(actionRecord, access) >= (int)Poker::Character::length - 1) { //1キャラ以外全てキャラが抜けた場合ノーコンテストへ
					SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
					parent->run = parent->list[(int)Poker::Section::nocontest];
				}
			}
			parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す
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
	int pay = playerGage->GetVol() * parent->dealer->GetBB() - parent->pot->Inquiry(*parent->chara[access]); //現在ゲージと支払状況に基づいた支払額

	if (pay == parent->dealer->GetBB()) { action = Cmp_BetActionRecord::Action::call; } //支払額がBBと同値だった場合アクションはcall
	if (pay > parent->dealer->GetBB()) { action = Cmp_BetActionRecord::Action::raise; } //支払額がBBを超えていた場合アクションはraise
	if (parent->chara[access]->GetCoint() - pay < 0) { action = Cmp_BetActionRecord::Action::allIn; } //支払額が所持金を超えていた場合AllIn


	for (auto itr : playerButton) { //ボタンをチェックし押されたボタンがあった場合ボタン押し共通機能を実行する
		if (itr->GetRunDrawClick()) {
			record->SetActionRecord(action, true); //該当アクションを動作済みにする
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

		if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
			SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
			if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //ファーストベットだった場合次実行するシーケンスはカード交換
			else { parent->run = parent->list[(int)Poker::Section::showdown]; } //セカンドベットならショーダウンへ移行する
		}
	}

	if (foldButton->GetRunUpdateClick()) { //foldボタンが押された場合の処理
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
	gageControl->SetRunUpdate(false); //ゲージの操作受け付けを終了する
	parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す
	count = 0; //カウントリセット
}

Poker::Change::Change(Poker& set) :parent(&set), count(0), cpuWait(30), moveY(-48), border(CardDealer::CardPower::ten), isClick(std::deque<bool>()), actionRecord(std::deque<Cmp_BetActionRecord*>()), actionButton(nullptr), cardButton(std::deque<Button*>()) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
	
	std::deque<Button*> playerButton = std::deque<Button*>();
	Button* fold = nullptr; //ボタン分解の際のfoldボタン格納用、今回はfoldは使わないのでローカル変数
	parent->chara[(int)Poker::Character::player]->EditCmpMulti<Button>(playerButton); //ボタン取り出し
	PlayerButtonAnalyze(playerButton, &actionButton, &fold); //ボタン配列をactionとfoldに分解格納

	for (auto itr : *parent->chara[(int)Poker::Character::player]->EditCard()) { cardButton.push_back(itr->EditCmp<Button>()); } //プレイヤーのカードから入力受付用ボタンを取得
	
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
	if (count == 0) {
		for (auto itr : cardButton) { itr->SetRunClickMonitor(true); } //クリック検知を開始する
	}


}
#include "PK_Main.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"

#include "../Code/Component/ComponentArray.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"



Poker::Main::Main(Poker& set) :parent(&set), phase(0), count(0), cpuWait(30), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), betLogic(std::deque<Cmp_CPUBetLogic*>(3)), playerButton(std::deque<Button*>()), actionButton(nullptr), foldButton(nullptr), playerGage(nullptr), playerGageBorder(nullptr), gageControl(nullptr), actionButtonImage(nullptr) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
	for (int i = 0; i < betLogic.size(); ++i) { betLogic[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_CPUBetLogic>(); } //ベットロジック取り出し、chara配列の並び順がplayer最後になってるのでこれで動く、不安ならif文でplayerチェックしてもいい
	parent->chara[(int)Poker::Character::player]->EditAppendCmp()->EditCmpMulti<Button>(playerButton); //ボタン取り出し
	PlayerButtonAnalyze(playerButton, &actionButton, &foldButton); //ボタン配列をactionとfoldに分解格納
	actionButtonImage = actionButton->EditAlwaysCmp<Cmp_Image>(); //アクション用ボタンの画像を取り出す


	playerGage = parent->chara[(int)Poker::Character::player]->EditAppendCmp()->EditCmp<Gage>(); //ゲージ取り出し
	playerGageBorder = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_Border>(); //ゲージから各種機能を取り出す
	playerGageUpper = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_UpperBorder>(); //プレイヤーゲージから上限設定機能の取り出し
	gageControl = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_MouseControl>();
}

void Poker::Main::Update() {
	++count;
	int access = parent->dealer->GetActionCharaSub(); //今回アクションを行うキャラへの添え字を記録するアクセスショートカット
	if (typeid(*parent->chara[access]) == typeid(CPU)) { //アクションキャラがcpuの場合

		if (count > cpuWait) { //指定待機時間を超えた場合実行アクションを決定する
			count = 0; //カウントリセット

			Cmp_BetActionRecord* record = actionRecord[access]; //このキャラのベット記録を取得
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
			if (action == Cmp_BetActionRecord::Action::raise && record->GetRaiseRunCount() >= betData->ReadRaiseSplit()->size()) { action = Cmp_BetActionRecord::Action::call; } //レイズ可能額全てを使い切っていた場合コールになる


			if (action == Cmp_BetActionRecord::Action::raise) { //レイズ額出し処理
				int runCount = record->GetRaiseRunCount(); //今回のsplit読み出し開始位置を入れる
				int raiseAdd = RaiseCalculation(*betData->ReadRaiseSplit(), runCount, oldPay, betRequest, parent->dealer->GetBB(), parent->chara[access]->GetCoint()); //レイズによる増分を得る

				record->SetRaiseRunCount(runCount); //使用済み分割数を記録する
				if (raiseAdd <= 0) { action = Cmp_BetActionRecord::Action::call; } //レイズしても届かなかったり所持金の問題で指定分レイズできなかった場合callにする
				else { pay += raiseAdd; } //普通にレイズできれば増分を加える
			}
			if (action == Cmp_BetActionRecord::Action::call && pay == 0) { action = Cmp_BetActionRecord::Action::check; } //指定アクションがcallで金額支払いが不要の場合チェックになる
			if (parent->chara[access]->GetCoint() - pay <= 0) { //支払額が所持金以上になる場合
				action = Cmp_BetActionRecord::Action::allIn; //allInになる
				pay = parent->chara[access]->GetCoint(); //支払額を所持金に合わせる
			}


			record->SetActionRecord(action, true); //該当アクションを動作済みにする
			record->SetIsAction(true); //アクション済みに設定

			if (action == Cmp_BetActionRecord::Action::call || action == Cmp_BetActionRecord::Action::raise) { parent->pot->SetMainPot(pay, *parent->chara[access]); } //call、raiseの場合メインポットへ
			if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent->chara[access]); } //allInの場合サイドポットへ
			if (action != Cmp_BetActionRecord::Action::fold) { parent->chara[access]->SetCoin(parent->chara[access]->GetCoint() - pay); } //fold以外の場合所持金から支払額を減算する(checkの場合payは0なので弾く必要なし)

			if (action == Cmp_BetActionRecord::Action::raise) { //レイズしていた場合全員のアクション状況の見直しを行う
				for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allInをしていない場合未アクション状態に更新する
				playerGageBorder->SetBorder((float)(pay + oldPay) / (parent->dealer->GetBB() * parent->dealer->GetMaxBet())); //ゲージの最低値を更新
				record->SetIsAction(true); //レイズしたキャラのアクションは終了済みに設定する
			}
			int endCount = ActionEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
			parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す

			if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
				SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
				parent->dealer->SetActionChara((ChangeEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //changeはallInしたキャラもアクション対象なので次回キャラの設定に含める

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
	int pay = std::round(playerGage->GetVol() * parent->dealer->GetMaxBet() * parent->dealer->GetBB()); //現在ゲージに合わせた支払額
	int oldPay = parent->pot->Inquiry(*parent->chara[access]); //前回までの支払額

	if (pay == parent->pot->GetCurrentMaxBet() && pay - oldPay != 0) { action = Cmp_BetActionRecord::Action::call; } //支払額が現在最大ベットと同値だった場合アクションはcall、但し最終支払額が0になる場合check
	if (pay > parent->pot->GetCurrentMaxBet()) { action = Cmp_BetActionRecord::Action::raise; } //支払額が現在最大ベットを超えていた場合アクションはraise
	pay -= oldPay; //支払状況を加味した額に変更

	if (parent->chara[access]->GetCoint() - pay <= 0) { action = Cmp_BetActionRecord::Action::allIn; } //支払額が所持金を超えていた場合AllIn

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
			playerGageBorder->SetBorder((float)(pay + oldPay) / (parent->dealer->GetBB() * parent->dealer->GetMaxBet())); //ゲージの最低値を更新
			for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allInをしていない場合未アクション状態に更新する
		}
		record->SetActionRecord(action, true); //該当アクションを動作済みにする
		record->SetIsAction(true); //レイズしたプレイヤーのアクションは終了済みに設定する
		endCount = ActionEndCount(actionRecord, access); //endcountの更新
	}
	parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す


	if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
		SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
		parent->dealer->SetActionChara((ChangeEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //changeはallInしたキャラもアクション対象なので次回キャラの設定に含める

		if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //ファーストベットだった場合次実行するシーケンスはカード交換
		else { parent->run = parent->list[(int)Poker::Section::showdown]; } //セカンドベットならショーダウンへ移行する
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

	gageControl->SetRunUpdate(false); //ゲージの操作受け付けを終了する
	count = 0; //カウントリセット
}

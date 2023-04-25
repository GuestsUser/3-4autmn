#include "PK_Player.h"
#include "PK_Player_Main.h"

#include "PK_CardDealer.h"
#include "PK_Chara.h"
#include "PK_Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"

#include "Button.h"
#include "Gage.h"
#include "Cmp_Gage_ControlSound.h"
#include "Cmp_Button_ClickCheck.h"
#include "Cmp_Gage_MouseControl.h"
#include "Cmp_Image.h"
#include "Cmp_PK_Chara_SE.h"
#include "Cmp_Sound.h"

#include <deque>

void PK_Player::Main::Update() {
	++count;
	if (count == 1) { //プレイヤーに操作が移った瞬間ならば各種ボタンを有効化する
		parent->actionButton->SetRunUpdateDraw(true, true); //ボタンのクリック検知開始と表示許可を出す 
		parent->foldButton->SetRunUpdateDraw(true, true);
		parent->actionButton->EditClick()->SetRunUpdateBundle(true); //クリック追加機能のUpdate実行を許可する

		parent->gageControl->SetRunUpdate(true); //ゲージの操作受け付けを開始する
		parent->gageSound->SetSoundStop(false); //ゲージ操作音を有効化する
	}


	Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::check; //今回のアクションを記録する、取り敢えずcheckを入れる
	int pay = std::round(parent->gage->GetVol() * parent->dealer->GetMaxBet() * parent->dealer->GetBB()); //現在ゲージに合わせた支払額
	int oldPay = parent->pot->Inquiry(*parent); //前回までの支払額

	if (pay == parent->pot->GetCurrentMaxBet() && pay - oldPay != 0) { action = Cmp_BetActionRecord::Action::call; } //支払額が現在最大ベットと同値だった場合アクションはcall、但し最終支払額が0になる場合check
	if (pay > parent->pot->GetCurrentMaxBet()) { action = Cmp_BetActionRecord::Action::raise; } //支払額が現在最大ベットを超えていた場合アクションはraise
	pay -= oldPay; //支払状況を加味した額に変更

	if (parent->GetCoint() - pay <= 0) { action = Cmp_BetActionRecord::Action::allIn; } //支払額が所持金を超えていた場合AllIn

	parent->actionButtonImage->SetAnimeSub((int)action); //ボタン画像を現在のアクションの物に変更

	if (parent->actionButton->GetRunUpdateClick()) { //アクションボタンが押された場合の処理
		if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent); } //allInの場合サイドポットへ
		else if (action != Cmp_BetActionRecord::Action::check) { parent->pot->SetMainPot(pay, *parent); } //call,raiseだった場合メインポットへ
		parent->SetCoin(parent->GetCoint() - pay); //所持金から支払額を減算する

		parent->record->SetActionRecord(action, true); //該当アクションを動作済みにする
		parent->record->SetIsAction(true); //レイズしたプレイヤーのアクションは終了済みに設定する

		if (action != Cmp_BetActionRecord::Action::check) { parent->se->ReadSE(Cmp_PK_Chara_SE::Request::call)->Play(); } //check以外ならベット音を鳴らす
		if (action == Cmp_BetActionRecord::Action::raise || action == Cmp_BetActionRecord::Action::allIn) { parent->se->ReadSE(Cmp_PK_Chara_SE::Request::raise)->Play(); } //raise又はallInしていれば対応した音を鳴らす
	}
	if (parent->foldButton->GetRunUpdateClick()) { //foldボタンが押された場合の処理
		action = Cmp_BetActionRecord::Action::fold; //実行アクションをfoldにセット
		for (auto itr : *parent->EditHand()->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //手札をfold表示へ変更
		parent->record->SetActionRecord(action, true); //foldを動作済みにする
		parent->record->SetIsAction(true); //アクション済みに設定

		parent->se->ReadSE(Cmp_PK_Chara_SE::Request::fold)->Play(); //fold音を鳴らす
	}
	if (!parent->record->GetIsAction()) { //アクション未実行なら
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //noActionを設定
		return; //終わり
	}


	//ボタンのクリック検知終了と表示隠し、クリック情報の削除を行う
	parent->actionButton->SetRunUpdateDraw(false, false);
	parent->actionButton->SetRunUpdateDrawClick(false, false);
	parent->foldButton->SetRunUpdateDraw(false, false);
	parent->foldButton->SetRunUpdateDrawClick(false, false);

	parent->gageControl->SetRunUpdate(false); //ゲージの操作受け付けを終了する
	parent->gageSound->SetSoundStop(true); //ゲージ操作音を無効化する
	count = 0; //時間カウントリセット

	parent->record->SetFinalAction(action); //今回アクションを最終アクションにする
}

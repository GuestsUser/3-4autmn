#include "Poker.h"
#include "PK_Player.h"
#include "PK_Player_Change.h"

#include "PK_CardDealer.h"
#include "PK_Card.h"
#include "PK_SectionLibrary.h"

#include "Button.h"
#include "Cmp_Hand.h"
#include "Cmp_Image.h"
#include "Cmp_PK_Chara_SE.h"
#include "Cmp_Sound.h"

PK_Player::Change::Change(PK_Player& parent) :parent(&parent), moveY(-48), count(0) {
	for (auto itr : *parent.EditHand()->EditCard()) {
		cardButton.push_back(itr->EditAppendCmp()->EditCmp<Button>()); //プレイヤーのカードから入力受付用ボタンを取得
		cardPos.push_back(&itr->EditTransform()->EditPos()); //各カードのTransformから位置情報を抜き出しておく
	}

	originalY = (*parent.EditHand()->EditCard())[0]->ReadTransform()->ReadPos().GetY(); //カードの元yを記憶しておく
}

void PK_Player::Change::Update() {
	++count;
	if (count == 1) {
		parent->actionButton->SetRunUpdateDraw(true, true); //交換用ボタンの有効化
		parent->actionButton->EditClick()->SetRunUpdateBundle(true); //クリック追加機能のUpdate実行を許可する
		for (auto itr : cardButton) { itr->SetRunClickMonitor(true); } //クリック検知を開始する
	}
	parent->actionButtonImage->SetAnimeSub((int)Cmp_BetActionRecord::Action::change); //ボタン画像を交換に変更


	for (int i = 0; i < cardButton.size(); ++i) { //各カードのクリックチェック
		if (cardButton[i]->GetRunUpdateClick()) { //クリックされた場合
			int y = cardPos[i]->GetY() - moveY * (1 - 2 * (cardPos[i]->GetY() == originalY)); //カードが元位置と同じならmoveY分動かし、違っていればmoveY分戻す
			cardPos[i]->SetY(y); //カード位置変更
			cardButton[i]->EditTransform()->EditPos().SetY(y); //ボタンの位置もカード位置に合わせる

			cardButton[i]->EditClick()->SetRunUpdate(false); //クリックしてない扱いに戻す
		}
	}


	if (parent->actionButton->GetRunUpdateClick()) { //アクションボタンが押された場合の処理
		bool runChange = false; //カード交換を実行した場合trueにする
		for (int i = 0; i < cardButton.size(); ++i) { //各カードの交換チェック
			std::deque<PK_Card*>* card = parent->EditHand()->EditCard(); //カード配列を保持
			if (cardPos[i]->GetY() != originalY) { //カードが元位置にない場合交換するとして扱う
				(*card)[i]->SetCard(parent->cardDealer->DeckDraw()); //交換指定のあるカードを交換
				runChange = true; //カード交換を行ったのでtrueを設定

				cardPos[i]->SetY(originalY); //位置を元に戻す処理
				cardButton[i]->EditTransform()->EditPos().SetY(originalY);
			}
		}
		if (runChange) { parent->se->ReadSE(Cmp_PK_Chara_SE::Request::cardChange)->Play(); } //カード交換があった場合対応seを鳴らす
		parent->EditHand()->HandPowerUpdate(); //役の強さを新しい手札に合わせる

		parent->record->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //アクション済みに設定する
		parent->record->SetIsAction(true);

		parent->actionButton->SetRunUpdateDraw(false, false); //ボタン無効化
		parent->actionButton->SetRunUpdateDrawClick(false, false); //クリック状態のリセット
		for (auto itr : cardButton) { itr->SetRunClickMonitor(false); } //クリック検知を無効化

		count = 0; //カウントリセット
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //交換したのでchangeを最終アクションに指定
		return;//終わり


	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //アクションを実行してないのでnoActionを設定
}

void PK_Player::Change::Reset() { //カード位置が操作されたままの可能性があるので戻しておく
	for (int i = 0; i < cardButton.size(); ++i) { 
		cardPos[i]->SetY(originalY); //位置を元に戻す
		cardButton[i]->EditTransform()->EditPos().SetY(originalY); //検知用ボタン位置も戻す
		cardButton[i]->SetRunClickMonitor(false); //クリック検知を無効化
	}
	count = 0; //カウントリセット
}
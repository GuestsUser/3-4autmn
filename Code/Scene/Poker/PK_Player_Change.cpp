#include "Poker.h"
#include "PK_Player.h"
#include "PK_Player_Change.h"

#include "CardDealer.h"
#include "PK_Card.h"
#include "PK_SectionLibrary.h"

#include "../Code/Component/Button.h"
#include "../Code/Component/Cmp_Image.h"

PK_Player::Change::Change(PK_Player& parent):parent(&parent), moveY(-48), count(0) {
	for (auto itr : *parent.EditCard()) {
		cardButton.push_back(itr->EditAppendCmp()->EditCmp<Button>()); //プレイヤーのカードから入力受付用ボタンを取得
		cardPos.push_back(&itr->EditTransform()->EditPos()); //各カードのTransformから位置情報を抜き出しておく
	}

	originalY = (*parent.EditCard())[0]->ReadTransform()->ReadPos().GetY(); //カードの元yを記憶しておく
}

void PK_Player::Change::Update() {
	++count;
	if (count == 1) {
		parent->actionButton->SetRunUpdate(true); //交換用ボタンの有効化
		parent->actionButton->SetRunDraw(true);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(true); } //クリック検知を開始する
	}
	parent->actionButtonImage->SetAnimeSub((int)Cmp_BetActionRecord::Action::change); //ボタン画像を交換に変更


	for (int i = 0; i < cardButton.size(); ++i) { //各カードのクリックチェック
		if (cardButton[i]->GetRunUpdateClick()) { //クリックされた場合
			int y = cardPos[i]->GetY() - moveY * (1 - 2 * (cardPos[i]->GetY() == originalY)); //カードが元位置と同じならmoveY分動かし、違っていればmoveY分戻す
			cardPos[i]->SetY(y); //カード位置変更
			cardButton[i]->EditTransform()->EditPos().SetY(y); //ボタンの位置もカード位置に合わせる

			cardButton[i]->SetRunUpdateClick(false); //クリックしてない扱いに戻す
		}
	}


	if (parent->actionButton->GetRunUpdateClick()) { //アクションボタンが押された場合の処理
		for (int i = 0; i < cardButton.size(); ++i) { //各カードの交換チェック
			std::deque<PK_Card*>* card = parent->EditCard(); //カード配列を保持
			if (cardPos[i]->GetY() != originalY) { //カードが元位置にない場合交換するとして扱う
				(*card)[i]->SetCard(parent->cardDealer->DeckDraw()); //交換指定のあるカードを交換

				cardPos[i]->SetY(originalY); //位置を元に戻す処理
				cardButton[i]->EditTransform()->EditPos().SetY(originalY);
			}
		}

		parent->record->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //アクション済みに設定する
		parent->record->SetIsAction(true);

		parent->actionButton->SetRunUpdate(false); //ボタン無効化
		parent->actionButton->SetRunDraw(false);
		parent->actionButton->SetRunUpdateClick(false); //クリック状態のリセット
		parent->actionButton->SetRunDrawClick(false);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(false); } //クリック検知を無効化

		count = 0; //カウントリセット
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //交換したのでchangeを最終アクションに指定
		return;//終わり


	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //アクションを実行してないのでnoActionを設定
}
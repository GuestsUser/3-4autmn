#include "PK_Chara.h"
#include "PK_CPU.h"
#include "PK_CPU_Change.h"

#include "PK_Card.h"
#include "PK_CardDealer.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_Hand.h"

#include "PK_SectionLibrary.h"

#include <deque>

void PK_CPU::Change::Update() {
	++count;
	if (count > waitTime) {
		count = 0; //カウントリセット

		parent->record->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //アクション済みに設定する
		parent->record->SetIsAction(true);

		//特定状態で動いてない可能性あり
		std::deque<int> hand = parent->EditHand()->GetHandPower(); //手札評価を得る
		if (hand[0] <= (int)Cmp_Hand::HandRank::OnePair * (int)Cmp_Hand::CardPower::max) { //ワンペア以下だった場合リーチチェックを行う
			PK_Card* change = parent->EditHand()->ReachCheck(); //ストレート、フラッシュに不要なカードを取得
			if (change != nullptr) { //changeに有効なカードが入った場合チェックを行う
				change->SetCard(parent->cardDealer->DeckDraw()); //不要カードを交換
				change->SetMarking(true); //交換したカードをマーキング
				parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //交換したのでchangeを最終アクションに指定
				parent->EditHand()->HandPowerUpdate(); //役の強さを新しい手札に合わせる

				return; //終わり
			}
		}

		std::deque<PK_Card*> changeList = std::deque<PK_Card*>(); //交換を行う手札の参照を入れてゆく
		int handRank = hand[0] / (int)Cmp_Hand::CardPower::max; //完成役をHandRank形式に直した物を格納
		int start = 1; //hand評価から交換カード取り出しを始める位置
		switch ((Cmp_Hand::HandRank)handRank) {
		case Cmp_Hand::HandRank::No: start = 0; break;
		case Cmp_Hand::HandRank::OnePair: start = 1; break;
		case Cmp_Hand::HandRank::TwoPair: start = 2; break;
		case Cmp_Hand::HandRank::ThreeCard: start = 1; break;
		case Cmp_Hand::HandRank::FourCard: start = 1; break;
		default: start = hand.size(); break; //上記ハンドでない場合交換はしない
		}

		if (handRank <= (int)Cmp_Hand::HandRank::OnePair) { //完成役がワンペア以下だった場合
			if (hand[start] < (int)border) { changeList.push_back(Power2Card(*parent->EditHand()->EditCard(), hand[start])); } //最初のカードがborder以下ならそのカードは交換する
			++start; //startは交換の有無に関わらず進めないと強制的に交換されてしまうので進める
		}

		for (int i = start; i < hand.size(); ++i) { //役になってないカードを交換に指定する
			changeList.push_back(Power2Card(*parent->EditHand()->EditCard(), hand[i])); //handと一致するカードを交換カードとしてリストに加える処理
		}
		for (auto itr : changeList) { //リスト内のカードを交換する処理
			itr->SetCard(parent->cardDealer->DeckDraw()); //交換指定のあるカードを交換
			itr->SetMarking(true); //交換したカードをマーキング
		}
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //交換したのでchangeを最終アクションに指定
		parent->EditHand()->HandPowerUpdate(); //役の強さを新しい手札に合わせる

		return; //終わり
	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //交換してないのでnoActionを指定

}

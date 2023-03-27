#include "PK_Chara.h"
#include "PK_CPU.h"
#include "PK_CPU_Change.h"

#include "PK_Card.h"
#include "PK_CardDealer.h"
#include "Cmp_BetActionRecord.h"

#include "PK_SectionLibrary.h"

#include <deque>

void PK_CPU::PK_Change::Update() {
	++count;
	if (count > waitTime) {
		count = 0; //カウントリセット

		parent->record->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //アクション済みに設定する
		parent->record->SetIsAction(true);

		//特定状態で動いてない可能性あり
		std::deque<int> hand = parent->cardDealer->HandCheck(*parent); //手札評価を得る
		if (hand[0] <= (int)PK_CardDealer::HandRank::OnePair * (int)PK_CardDealer::CardPower::max) { //ワンペア以下だった場合リーチチェックを行う
			int change = parent->cardDealer->ReachCheck(*parent); //ストレート、フラッシュに不要なカード
			if (change != -1) { //changeに有効なカードが入った場合チェックを行う
				for (auto itr : *parent->EditCard()) {
					if (itr->GetCard() == change) {
						itr->SetCard(parent->cardDealer->DeckDraw()); //不要カードを交換
						itr->SetMarking(true); //交換したカードをマーキング
						parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //交換したのでchangeを最終アクションに指定
						return;//終わり
					}
				}
			}
		}

		std::deque<PK_Card*> changeList = std::deque<PK_Card*>(); //交換を行う手札の参照を入れてゆく
		int handRank = hand[0] / (int)PK_CardDealer::CardPower::max; //完成役を数値に直した物を格納
		int start = 1; //hand評価から交換カード取り出しを始める位置
		switch ((PK_CardDealer::HandRank)handRank) {
		case PK_CardDealer::HandRank::No: start = 0; break;
		case PK_CardDealer::HandRank::OnePair: start = 1; break;
		case PK_CardDealer::HandRank::TwoPair: start = 2; break;
		case PK_CardDealer::HandRank::ThreeCard: start = 1; break;
		case PK_CardDealer::HandRank::FourCard: start = 1; break;
		default: start = hand.size(); break; //上記ハンドでない場合交換はしない
		}

		if (handRank <= (int)PK_CardDealer::HandRank::OnePair) { //完成役がワンペア以下だった場合
			if (hand[start] < (int)border) { changeList.push_back(Power2Card(*parent->EditCard(), hand[start])); } //最初のカードがborder以下ならそのカードは交換する
			++start; //startは交換の有無に関わらず進めないと強制的に交換されてしまうので進める
		}

		for (int i = start; i < hand.size(); ++i) { //役になってないカードを交換に指定する
			changeList.push_back(Power2Card(*parent->EditCard(), hand[i])); //handと一致するカードを交換カードとしてリストに加える処理
		}
		for (auto itr : changeList) { //リスト内のカードを交換する処理
			itr->SetCard(parent->cardDealer->DeckDraw()); //交換指定のあるカードを交換
			itr->SetMarking(true); //交換したカードをマーキング
		}
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //交換したのでchangeを最終アクションに指定
		return;//終わり
	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //交換してないのでnoActionを指定

}

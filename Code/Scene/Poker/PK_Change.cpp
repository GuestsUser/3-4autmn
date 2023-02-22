#include "PK_Change.h"
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

#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "Cmp_CPUBetLogic.h"

Poker::Change::Change(Poker& set) :parent(&set), count(0), cpuWait(30), moveY(-48), border(CardDealer::CardPower::jack), isClick(std::deque<bool>()), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), actionButton(nullptr), cardButton(std::deque<Button*>()), cardPos(std::deque<Vector3*>()) {
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

			int endCount = ChangeEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
			parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す

			if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
				SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット

				parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //mainではallInキャラのアクションは不能なのでそれを取り除いた値に応じてとなる
				parent->run = parent->list[(int)Poker::Section::main]; //セカンドベットへ
				((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);


				int endCount = 1; //アクション不能なキャラの数を取得
				for (endCount; endCount < actionRecord.size(); ++endCount) {
					if (!BetIgnore(actionRecord[(access + endCount) % actionRecord.size()])) { break; } //チェックキャラが終了条件の1つにも引っかからなかった場合中断
				}
				if (endCount >= actionRecord.size()) { parent->run = parent->list[(int)Poker::Section::showdown]; } //どのキャラもベット不能の場合ショーダウン直行
			}

			//特定状態で動いてない可能性あり
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
			int handRank = hand[0] / (int)CardDealer::CardPower::max; //完成役を数値に直した物を格納
			int start = 1; //hand評価から交換カード取り出しを始める位置
			switch ((CardDealer::HandRank)handRank) {
			case CardDealer::HandRank::No: start = 0; break;
			case CardDealer::HandRank::OnePair: start = 1; break;
			case CardDealer::HandRank::TwoPair: start = 2; break;
			case CardDealer::HandRank::ThreeCard: start = 1; break;
			case CardDealer::HandRank::FourCard: start = 1; break;
			default: start = hand.size(); break; //上記ハンドでない場合交換はしない
			}


			if (handRank <= (int)CardDealer::HandRank::OnePair) { //完成役がワンペア以下だった場合
				if (hand[start] < (int)border) { changeList.push_back(Power2Card(*parent->chara[access]->EditCard(), hand[start])); } //最初のカードがborder以下ならそのカードは交換する
				++start; //startは交換の有無に関わらず進めないと強制的に交換されてしまうので進める
			}

			for (int i = start; i < hand.size(); ++i) { //役になってないカードを交換に指定する
				changeList.push_back(Power2Card(*parent->chara[access]->EditCard(), hand[i])); //handと一致するカードを交換カードとしてリストに加える処理
			}
			for (auto itr : changeList) { //リスト内のカードを交換する処理
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

		int endCount = ChangeEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
		parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す

		if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
			SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
			parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //mainではallInキャラのアクションは不能なのでそれを取り除いた値に応じてとなる
			parent->run = parent->list[(int)Poker::Section::main]; //セカンドベットへ
			((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);


			int endCount = 1; //アクション不能なキャラの数を取得
			for (endCount; endCount < actionRecord.size(); ++endCount) {
				if (!BetIgnore(actionRecord[(access + endCount) % actionRecord.size()])) { break; } //チェックキャラが終了条件の1つにも引っかからなかった場合中断
			}
			if (endCount >= actionRecord.size()) { parent->run = parent->list[(int)Poker::Section::showdown]; } //どのキャラもベット不能の場合ショーダウン直行
		}


		actionButton->SetRunUpdate(false); //ボタン無効化
		actionButton->SetRunDraw(false);
		actionButton->SetRunUpdateClick(false); //クリック状態のリセット
		actionButton->SetRunDrawClick(false);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(false); } //クリック検知を無効化

		count = 0; //カウントリセット
	}


}

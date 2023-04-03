#include "PK_Ini.h"

#include "Scene.h"
#include "Poker.h"
#include "ConstVal.h"

#include "PK_Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "PK_CardDealer.h"
#include "PK_SectionLibrary.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_Hand.h"
#include "ComponentArray.h"


Poker::Ini::Ini(Poker& set) :parent(&set), actionRecord(std::deque<Cmp_BetActionRecord*>((int)Poker::Character::length)) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}

void Poker::Ini::Update() {
	parent->pot->Reset();
	parent->dealer->Reset();
	parent->cardDealer->Reset();
	for (int i = 0; i < parent->chara.size(); ++i) {
		parent->chara[i]->Reset(); //キャラコンポーネントのリセット
		parent->chara[i]->SetSection(PK_Chara::Section::main); //実行セクションをmainに設定


		if (actionRecord[i]->GetIsLose()) { //今回キャラが敗北済みの場合
			std::deque<PK_Card*>* card = parent->chara[i]->EditHand()->EditCard(); //カードを管理する配列を取得
			for (auto itr : *card) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //カードをfold表示にする
		}

	}

	int pos = EnableCharaSearch(actionRecord, parent->dealer->ReadBtn()->GetBtnPos()); //敗北済みキャラを飛ばしてポジション決定
	parent->dealer->EditBtn()->SetBtnPos(pos); //勝負可能な最短のキャラ位置に設定する
	parent->dealer->SetActionChara(EnableCharaSearch(actionRecord, (pos + 1) % parent->chara.size())); //位置更新に合わせて初めにアクションを開始するキャラを更新する

	parent->run = parent->list[(int)Poker::Section::pre];
}
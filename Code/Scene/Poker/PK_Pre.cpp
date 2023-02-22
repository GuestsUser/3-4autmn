#include "PK_Pre.h"
#include "PK_Main.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "CardDealer.h"

#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "Cmp_CPUBetLogic.h"


Poker::Pre::Pre(Poker& set) :parent(&set), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	playerGage = parent->chara[(int)Poker::Character::player]->EditCmp<Gage>(); //ゲージ取り出し
	playerGageBorder = playerGage->EditCmp<Cmp_Gage_Border>(); //ゲージから各種機能を取り出す
	playerGageUpper = playerGage->EditCmp<Cmp_Gage_UpperBorder>(); //プレイヤーゲージから上限設定機能の取り出し
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}

void Poker::Pre::Update() {
	BBSBLevy(parent->dealer->ReadBtn()->GetBtnPos(), parent->chara, actionRecord, *playerGageBorder, *playerGageUpper, *parent->pot, *parent->dealer); //BB、SBの徴収
	playerGage->SetVol(0); //プレイヤーのベットゲージ初期化

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

	if (EnableCharaSearch(actionRecord, parent->dealer->ReadBtn()->GetBtnPos()) <= -1) { //この段階で全キャラアクションを終了していた場合
		SequenceNextReset(actionRecord); //アクション実行記憶の初期化
		parent->run = parent->list[(int)Poker::Section::change]; //交換シーンに移行
		return; //終わり
	}
	parent->run = parent->list[(int)Poker::Section::main];
	((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(0); //ダウンキャストだが中身がハッキリしてるから許して……

	//デバッグ用
	//parent->run = parent->list[(int)Poker::Section::change];
}

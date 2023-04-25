#include "PK_NewGameReset.h"
#include "Poker.h"

#include "PK_BGM.h"
#include "PK_CardDealer.h"
#include "PK_Chara.h"
#include "PK_Dealer.h"
#include "PK_Pot.h"

void Poker::NewGameReset::Update() {
	parent->bgm->Reset(); //bgmシステムのリセット
	parent->pot->Reset(); //ポットのリセット
	parent->dealer->FullReset(); //BB等の管理状態の完全リセット
	parent->cardDealer->Reset(); //山札をリセット

	for (auto chara : parent->chara) { chara->FullReset(); } //キャラ状態を完全リセット
	for (auto section : parent->list) { section->FullReset(); } //セクションの完全リセット

	parent->SetNextSection(Poker::Section::pre); //新しいゲームはpreスタート
}
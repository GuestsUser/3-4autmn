#include <DxLib.h>

#include "../Scene.h"
#include "Poker.h"
#include "PokerFontData.h"

#include "PK_Ini.h"
#include "PK_Pre.h"
#include "PK_Main.h"
#include "PK_Change.h"
#include "PK_ShowDown.h"
#include "PK_NoContest.h"
#include "PK_GameOver.h"
#include "PK_GameClear.h"

#include "PK_Card.h"
#include "CPU.h"
#include "Pot.h"
#include "Chara.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"
#include "../Code/OriginMath.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Image.h"

#include <deque>

void Poker::Update() {
	run->Update(); //Update実行
	for (auto itr : chara) { if (itr->GetRunUpdate()) { itr->Update(); } } //キャラ内の追加機能を実行

	run = run->GetNext(); //次シーンの取得
	for (auto itr : list) { //次シーンがlist内にある物かどうかチェック
		if (run == itr) { return; } //list内にあった場合Drawに処理を移す
	}

	SetNext(run); //次シーンがPoker管理のScene以外だった場合それを次シーンに設定してPokerは終了する
}

void Poker::Draw() {
	back->Draw(); //背景描写
	pot->Draw(); //ポット描写
	dealer->Draw(); //ボタンポジションの描写
	for (auto itr : chara) { itr->Draw(); } //各キャラの手札とか所持金とか描写

	run->Draw();
}

Poker::Poker() :pot(new Pot()), dealer(new PK_Dealer()), cardDealer(new CardDealer()), back(nullptr), list(std::deque<Scene*>()) {
	PokerFontData::SetUp(); //フォントデータの使用準備

	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_back.png")), 1); //背景画像作成
	back->EditTranform()->EditPos().SetXYZ(1280 / 2, 720 / 2, 0); //画面中央に配置

	for (int i = 0; i < (int)Character::length; ++i) { //キャラクター精製
		Chara* current = nullptr;

		if (i == (int)Character::player) { current = new PK_Player(*pot, *dealer, *cardDealer); } //プレイヤーの精製
		else { current = new CPU(i, *pot, *dealer, *cardDealer); } //cpuの精製

		current->SetBBView(PK_Player::BBView::hide); //BB表示は隠しておく
		

		chara.push_back(current);
	}
	cardDealer->Reset(); //最初はIniを実行しないので山札だけは初期化しておく

	list.push_back(new Ini(*this));
	list.push_back(new Pre(*this));
	list.push_back(new Main(*this));
	list.push_back(new Change(*this));
	list.push_back(new ShowDown(*this));
	list.push_back(new NoContest(*this));
	list.push_back(new GameOver(*this));
	list.push_back(new GameClear(*this));



	run = list[(int)Section::pre]; //Preから開始
}

Poker::~Poker() {
	for (auto itr : list) { delete itr; } //Pokerで管理していたシーンの削除
	for (int i = 0; i < (int)Character::length; ++i) { delete chara[i]; }
	delete pot;
	delete dealer;
	delete cardDealer;
	delete back;
}




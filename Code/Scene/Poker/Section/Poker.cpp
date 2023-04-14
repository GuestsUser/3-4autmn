#include <DxLib.h>

#include "Scene.h"
#include "Poker.h"
#include "PokerFontData.h"
#include "Title/Title_Select.h"

#include "PK_Ini.h"
#include "PK_Pre.h"
#include "PK_Main.h"
#include "PK_Change.h"
#include "PK_ShowDown.h"
#include "PK_NoContest.h"
#include "PK_GameOver.h"
#include "PK_GameClear.h"
#include "PK_NewGameReset.h"
#include "Cmp_PK_Pause.h"

#include "PK_Chara.h"
#include "PK_CPU.h"
#include "PK_Player.h"

#include "PK_Card.h"
#include "PK_CardDealer.h"
#include "PK_Dealer.h"
#include "PK_Pot.h"
#include "OriginMath.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "Button.h"
#include "Gage.h"
#include "Cmp_Button_ClickCheck.h"
#include "Cmp_ButtonOverlapGroup.h"
#include "Cmp_Gage_MouseControl.h"
#include "Cmp_Gage_Border.h"
#include "Cmp_Gage_UpperBorder.h"
#include "Cmp_Image.h"

#include <deque>

void Poker::Update() {
	pauseButon->Update(); //ポーズ画面とボタンの処理実行
	if (pauseButon->GetRunUpdateClick()) { return; } //クリックされた場合ポーズ画面実行中なのでゲームシーンに関する処理は実行しない

	run->Update(); //指定セクションの処理実行
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

	run->Draw(); //実行セクション専用描写
	pauseButon->Draw(); //ポーズ画面とボタンの描写
}

Poker::Poker() :pot(new PK_Pot()), dealer(new PK_Dealer()), cardDealer(new PK_CardDealer()), back(nullptr), list(std::deque<Scene*>()) {
	PokerFontData::SetUp(); //フォントデータの使用準備

	pauseButon = new Button(65, 53, 45, 37);
	pauseButon->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause.png")), 1, pauseButon->EditTransform())); //ポーズボタン画像を作成
	pauseButon->EditAlways()->SetCmp(new Cmp_ButtonOverlapGroup(*pauseButon)); //ポーズボタンに押された時重なっているボタンの入力を切る機能の追加
	//上記重なっているボタン入力受付禁止コンポーネントのグループは該当ボタン作成箇所で各個グループへ格納する
	pauseButon->EditClick()->SetCmp(new Cmp_PK_Pause(*pauseButon, *this)); //クリックされた時起動するポーズ画面実行機能追加

	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_back.png")), 1); //背景画像作成
	back->EditTranform()->EditPos().SetXYZ(1280 / 2, 720 / 2, 0); //画面中央に配置

	for (int i = 0; i < (int)Character::length; ++i) { //キャラクター精製
		PK_Chara* current = nullptr;

		if (i == (int)Character::player) { current = new PK_Player(*pot, *dealer, *cardDealer); } //プレイヤーの精製
		else { current = new PK_CPU(i, *pot, *dealer, *cardDealer); } //cpuの精製

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
	list.push_back(new NewGameReset(*this));


	run = list[(int)Section::pre]; //Preから開始
}

Poker::~Poker() {
	PokerFontData::Release(); //フォントデータを格納していた配列をクリーンする
	for (auto itr : list) { delete itr; } //Pokerで管理していたシーンの削除
	for (int i = 0; i < (int)Character::length; ++i) { 
		delete chara[i]; 
	}
	delete pot;
	delete dealer;
	delete cardDealer;
	delete back;
	delete pauseButon;
}

void Poker::SetNextSection(Section section) {
	if (section == Section::titleback) { SetNext(new Title_Select()); } //titlebackが指定されたらゲームセレクト画面へ戻す
	else { run = list[(int)section]; } //それ以外なら該当セクションへ移行する
}



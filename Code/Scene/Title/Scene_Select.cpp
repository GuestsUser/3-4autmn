#include "DxLib.h"

#include "../Code/Scene/Scene.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_ButtonGroup.h"
#include "Cmp_SelectSelector.h"
#include "Scene_Select.h"
#include "Scene_Explain.h"

//プレイするゲームシーンをインクルード
#include"../Code/Scene/Karuta/Scene_Karuta.h"
#include"../Code/Scene/ConnectFour/Scene_ConnectFour.h"
#include"../Code/Scene/daifugou/CP_Scene.h"
#include"../Code/Scene/BlackJack/BJ_Main.h"
#include"../Code/Scene/Asuma/Scene_PageOne.h"
#include"../Code/Scene/Othello/Scene_Othello.h"
#include"../Code/Scene/Sugoroku/SR_Game.h"
#include <deque>


Scene_Select::Scene_Select() :explain(std::deque<Scene_Explain*>()), button(std::deque<Button*>()), run(nullptr) {
	SetFontSize(36); //描写文字サイズ指定

	int place = 9; //ボタン配置数
	int xSplit = 4; //ボタンの1列の配置数
	int ySplit = place / xSplit; //ボタンの配置行数
	int xSize = 260; //ボタンの画像サイズx
	int ySize = 203; //ボタンの画像サイズy

	for (int i = 0; i < place; ++i) {
		std::deque<Cmp_Image*>* explainImage = new std::deque<Cmp_Image*>(); //説明画像格納用変数
		Scene* gameScene = nullptr; //説明画面でクリックした時実行したいゲームシーン
		int* img = new int(0); //画像ハンドル格納用変数
		button.push_back(new Button((1240 / xSplit) / 2 + xSize * (i % xSplit), (720 / ySplit) / 2 + ySize * (int)(i / xSplit), xSize / 2, ySize / 2));
		
		switch (i) {
		case 0: //エアホッケーの説明画像とかを入れる項目
			*img = LoadGraph("Resource/image/Select_AirHockey.png"); //ボタン画像を入れる
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_AirHockey1.png")), 1)); //説明画像を入れる、ページ順は最初に入れた物が1ページになる
			break;
		case 1: //ブラックジャック
			*img = LoadGraph("Resource/image/Select_Blackjack.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Blackjack1.png")), 1));
			break;
		case 2: //大富豪
			*img = LoadGraph("Resource/image/Select_CareerPoker.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_CareerPoker1.png")), 1));
			break;
		case 3: //コネクトフォー
			*img = LoadGraph("Resource/image/Select_ConnectFour.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_ConnectFour1.png")), 1));
			break;
		case 4: //かるた
			*img = LoadGraph("Resource/image/Select_Karuta.png");
			gameScene = new Scene_Karuta(); //個別シーン飛ばし作例、scmに入れていたのがgameSceneになった程度の違い
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Karuta1.png")), 1));
			break;
		case 5: //ページワン
			*img = LoadGraph("Resource/image/Select_PageOne.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_PageOne1.png")), 1));
			break;
		case 6: //ポーカー
			*img = LoadGraph("Resource/image/Select_Poker.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker1.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker2.png")), 1)); //複数の説明画面導入作例
			break;
		case 7: //すごろく
			*img = LoadGraph("Resource/image/Select_Sugoroku.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Sugoroku1.png")), 1));
			gameScene = new SR_Game(); //個別シーン飛ばし作例、scmに入れていたのがgameSceneになった程度の違い
			break;
		case 8: //オセロ
			*img = LoadGraph("Resource/image/Select_Othello.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Othello1.png")), 1));
			break;
		}
		explain.push_back(new Scene_Explain(*explainImage, gameScene)); //ボタンを押した際の説明シーン作成

		button[i]->SetAlways(new Cmp_Image(*img, 1, button[i]->EditTransform())); //ボタンに画像を追加
		button[i]->SetClick(new Cmp_ButtonGroup(*button[i], button)); //ボタンが押された際、押されたボタン以外を停止する機能の追加
		button[i]->SetClick(new Cmp_SelectSelector(explain[i], &run, button)); //ボタンが押された際、runへexplain[i]を入れる機能の追加

		
	}

	
	//button.push_back(new Poker());
}

Scene_Select::~Scene_Select() {
	for (int i = 0; i < button.size(); ++i) {
		delete button[i]; //newしたbuttonの削除
		delete explain[i]; //newした説明シーンの削除
	}
}

void Scene_Select::Update() {
	if (run != nullptr) { //runに何か入っていた場合そちらを優先実行
		run->Update(); //run実行

		run = run->GetNext(); //runに設定された次の実行シーンを取得runに設定
		if (run == nullptr) { return; }  //空にされたら抜け、次回からは平常時のUpdateを実行する
		for (auto itr : explain) {
			if (run == itr) { return; } //explainと同じ物があった場合抜け、次回もrunを実行する
		}
		SetNext(run); //ここまで来たら設定されたシーンはゲーム実行シーンになるのでセレクト画面を終了しそちらに移行する
		return;
	}

	//runに何も入ってない場合
	for (auto itr : button) { itr->Update(); } //ボタンupdateを実行
}

void Scene_Select::Draw() {
	if (run != nullptr) { run->Draw(); } //runに何か入っていた場合そちらを優先実行
	else {
		for (auto itr : button) { itr->Draw(); } //ボタンdrawを実行
	}
}
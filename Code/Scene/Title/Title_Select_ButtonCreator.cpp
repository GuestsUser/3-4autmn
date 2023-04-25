#include "Title_Select_ButtonCreator.h"
#include "Title_Select_Explain.h"

#include "../Code/Scene/Scene.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_ButtonGroup.h"
#include "Cmp_3DSoundListener.h"
#include "Cmp_SelectSelector.h"
#include "Cmp_Button_ClickSound.h"
#include "SoundSetting.h"

//プレイするゲームシーンをインクルード
#include"../Code/Scene/Karuta/Scene_Karuta.h"
#include"../Code/Scene/ConnectFour/Scene_ConnectFour.h"
#include"../Code/Scene/daifugou/CP_Scene.h"
#include"../Code/Scene/BlackJack/BJ_Main.h"
#include"../Code/Scene/PageOne/Scene_PageOne.h"
#include"../Code/Scene/Othello/Scene_Othello.h"
#include"../Code/Scene/Sugoroku/SR_Game.h"
#include "../Code/Scene/Poker/Section/Poker.h"
#include"../Code/Scene/AirHockey/AirHockeyGameScene.h"

#include <deque>
#include <functional>

void Title_Select_ButtonCreator::Creat(Scene& parent, std::deque<Title_Select_Explain*>& explain, std::deque<Button*>& button, Scene*& run) {
	int place = 9; //ボタン配置数
	int xSplit = 4; //ボタンの1列の配置数
	int ySplit = place / xSplit; //ボタンの配置行数
	int xSize = 260; //ボタンの画像サイズx
	int ySize = 203; //ボタンの画像サイズy

	for (int i = 0; i < place; ++i) {
		std::deque<Cmp_Image*>* explainImage = new std::deque<Cmp_Image*>(); //説明画像格納用変数
		std::function<Scene* ()> sceneCreator = nullptr; //説明画面でクリックした時実行するゲームシーンを作成するラムダ式格納変数
		int* img = new int(0); //画像ハンドル格納用変数
		button.push_back(new Button((1240 / xSplit) / 2 + xSize * (i % xSplit), (720 / ySplit) / 2 + ySize * (int)(i / xSplit), xSize / 2, ySize / 2));

		switch (i) {
		case 0: //エアホッケーの説明画像とかを入れる項目
			*img = LoadGraph("Resource/image/Select_AirHockey.png"); //ボタン画像を入れる
			sceneCreator = []() -> Scene* { return new Scene_AirHockey(); };
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_AirHockey1.png")), 1)); //説明画像を入れる、ページ順は最初に入れた物が1ページになる
			break;
		case 1: //ブラックジャック
			*img = LoadGraph("Resource/image/BJ_Image/Select_Blackjack.png");
			sceneCreator = []() -> Scene* { return new BlackJack(); };
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/BJ_Image/Explain_Blackjack1.png")), 1));
			break;
		case 2: //大富豪
			*img = LoadGraph("Resource/image/Select_CareerPoker_comingsoon.png");
			//sceneCreator = []() -> Scene* { return new CP_Scene(); };
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_CareerPoker1.png")), 1));
			break;
		case 3: //コネクトフォー
			*img = LoadGraph("Resource/image/Select_ConnectFour.png");
			sceneCreator = []() -> Scene* { return new Scene_ConnectFour(); };
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_ConnectFour1.png")), 1));
			break;
		case 4: //かるた
			*img = LoadGraph("Resource/image/Select_Karuta.png");
			sceneCreator = []() -> Scene* { return new Scene_Karuta(); }; //個別シーン飛ばし作例、scmに入れていたのがgameSceneになった程度の違い
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Karuta1.png")), 1));
			break;
		case 5: //ページワン
			*img = LoadGraph("Resource/image/Select_PageOne.png");
			sceneCreator = []() -> Scene* { return new Scene_PageOne(); };
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/PageOne_Image/Explain_PageOne1.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/PageOne_Image/Explain_PageOne4.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/PageOne_Image/Explain_PageOne2.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/PageOne_Image/Explain_PageOne3.png")), 1));
			break;
		case 6: //ポーカー
			*img = LoadGraph("Resource/image/Select_Poker.png");
			sceneCreator = []() -> Scene* { return new Poker(); };
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker1.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker2.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker3.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker4.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker5.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker6.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker7.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker8.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker9.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker10.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker11.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker12.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker13.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker14.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker15.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker16.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker17.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker18.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker19.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker20.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker21.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker22.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker23.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker24.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker25.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker26.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker27.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker28.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker29.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker30.png")), 1));
			break;
		case 7: //すごろく
			*img = LoadGraph("Resource/image/Select_Sugoroku.png");
			sceneCreator = []() -> Scene* { return new SR_Game(); };
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Sugoroku1.png")), 1));
			break;
		case 8: //オセロ
			*img = LoadGraph("Resource/image/Othello_Image/OthelloAicon2.png");
			sceneCreator = []() -> Scene* { return new Scene_Othello(); };
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Othello_Image/RuleImagePage1.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Othello_Image/RuleImagePage2.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Othello_Image/RuleImagePage3.png")), 1));
			break;
		}
		explain.push_back(new Title_Select_Explain(*explainImage, sceneCreator)); //ボタンを押した際の説明シーン作成

		button[i]->EditAlways()->SetCmp(new Cmp_Image(*img, 1, button[i]->EditTransform())); //ボタンに画像を追加
		button[i]->EditClick()->SetCmp(new Cmp_ButtonGroup(*button[i], button)); //ボタンが押された際、押されたボタン以外を停止する機能の追加
		button[i]->EditClick()->SetCmp(new Cmp_SelectSelector(explain[i], &run)); //ボタンが押された際、runへ次シーンを入れる機能の追加
		button[i]->EditClick()->SetCmp(new Cmp_Button_ClickSound(*SoundSetting::CreateDefaultButtonClickSound(Cmp_3DSoundListener::EditTransform()))); //クリックされた時に鳴る音を追加

	}
}


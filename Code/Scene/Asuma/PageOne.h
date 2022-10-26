#pragma once
#include <list>
#include <vector>

class Card {
public:
	int img;	//画像用の変数
	int num;	//カードの数字
	int suit;	//カードのスート(マーク)

	//Card(画像、数値、スート、使用フラグ)
	Card(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};

class PageOne{
public:

	Card Card_back;		//カードの裏面の情報
	Card Card_joker;	//ジョーカーの情報

	std::vector<Card> Card_obj;		//全カードの情報
	std::list<Card> Player_card;	//プレイヤーの持っているカードの情報

	int card_type[65];	//画像用ハンドル

	int CF_Back;
	int CF_Panel;
	int CF_PCoin;
	int CF_CCoin;
	int CF_Yajirusi;

	float Yajirusi_Move;
	float Yajirusi_Y;

	int Yajirusi_Col[7];
	int Mouse_X; //マウスのX座標
	int Mouse_Y; //マウスのY座標
	int Player_X; //プレイヤーのX座標
	int Player_Y; //プレイヤーのY座標

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

	int i;
	int j;
	int r;
};

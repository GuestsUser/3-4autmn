#pragma once
#include <list>

class Card {
public:
	int img;	//画像用の変数
	int num;	//カードの数字
	int suit;	//カードのスート(マーク)
	bool flg;	//使用したかどうか(false:使ってない　true:使ってる)

	//Card(画像、数値、スート、使用フラグ)
	Card(int i, int n, int s, bool f) {
		img = i;
		num = n;
		suit = s;
		flg = f;
	}
};

class PO_Player {
private:

	Card Card_obj[54];	//カードの情報

	std::list<Card> Player_card;	//プレイヤーの持っているカードの情報

	int card_type[65];	//画像用ハンドル

	int i;

	float Yajirusi_Move;
	float Yajirusi_Y;

	int Yajirusi_Col[7];
	int Mouse_X; //マウスのX座標
	int Mouse_Y; //マウスのY座標
	int Player_X; //プレイヤーのX座標
	int Player_Y; //プレイヤーのY座標
public:
	void PO_Player_Initialize();
	void PO_Player_Finalize();
	void PO_Player_Update();
	void PO_Player_Draw();
};
//
//extern CF_Player cf_player;
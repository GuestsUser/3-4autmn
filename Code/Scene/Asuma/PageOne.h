#pragma once
#include "./../Scene.h"

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

class PageOne : public Scene{
private:
	Card Card_obj[54];	//カードの情報

	int card_type[65];	//画像用ハンドル

	int Mouse_X; //マウスのX座標
	int Mouse_Y; //マウスのY座標
	int Player_X; //プレイヤーのX座標
	int Player_Y; //プレイヤーのY座標

public:
	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();
};

#pragma once

class Card {
private:
	int img;	//画像用の変数
	int num;	//カードの数字
	int suit;	//カードのスート(マーク)

public:
	Card(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};

class PageOne {
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

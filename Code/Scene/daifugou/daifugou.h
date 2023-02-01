#pragma once

class CP {
private:
	int i, j, x, y;

public:

	int card_w = 200;	//カード１枚の幅
	int card_h = 300;	//カード１枚の高さ
	int Mouse_X;	//マウスのX座標
	int Mouse_Y;    //マウスのY座標
	int Player_X;
	int Player_Y;

	bool Hit(int mx, int my, int cx, int cy, int cw, int ch, double ExRate) {
		if (mx > cx - (cw * ExRate) / 2 && mx < cx + (cw * ExRate) / 2 && my > cy - (ch * ExRate) / 2 && my < cy + (ch * ExRate) / 2) {
			return true;
		}
		else {
			return false;
		}
	}

	void Player_Initialize();//済
	void Player_Finalize();//済
	void Player_Update();
	void Player_Draw();
	void onesec(void);//済
	void deckmake();//山札生成//済
	void datareset();//データの設定
	void deckshuffle();//シャッフル
	void phase(int n);
	void turn(int n);
	//void sort(int sort_x, int* sort_y, int sort_z);//ソートを決める
	void pl_routine(int n);
	void expend(int n);//手札が無くなった時
	void slash8(int n);//8切り用
	void main();
	void dealcards();
	void d3start();
	void status(int n);
	void print(int n);
	void revolution();
	void elevenback();
	void cp_routine(int n);
	void arrange(int n);
	//void main(void);
};

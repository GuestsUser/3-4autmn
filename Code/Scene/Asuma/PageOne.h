#pragma once
#include <vector>

#define MAX (4U)

class Card {
public:
	Card() {}

	int card_w = 200;	//カード１枚の幅
	int card_h = 300;	//カード１枚の高さ

	int img;	//画像用の変数
	int num;	//カードの数字
	int suit;	//カードのスート(マーク)

	//カードごとの当たり判定（マウスX座標、マウスY座標、カードX座標、カードY座標、カードの幅、カードの高さ、カードの画像倍率）
	bool Hit(int mx, int my, int cx, int cy, int cw, int ch, double ExRate) {
		if (mx > cx - (cw * ExRate) / 2 && mx < cx + (cw * ExRate) / 2 && my > cy - (ch * ExRate) / 2 && my < cy + (ch * ExRate) / 2) {
			return true;
		}
		else {
			return false;
		}
	}

	//Card(画像、数値、スート)
	Card(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};

class PageOne : public Card {
private:
	int card_type[54];	//画像用ハンドル
	int background;	//背景

	Card Card_back;		//カードの裏面の情報
	Card Card_joker;	//ジョーカーの情報

	//Card Card_obj[4][13];		//全カードの情報
	std::vector<Card> Card_obj;		//全カードの情報(山札)
	std::vector<Card> Player_card;	//プレイヤーの持っているカードの情報

	std::vector<Card> Field_card;		//場に出ているカード
	std::vector<Card> Cemetery_card;	//使用済みのカード

	std::vector<Card> NPC_card_1;		//NPC１号の持っているカードの情報
	std::vector<Card> NPC_card_2;		//NPC２号の持っているカードの情報
	std::vector<Card> NPC_card_3;		//NPC３号の持っているカードの情報

	int Pass_Icon;		//パスのアイコン画像
	int PageOne_Icon;	//ページワン宣言のアイコン画像

	bool PageOne_flg;	//ページワン宣言をしたかどうか(true:した	false:してない)

	bool PageOne_player;	//プレイヤーのページワン宣言
	bool PageOne_npc1;	//NPC１号のページワン宣言
	bool PageOne_npc2;	//NPC２号のページワン宣言
	bool PageOne_npc3;	//NPC３号のページワン宣言

	int priority;	//手番を決める優先度
	int field;		//場に出ているカードの枚数

	int pri;		//親を決めるための変数
	bool draw;		//カードが引けるかどうかを決めるためのフラグ
	bool finish;	//ゲーム終了フラグ

	int player;		//プレイヤーの手札の枚数
	bool flg_p;		//プレイヤーの手番が終わったかどうか

	int npc_1;		//NPC１号の手札の枚数
	bool flg_1;		//NPC１号の手番が終わったかどうか

	int npc_2;		//NPC２号の手札の枚数
	bool flg_2;		//NPC２号の手番が終わったかどうか

	int npc_3;		//NPC３号の手札の枚数
	bool flg_3;		//NPC３号の手番が終わったかどうか

	int p_pow;		//プレイヤーが出したカードの強さ
	int n1_pow;		//NPC１号が出したカードの強さ
	int n2_pow;		//NPC２号が出したカードの強さ
	int n3_pow;		//NPC３号が出したカードの強さ

	int lead;	//場のスートの基準にするカードの順番（基本は先頭（0番目））

	int p;		//プレイヤーの手札から p 番目にあるカード
	int n1;		//NPC１号の手札から n1 番目にあるカード
	int n2;		//NPC２号の手札から n2 番目にあるカード
	int n3;		//NPC３号の手札から n3 番目にあるカード

	int i;	//ループに使っている変数
	int r;	//ランダム用変数

	int n;	//クールタイム用変数

	int Mouse_X;	//マウスのX座標
	int Mouse_Y;	//マウスのY座標

	int Deck_X;		//山札のX座標
	int Deck_Y;		//山札のY座標

	int Field_X;		//場に出したカードのX座標
	int Field_Y;		//場に出したカードのY座標

	int Player_X;	//プレイヤーの手札のX座標
	int Player_Y;	//プレイヤーの手札のY座標

	int NPC1_X;		//NPC1の手札のX座標
	int NPC1_Y;		//NPC1の手札のY座標

	int NPC2_X;		//NPC2の手札のX座標
	int NPC2_Y;		//NPC2の手札のY座標

	int NPC3_X;		//NPC3の手札のX座標
	int NPC3_Y;		//NPC3の手札のY座標

	int color;	//デバッグ用
public:
	PageOne() {}

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

};

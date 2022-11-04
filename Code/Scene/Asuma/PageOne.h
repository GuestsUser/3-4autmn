#pragma once
#include <vector>

#define SWAP(type,a,b)          { type work = a; a = b; b = work; }

class Card {
public:
	Card(){}

	int card_w = 200;	//カード１枚の幅
	int card_h = 300;	//カード１枚の高さ

	int img;	//画像用の変数
	int num;	//カードの数字
	int suit;	//カードのスート(マーク)

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

class PageOne : public Card{
private:
	enum Priority {PLAYER, NPC1, NPC2, NPC3};	//親を決める優先度
	Priority pri;
	int priority[4];

	int card_type[54];	//画像用ハンドル
	
	Card Card_back;		//カードの裏面の情報
	Card Card_joker;	//ジョーカーの情報

	//Card Card_obj[4][13];		//全カードの情報
	std::vector<Card> Card_obj;		//全カードの情報
	std::vector<Card> Player_card;	//プレイヤーの持っているカードの情報

	std::vector<Card> Field_card;		//場に出ているカード

	std::vector<Card> NPC_card_1;		//NPC１号の持っているカードの情報
	std::vector<Card> NPC_card_2;		//NPC２号の持っているカードの情報
	std::vector<Card> NPC_card_3;		//NPC３号の持っているカードの情報

	int field;

	int par;

	int player;
	bool flg_p;

	int npc_1;
	bool flg_1;

	int npc_2;
	bool flg_2;

	int npc_3;
	bool flg_3;

	int i;
	int j;
	int r;
	int n;
	int c;

	int Mouse_X;	//マウスのX座標
	int Mouse_Y;	//マウスのY座標
	
	int Deck_X;		//山札のX座標
	int Deck_Y;		//山札のY座標

	int Player_X;		//プレイヤーの手札のX座標
	int Player_Y;		//プレイヤーの手札のY座標

	void random_shuffle(int* array, size_t size)
	{
		for (size_t i = size; i > 1; --i) {
			size_t a = i - 1;
			size_t b = rand() % i;
			SWAP(int, array[a], array[b]);
		}
	}

public:
	PageOne() {}

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

};

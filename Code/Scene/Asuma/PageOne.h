#pragma once
#include <list>
#include <vector>

class Card {
public:
	Card(){}

	int card_w = 200;	//カード１枚の幅
	int card_h = 300;	//カード１枚の高さ

	int img;	//画像用の変数
	int num;	//カードの数字
	int suit;	//カードのスート(マーク)

	bool Hit(int mx, int my, int cx, int cy, int cw, int ch) {
		if (mx > cx - (cw / 2) && mx < cx + (cw / 2) && my > cy - (ch / 2) && my < cy + (ch / 2)) {
			return true;
		}
		else {
			return false;
		}
	}

	//Card(画像、数値、スート、使用フラグ)
	Card(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};

class PageOne : public Card{
private:

	int card_type[54];	//画像用ハンドル
	
	Card Card_back;		//カードの裏面の情報
	Card Card_joker;	//ジョーカーの情報

	//Card Card_obj[4][13];		//全カードの情報
	std::vector<Card> Card_obj;		//全カードの情報
	std::list<Card> Player_card;	//プレイヤーの持っているカードの情報

	std::list<Card> NPC_card_1;		//NPC１号の持っているカードの情報
	std::list<Card> NPC_card_2;		//NPC２号の持っているカードの情報
	std::list<Card> NPC_card_3;		//NPC３号の持っているカードの情報

	int player;
	int npc_1;
	int npc_2;
	int npc_3;

	int i;
	int j;
	int r;
	int n;

	int Mouse_X;	//マウスのX座標
	int Mouse_Y;	//マウスのY座標
	
	int Deck_X;		//山札のX座標
	int Deck_Y;		//山札のY座標

	int Player_X;		//プレイヤーの手札のX座標
	int Player_Y;		//プレイヤーの手札のY座標

public:
	PageOne() {}

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

};

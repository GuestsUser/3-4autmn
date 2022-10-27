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

class PageOne {
private:

	int card_type[54];	//画像用ハンドル
	Card Card_back;		//カードの裏面の情報
	Card Card_joker;	//ジョーカーの情報

	Card Card_obj[4][13];		//全カードの情報
	//std::vector<Card> Card_obj;		//全カードの情報
	std::list<Card> Player_card;	//プレイヤーの持っているカードの情報

	int i;
	int j;
	int r;
	int n;

public:

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

};

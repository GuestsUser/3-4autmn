#pragma once
#include<random>
#include<algorithm>
#include <vector>
#include <list>

class C{
public:
	C() {}

	int img;	//画像用の変数
	int num;	//カードの数字
	int suit;	//カードのスート(マーク)

	//Card(画像、数値、スート、使用フラグ)
	C(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};
class CareerPoker {
private:
	int i, x, r, j;
	int rule;//ルールの画像
	int stage;//ステージの画像
	int T_cards[54];//山札
	int cards[5][13];//トランプ画像
	int hand[15];//手札
	int order[4];//誰から始めるか
	int pass;//ぱす
	int rev;//革命

	int card_type[54];	//画像用ハンドル

	C Card_back;		//カードの裏面の情報
	C Card_joker;	//ジョーカーの情報

	//Card Card_obj[4][13];		//全カードの情報
	std::vector<C> Card_obj;		//全カードの情報
	std::list<C> Player_card;	//プレイヤーの持っているカードの情報
	
public:
	void CP_Player_Initialize();
	void CP_Player_Finalize();
	void CP_Player_Update();
	void CP_Player_Draw();
	void deckmake();
	
};
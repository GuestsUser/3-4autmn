#pragma once
#include<random>
#include<algorithm>
#include<time.h>
#include <vector>
#include <list>
#define MAX (4U)

class C{
public:
	C() {}

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

	//Card(画像、数値、スート、使用フラグ)
	C(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};
class CareerPoker : public C{
private:
	int pri = 1;
	int i, x, r, j;
	int n;
	int rule;//ルールの画像
	int stage;//ステージの画像
	int cards[5][13];//トランプ画像
	int hand[15];//手札
	int Player_state;//switch文用のなんか

	int T_cards[54];//山札
	int order[4];//誰から始めるか
	int trash[15] = { 0 };//捨て札
	int rev = 0;//革命
	
	
	
	int pass;//ぱす
	int pc = -1; //最後に誰が出したかカウント
	int Mouse_X;	//マウスのX座標
	int Mouse_Y;    //マウスのY座標
	int Player_X;
	int Player_Y;
	int player;
	int card_type[54];	//画像用ハンドル


	C Card_back;		//カードの裏面の情報
	C Card_joker;	//ジョーカーの情報

	//Card Card_obj[4][13];		//全カードの情報
	std::vector<C> Card_obj;		//全カードの情報・画像の情報・マークの情報・数字の情報
	std::vector<C> Player_card;	//プレイヤーの持っているカードの情報
	std::vector<C> Field_card;  //場に出すため

public:
	void CP_Player_Initialize();
	void CP_Player_Finalize();
	void CP_Player_Update();
	void CP_Player_Draw();	
};

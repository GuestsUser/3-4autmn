#pragma once
#include "./../Scene.h"
#include<list>
#include<vector>

#define MAX (4U)

class Card {
public:

	int card_w = 200;	//カード１枚の幅
	int card_h = 300;	//カード１枚の高さ

	int img;	//画像用の変数
	int num;	//カードの数字
	int suit;	//カードのスート(マーク)


	int card_x;
	int card_y;

	Card() {}

	//カードごとの当たり判定（マウスX座標、マウスY座標、カードX座標、カードY座標、カードの幅、カードの高さ、カードの画像倍率）
	bool Hit(int mx, int my, int cx, int cy, int cw, int ch, double ExRate) {
		if (mx > cx - (cw * ExRate) / 2 && mx < cx + (cw * ExRate) / 2 && my > cy - (ch * ExRate) / 2 && my < cy + (ch * ExRate) / 2) {
			return true;
		}
		else {
			return false;
		}
	}

	//Set_Card(画像、数値、スート、カードごとのX座標、カードごとのY座標、使用フラグ(0:使ってない　1:使っている))
	Card(int i, int n, int s, int x, int y) {
		img = i;
		num = n;
		suit = s;

		card_x = x;
		card_y = y;

	}
};

class PageOne : public Card {
private:
	int card_type[54];	//画像用ハンドル
	int background;	//背景

	//std::vector <Card> Card_obj[53];		//全カードの情報(山札)
	//std::vector <Card> Player_card[53];	//プレイヤーの持っているカードの情報

	//std::vector <Card> Field_card[4];		//場に出ているカード
	//std::vector <Card> Cemetery_card[53];		//場に出ているカード

	//std::vector <Card> NPC_card_1[53];		//NPC１号の持っているカードの情報
	//std::vector <Card> NPC_card_2[53];		//NPC２号の持っているカードの情報
	//std::vector <Card> NPC_card_3[53];		//NPC３号の持っているカードの情報
	
	std::list <Card> Card_obj;		//全カードの情報(山札)
	std::list <Card> Player_card;	//プレイヤーの持っているカードの情報

	std::list <Card> Field_card;		//場に出ているカード
	std::list <Card> Cemetery_card;		//場に出ているカード

	std::list <Card> NPC_card_1;		//NPC１号の持っているカードの情報
	std::list <Card> NPC_card_2;		//NPC２号の持っているカードの情報
	std::list <Card> NPC_card_3;		//NPC３号の持っているカードの情報

	std::list <Card>::iterator itr;
	std::list <Card>::iterator f_itr;

	std::list <Card>::iterator p_itr;
	std::list <Card>::iterator n1_itr;
	std::list <Card>::iterator n2_itr;
	std::list <Card>::iterator n3_itr;

	//スートUI
	int Spade;	//スペード
	int Heart;	//ハート
	int Diamond;//ダイヤ
	int Club;	//クラブ
	int free;	//何でもよい

	//ポーズUI
	int Pause_Button;
	int Pause_Back;
	int Pause_Continue;
	int Pause_Select;
	int pause_continue[2];
	int pause_select[2];

	bool Pause_Flg;
	int Now_key;
	int Old_key;

	//リザルト背景
	int Result;

	//各種SE
	int pass_SE;
	int pageone_SE;
	int card_SE_1;	//カードを引く
	int card_SE_2;	//カードを出す
	int card_SE_3;	//カードを移動する
	int win_SE;	//勝利時のSE

	int Cursor_SE;	//カーソルのSE
	int Select_SE;	//決定ボタンのSE

	int BGM;	//BGM保存用変数

	bool OneShot;	//鳴ったかどうか（一回だけ鳴らすのに使う）

	Scene* select;

	int Card_back;		//カードの裏面の情報
	int card_img;	//カード画像
	//int card_num;	//カード枚数

	int PlayerCrown;		//王冠のアイコン画像
	int NPC1_Icon;		//王冠のアイコン画像
	int NPC2_Icon;		//王冠のアイコン画像
	int NPC3_Icon;		//王冠のアイコン画像

	int Player_Pass_Icon;		//パスのアイコン画像
	int NPC1_Pass_Icon;		//パスのアイコン画像
	int NPC2_Pass_Icon;		//パスのアイコン画像
	int NPC3_Pass_Icon;		//パスのアイコン画像

	int Player_PageOne_Icon;	//ページワン宣言のアイコン画像
	int NPC1_PageOne_Icon;	//ページワン宣言のアイコン画像
	int NPC2_PageOne_Icon;	//ページワン宣言のアイコン画像
	int NPC3_PageOne_Icon;	//ページワン宣言のアイコン画像

	bool Player_Pass_Flg;		//プレイヤーパスフラグ
	bool NPC1_Pass_Flg;		//NPC1パスフラグ
	bool NPC2_Pass_Flg;		//NPC2パスフラグ
	bool NPC3_Pass_Flg;		//NPC3パスフラグ

	bool PageOne_flg;	//ページワン宣言をしたかどうか(true:した	false:してない)

	bool PageOne_player;	//プレイヤーのページワン宣言
	bool PageOne_npc1;	//NPC１号のページワン宣言
	bool PageOne_npc2;	//NPC２号のページワン宣言
	bool PageOne_npc3;	//NPC３号のページワン宣言

	int priority;	//手番を決める優先度
	int field;		//場に出ているカードの枚数
	int cemetery;	//使用したカードの枚数

	int pri;		//親を決めるための変数(フィールドで一番強いカードが記録される)
	bool draw;		//カードが引けるかどうかを決めるためのフラグ(false:引けない　true:引ける)

	bool Player_setup;		//プレイヤー準備フラグ
	bool NPC1_setup;		//NPC1準備フラグ
	bool NPC2_setup;		//NPC2準備フラグ
	bool NPC3_setup;		//NPC3準備フラグ

	bool finish;	//ゲーム終了フラグ
	bool reset;	//盤面リセットフラグ

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

	void PageOne_Initialize(Scene* scene);
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();
};

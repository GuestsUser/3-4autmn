#pragma once
#define Board_Xsize 7 //パネルの横のマスの数
#define Board_Ysize 6 //パネルの縦のマスの数
#define Coin_Space 0 //コインが入っていない場所
#define Coin_Player 1 //プレイヤーのコインがある場所
#define Coin_CPU 2 //CPUのコインがある場所

class CF_Player {
private:
	int CF_Back; //背景
	int CF_Panel; //パネル
	int CF_Board[Board_Xsize][Board_Ysize]; //パネルの情報の二次元配列
	int CF_PCoin; //プレイヤーのコイン
	int CF_CCoin; //CPUのコイン
	int CF_Yajirusi; //矢印
	int i,j,k; //for分の変数
	int Yajirusi_Col[7]; //矢印の色
	int Mouse_X; //マウスのX座標
	int Mouse_Y; //マウスのY座標
	int Player_X; //プレイヤーのX座標
	int Player_Y; //プレイヤーのY座標
	int PlayUser; //今プレイしているコインの所持者
	
	float yadd; //重力加速度
	float Yajirusi_Move; //矢印のアニメーションの値
	float Yajirusi_Y; //矢印のY座標
	float FallCount;

	bool Mouse_Push; //マウスの左クリックがされたかのフラグ
	bool CF_Clear; //コネクトフォーをクリアしたかのフラグ
	bool CF_Draw; //コネクトフォーで引き分けをしたかのフラグ
	
public:
	void CF_Player_Initialize();
	void CF_Player_Finalize();
	void CF_Player_Update();
	void CF_Player_Draw();

	void Coin_Fall();
	void Board_Init();
	void ChangeTurn(int *PlayUser);

	int ClearCheck(int board[Board_Xsize][Board_Ysize], int x, int y);
	int DrawCheck(int board[Board_Xsize][Board_Ysize]);

};
//
//extern CF_Player cf_player;
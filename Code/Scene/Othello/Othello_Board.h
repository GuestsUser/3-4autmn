#pragma once
#include "DxLib.h"
#include "./../Scene.h"
#define PB 10			// ボードの配列の数
#define MAP_SIZE 66		// ボードの1マス当たりの大きさ


class Othello_Board {
private:
	Scene* Parent;

	int PutCheckImage;	// かっこの画像を入れる用の変数
	int ResultImage;
	int WinLoseImage[3];
	int Black;
	int White;

	int Pause_Button;
	int Pause_Back;
	int Pause_Continue;
	int Pause_Select;

	int pause_continue[2];
	int pause_select[2];

	int BGM;		// BGM用の変数
	int PutSE;		// 石を置くときのSE用の変数
	int PassSE;		// パスされたときのSE用の変数
	int PauseClickSE;
	int PauseSelectSE;

	int BlackCr;	// 黒色をセットしておく用の変数
	int WhiteCr;	// 白色をセットしておく用の変数
	int GreenCr;	// 緑色をセットしておく用の変数
	int RedCr;
	int Cr;

	int OrderNum;	// 手番を決める数を入れる変数
	int BlackNum;	// 黒石の数を入れる変数
	int WhiteNum;	// 白石の数を入れる変数
	int TimeCount;	// 時間を測る用の変数
	int CheckNum;	// 
	int ReturnNum;	// 
	int ReturnNumMax;		// 
	int Board_X, Board_Y;	//　board[Board_X][Board_Y] みたいな感じで、ボードのマスを入れる変数
	int RandomNum;	// 
	int Player;		// プレイヤーかどうかを判定するための変数
	int PutPlace_X, PutPlace_Y;		// 置いた場所を保存する変数
	int BoardShift_X, BoardShift_Y;
	
	int Mouse_X;		// マウスのX座標のポインタを入れる用変数
	int Mouse_Y;		// マウスのY座標のポインタを入れる用変数
	int OldKey;
	int nowKey;

	bool DrawFlag;		// カーソルがマスの上に来た時に赤く描画していいか判定
	bool CheckFlag;		// 
	bool PassFlag;		// パスされたかどうかを判定
	bool EndFlag;		// 終了条件を満たしているかどうかを判定
	bool RandomFlag;	// ランダムに値を振ったかどうか
	bool CornerFlag;	// 角が取れるかどうかを判定
	bool PauseFlg;		// ポーズ画面を開いているかどうか

public:
	int Square_X;		// マウスから読みとったX座標を、MAP_SIZEで割った値を入れた変数
	int Square_Y;		// マウスから読み取ったY座標を、MAP_SIZEで割った値を入れた変数
	int Board[PB][PB];	// ボードのマップチップ情報を入れる用変数
	int ScoreBoard[PB][PB];

	void Othello_Board_Initialize(Scene* scene);	// 初期化
	void Othello_Board_Finalize();					// 終了処理
	void Othello_Board_Update();					// 更新
	void Othello_Board_Draw();						// 描画

	void Init_OthelloBoard(int board[PB][PB]);		// ボードを初期化
	void Print_OthelloBoard(int board[PB][PB]);		// ボードを表示

	void CursorOn_OthelloBoard();		// 置ける場所にカーソルが来たマスを赤くする

	int CursorPutOnCheck(int board[PB][PB], int p, int q, int enemy, int player);			// 選択したマスに石を置いて石をひっくり返す
	int CPUPutOnCheck(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);	// CPUが選択したマスに石を置いてひっくり返す

	int PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);	// 置ける場所がないか探す

	int BlackPutCheck(int d, int e);			// 黒石が置ける場所があるかどうか調べる
	int BlackPut();								// 黒石を置く
	int BlackPutCPU(int d, int e);				// 黒石がCPUの場合の置ける場所があるかどうか調べる関数
	int BoardSearchBlack(int board[PB][PB]);	// 黒石を置けるようにする処理の関数
	int CPUBlack(int board[PB][PB], int scoreboard[PB][PB]);			// 黒石がCPUの場合の黒石を置く処理


	int WhitePutCheck(int d, int e);			// 白石が置ける場所があるかどうか調べる
	int WhitePut();								// 白石を置く
	int WhitePutCPU(int d, int e);				// 白石がCPUの場合の置ける場所があるかどうか調べる関数
	int BoardSearchWhite(int board[PB][PB]);	// 白石を置けるようにする処理の関数	
	int CPUWhite(int board[PB][PB], int scoreboard[PB][PB]);			// 白石がCPUの場合の置く処理

	void BoardSearchBWNumber(int board[PB][PB]);	// 黒・白石が、現在どれだけあるか調べる関数


	int EndGame(int board[PB][PB]);				// ゲームの終了条件を満たしたら終了する

	void RandomOrder();							// 先手・後手を決める関数

	void BoardScore(int board[PB][PB]);			//　静的評価を合計する関数
};

extern Othello_Board* OB;
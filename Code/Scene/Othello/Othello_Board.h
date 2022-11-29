#pragma once
//#include "./Othello_Player.h"
#include "DxLib.h"
#include "./../Scene.h"
#define PB 10
#define MAP_SIZE 66

//
class Othello_Board {
private:
	Scene* Parent;

	int PutCheckImage;	// かっこの画像を入れる用の変数

	int BGM;		// BGM用の変数
	int PutSE;		// 石を置くときのSE用の変数
	int PassSE;		// パスされたときのSE用の変数

	int BlackCr;	// 黒色をセットしておく用の変数
	int WhiteCr;	// 白色をセットしておく用の変数
	int GreenCr;	// 緑色をセットしておく用の変数
	int Cr;

	int OrderNum;	// 手番を決める数を入れる変数
	int BlackNum;	// 黒石の数を入れる変数
	int WhiteNum;	// 白石の数を入れる変数
	int TimeCount;	// 時間を測る用の変数
	int CheckNum;	// 
	int ReturnNum;
	int ReturnNumMax;
	int Board_X, Board_Y;
	int RandomNum;
	int Player;

	bool DrawFlag;
	bool CheckFlag;
	bool PassFlag;
	bool EndFlag;
	bool RandomFlag;
	bool CornerFlag;

public:
	int Mouse_X;
	int Mouse_Y;
	int Square_X;
	int Square_Y;
	int Board[PB][PB];

	void Othello_Board_Initialize(Scene* scene);
	void Othello_Board_Finalize();
	void Othello_Board_Update();
	void Othello_Board_Draw();

	void Init_OthelloBoard(int board[PB][PB]);
	void Print_OthelloBoard(int board[PB][PB]);

	void CursorOn_OthelloBoard();

	int CursorPutOnCheck(int board[PB][PB], int p, int q, int enemy, int player);
	int CPUPutOnCheck(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);



	int PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);

	int BlackPutCheck(int d, int e);
	int BlackPut();
	int BlackPutCPU(int d, int e);
	int BoardSearchBlack(int board[PB][PB]);


	int WhitePutCheck(int d, int e);
	int WhitePut();
	int WhitePutCPU(int d, int e);
	int BoardSearchWhite(int board[PB][PB]);


	void BoardSearchBWNumber(int board[PB][PB]);

	int CPUWhite(int board[PB][PB]);
	int CPUBlack(int board[PB][PB]);
	int EndGame(int board[PB][PB]);

	int RandomOrder();
	/*
	* プレイヤーが黒色（先手）の場合、白色をＣＰＵにしたい
	* プレイヤーが白色（後手）の場合、黒色をＣＰＵにしたい
	*/

};

extern Othello_Board* OB;
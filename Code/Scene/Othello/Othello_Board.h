#pragma once
//#include "./Othello_Player.h"
#include "DxLib.h"
#define PB 10
#define MAP_SIZE 66

//extern const int  PB = 10;
//extern const int  MAP_SIZE = 66;
//
class Othello_Board {
private:
	int BlackCr;
	int GreenCr;
	int WhiteCr;


	int OrderNum;	// è”Ô‚ğŒˆ‚ß‚é”‚ğ“ü‚ê‚é•Ï”
	int BlackNum;	// •Î‚Ì”‚ğ“ü‚ê‚é•Ï”
	int WhiteNum;	// ”’Î‚Ì”‚ğ“ü‚ê‚é•Ï”
	int TimeCount;
	int CheckNum;
	int ReturnNum;
	int ReturnNumMax;
	int Board_X, Board_Y;

	bool DrawFlag;
	bool CheckFlag;
	bool PassFlag;
	bool EndFlag;
public:
	int Mouse_X;
	int Mouse_Y;
	int Square_X;
	int Square_Y;
	int Board[PB][PB];

	void Othello_Board_Initialize();
	void Othello_Board_Finalize();
	void Othello_Board_Update();
	void Othello_Board_Draw();

	void Init_OthelloBoard(int board[PB][PB]);
	void Print_OthelloBoard(int board[PB][PB]);

	void CursorOn_OthelloBoard();

	int CursorPutOnCheck(int board[PB][PB], int p, int q, int enemy, int player);
	int PutOnCheck(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);


	int PutOnCheck2(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);
	int put();


	int PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);

	int BlackPutCheck(int d, int e);
	int BlackPut();
	//void BoardSearchBlack(int board[PB][PB]);
	int BoardSearchBlack(int board[PB][PB]);


	int WhitePutCheck(int d, int e);
	int WhitePut();
	int WhitePutCPU(int d, int e);
	//void BoardSearchWhite(int board[PB][PB]);
	int BoardSearchWhite(int board[PB][PB]);


	void BoardSearchBWNumber(int board[PB][PB]);

	int ReturnNumWhite(int board[PB][PB]);
	int EndGame(int board[PB][PB]);

};

extern Othello_Board* OB;
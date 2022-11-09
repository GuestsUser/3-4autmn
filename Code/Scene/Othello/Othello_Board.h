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
	int CheckNum;

	int OrderNum;	// è”Ô‚ğŒˆ‚ß‚é”‚ğ“ü‚ê‚é•Ï”
	int BlackNum;	// •Î‚Ì”‚ğ“ü‚ê‚é•Ï”
	int WhiteNum;	// ”’Î‚Ì”‚ğ“ü‚ê‚é•Ï”

	bool DrawFlag;
	bool CheckFlag;
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

	int PutOnCheck(int board[PB][PB], int p, int q, int enemy, int player);

	int PutOnCheck2(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);
	int put();


	int PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);

	int BlackPutCheck(int d, int e);
	int BlackPut();
	void BoardSearchBlack(int board[PB][PB]);

	int WhitePutCheck(int d, int e);
	int WhitePut();
	void BoardSearchWhite(int board[PB][PB]);

	void BoardSearchBWNumber(int board[PB][PB]);


	int BWPut(int board[PB][PB], int p, int q, int enemy, int player);

};

extern Othello_Board* OB;
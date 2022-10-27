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
	//void Check(int board[PB][PB]);
	int Check2(int board[PB][PB], int p, int q, int enemy, int player);
	//int Check3();
	void Check3();
	void BlackOn_OthelloBoard(int board[PB][PB], int p, int q, int enemy, int player);
};

extern Othello_Board* OB;
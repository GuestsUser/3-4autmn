#pragma once
#define PB 10
class Othello_Board {
private:
	const int MAP_SIZE = 66;
	//const int MAP_SIZE_X = 65;
	//const int MAP_SIZE_Y = 65;
	//const int B = 10;
	int BlackCr;
	int GreenCr;
	int WhiteCr;
	int Board[PB][PB];
public:
	void Othello_Board_Initialize();
	void Othello_Board_Finalize();
	void Othello_Board_Update();
	void Othello_Board_Draw();
	void Init_DataBoard(int board[PB][PB]);
	void Print_DataBoard(int board[PB][PB]);
};
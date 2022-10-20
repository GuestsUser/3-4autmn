#pragma once
#include "DxLib.h"
#include "./Othello_Board.h"



class Othello_Player {
private:
	//Othello_Board* OB;
	int BlackCr;
	int WhiteCr;
	int Mouse_X;
	int Mouse_Y;
	int Player_X;
	int Player_Y;

public:
	bool Flag;
	void Othello_Plyaer_Initialize();
	void Othello_Player_Finalize();
	void Othello_Player_Update();
	void Othello_Player_Draw();
	//void SetOB(Othello_Board* ob);
};

extern Othello_Player* OP;
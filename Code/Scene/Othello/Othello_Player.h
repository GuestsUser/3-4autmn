#pragma once


class Othello_Player {
private:
	int Board;
	const int MAP_SIZE_X = 65;
	const int MAP_SIZE_Y = 65;
	int BlackCr;
	int GreenCr;

public:
	void Othello_Plyaer_Initialize();
	void Othello_Player_Finalize();
	void Othello_Player_Update();
	void Othello_Player_Draw();
	void init_DataMap(int Board);
};
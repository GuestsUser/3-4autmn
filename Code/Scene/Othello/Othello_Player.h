#pragma once

class Othello_Player {
private:
	int BlackCr;
	int WhiteCr;
	int Mouse_X;
	int Mouse_Y;
	int Player_X;
	int Player_Y;
public:
	void Othello_Plyaer_Initialize();
	void Othello_Player_Finalize();
	void Othello_Player_Update();
	void Othello_Player_Draw();
};
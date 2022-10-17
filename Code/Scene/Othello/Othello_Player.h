#pragma once

class Othello_Player {
private:
	int BlackCr;
	int WhiteCr;

public:
	void Othello_Plyaer_Initialize();
	void Othello_Player_Finalize();
	void Othello_Player_Update();
	void Othello_Player_Draw();
};
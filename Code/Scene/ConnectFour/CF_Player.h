#pragma once

class CF_Player {
private:
	int CF_Back;
	int CF_Panel;
public:
	void CF_Player_Initialize();
	void CF_Player_Finalize();
	void CF_Player_Update();
	void CF_Player_Draw();
};
//
//extern CF_Player cf_player;
#pragma once

class CF_Player {
private:
	int CF_Back;
	int CF_Panel;
	int CF_PCoin;
	int CF_CCoin;
	int CF_Yajirusi;
	int i;
	
	float Yajirusi_Move;
	float Yajirusi_Y;

	int Yajirusi_Col[7];
	int Mouse_X; //�}�E�X��X���W
	int Mouse_Y; //�}�E�X��Y���W
	int Player_X; //�v���C���[��X���W
	int Player_Y; //�v���C���[��Y���W
public:
	void CF_Player_Initialize();
	void CF_Player_Finalize();
	void CF_Player_Update();
	void CF_Player_Draw();
};
//
//extern CF_Player cf_player;
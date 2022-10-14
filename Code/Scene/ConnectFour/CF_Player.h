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
	int Mouse_X; //マウスのX座標
	int Mouse_Y; //マウスのY座標
	int Player_X; //プレイヤーのX座標
	int Player_Y; //プレイヤーのY座標
public:
	void CF_Player_Initialize();
	void CF_Player_Finalize();
	void CF_Player_Update();
	void CF_Player_Draw();
};
//
//extern CF_Player cf_player;
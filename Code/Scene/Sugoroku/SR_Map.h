#pragma once
#include "./../Scene.h"
class SR_Map {
private:
	int MassX[63];	/*�}�X�̑���*/
	int MassY[63];	/*�}�X�̑���*/
	int MassX2[65];	/*�}�X�̑���*/
	int MassY2[65];	/*�}�X�̑���*/
	int MassX3[65];	/*�}�X�̑���*/
	int MassY3[65];	/*�}�X�̑���*/
	int MassX4[65];	/*�}�X�̑���*/
	int MassY4[65];	/*�}�X�̑���*/
	int Player1;
	int Player2;
	int Player3;
	int Player4;
	int game;
	int x, y;
	int i;
public:
	SR_Map();
	void Update();
	void Draw();
};

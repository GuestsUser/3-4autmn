#pragma once
#include "./../Scene.h"
class SR_Map {
private:
	int MassX[65];	/*�}�X�̑���*/
	int MassY[65];	/*�}�X�̑���*/
	int Player1;
	int Player2;
	int x, y;
public:
	SR_Map();
	void Update();
	void Draw();
};
#pragma once

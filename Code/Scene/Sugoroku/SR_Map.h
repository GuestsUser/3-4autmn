#pragma once
#include "./../Scene.h"
class SR_Map {
private:
	int MassX[65];	/*マスの総数*/
	int MassY[65];	/*マスの総数*/
	int Player1;
	int Player2;
	int x, y;
public:
	SR_Map();
	void Update();
	void Draw();
};
#pragma once

#pragma once
#include "./../Scene.h"
class SR_Saikoro;
class SR_Map {
private:
	SR_Saikoro* saikoro;
	int MassX[65];	/*マスの総数*/
	int MassY[65];	/*マスの総数*/
	int Player1;
	int Player2;
	int x, y;
	int i;
public:
	void Update();
	void Draw();
};

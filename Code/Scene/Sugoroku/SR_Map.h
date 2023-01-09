#pragma once
#include "./../Scene.h"
class SR_Map {
private:
	int MassX[63];	/*マスの総数*/
	int MassY[63];	/*マスの総数*/
	int MassX2[65];	/*マスの総数*/
	int MassY2[65];	/*マスの総数*/
	int MassX3[65];	/*マスの総数*/
	int MassY3[65];	/*マスの総数*/
	int MassX4[65];	/*マスの総数*/
	int MassY4[65];	/*マスの総数*/
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

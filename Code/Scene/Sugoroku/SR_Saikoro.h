#pragma once
#include "./../Scene.h"

class SR_Saikoro : public Scene {
private:
	int SR_Saikoro1[6];	/*サイコロ画像１*/
	int SR_Saikoro2[6];	/*サイコロ画像２*/
	int SR_MAP;
	int i;
	int y;
	int d;
	bool Shuffle = false;
	int count;
	int Dice1;
	int Dice2;
	int Sum;
public:
	SR_Saikoro();
	void Update();
	void Draw();
	void Saikoro();
	void Dice();
};

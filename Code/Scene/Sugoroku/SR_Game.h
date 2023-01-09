#pragma once
#include "./../Scene.h"

class SR_Saikoro;
class SR_Map;

class SR_Game : public Scene {
private:
	SR_Saikoro* saikoro;
	SR_Map* map;
	int SR_MAP;	/*”wŒi‰æ‘œ*/
	int SR_BGM;
public:
	SR_Game();
	void Update();
	void Draw();
};

#pragma once
#include "./../Scene.h"
class SR_Saikoro;
class SR_Map;

class SR_Game : public Scene {
private:
	SR_Saikoro* saikoro;
	SR_Map* map;
	int SR_MAP;	/*�w�i�摜*/
public:
	SR_Game();
	void Update();
	void Draw();
};

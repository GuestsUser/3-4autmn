#pragma once
#include "./../Scene.h"
class SR_Saikoro;

class SR_Game : public Scene {
private:
	SR_Saikoro* saikoro;
	int SR_MAP;	/*”wŒi‰æ‘œ*/
public:
	SR_Game();
	void Update();
	void Draw();
};

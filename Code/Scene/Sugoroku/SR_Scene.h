#pragma once
#include "./../Scene.h"
class SR_Game;
class SR_Saikoro;
class Pause;

class SR_Scene : public Scene {
private:
	SR_Saikoro* player;
public:
	SR_Scene();
	~SR_Scene();
	void Update();
	void Draw();

};

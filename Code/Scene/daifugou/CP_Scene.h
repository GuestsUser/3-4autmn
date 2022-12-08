#pragma once
#include"./../Scene.h"

class CareerPoker;
//class CP;
class CP_Scene :public Scene {
private:
	CareerPoker* Player;
	//CP* Player;
public:
	CP_Scene();
	~CP_Scene();
	void Update();
	void Draw();
};
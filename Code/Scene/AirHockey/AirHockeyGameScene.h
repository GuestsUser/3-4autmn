#pragma once
#include "./../Scene.h"

class AirHockey_Scene;

class Scene_AirHockey : public Scene {
private:
	AirHockey_Scene* C_Air;
public:
	Scene_AirHockey();
	~Scene_AirHockey();
	void Update();
	void Draw();
};
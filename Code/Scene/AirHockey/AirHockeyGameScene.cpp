#include "./../Code/Scene/AirHockey/AirHockeyGameScene.h"
#include "AirHockey.h"


Scene_AirHockey::Scene_AirHockey() {
	C_Air = new AirHockey_Scene();

	C_Air->AirHockey_Initialize();
}

Scene_AirHockey::~Scene_AirHockey() {
	delete C_Air;
}

void Scene_AirHockey::Update() {
	C_Air->AirHockey_Update();
}

void Scene_AirHockey::Draw() {
	C_Air->AirHockey_Draw();
}
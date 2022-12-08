#include"SR_Scene.h"
#include"SR_Saikoro.h"
#include "SR_Game.h"

SR_Scene::SR_Scene() {
	SR_Saikoro::SR_Saikoro(this);
}
SR_Scene::	~SR_Scene() {
	delete player;
}

void SR_Scene::Update() {
	player->SR_Saikoro::Update();
}
void SR_Scene::Draw() {
	player->SR_Saikoro::Draw();
}


#include"Scene_ConnectFour.h"
#include"CF_Player.h"

Scene_ConnectFour::Scene_ConnectFour() {
	player = new CF_Player();
	player->CF_Player_Initialize(this);
}
Scene_ConnectFour::	~Scene_ConnectFour() {
	delete player;
}

void Scene_ConnectFour::Update() {
	player->CF_Player_Update(); 
}
void Scene_ConnectFour::Draw() {
	player->CF_Player_Draw();
}


#include"CP_Scene.h"
#include"CP_Player.h"
#include"daifugou.h"
CP_Scene::CP_Scene(){
	Player = new CareerPoker();
	Player->CP_Player_Initialize();
}
CP_Scene::~CP_Scene() {
	delete Player;
}
void CP_Scene::Update() {
	Player->CP_Player_Update();
}

void CP_Scene::Draw() {
	Player->CP_Player_Draw();
}
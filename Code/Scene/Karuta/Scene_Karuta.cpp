#include"Scene_Karuta.h"
#include"Karu_Game.h"

Scene_Karuta::Scene_Karuta() {
	game = new Karu_Game();
	game->Karu_Game_Initialize(this);
}
Scene_Karuta::	~Scene_Karuta() {
	delete game;
}

void Scene_Karuta::Update() {
	game->Karu_Game_Update();
}
void Scene_Karuta::Draw() {
	game->Karu_Game_Draw();
}


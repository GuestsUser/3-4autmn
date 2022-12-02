#include"Scene_PageOne.h"
#include"PageOne.h"

Scene_PageOne::Scene_PageOne() {
	po_player = new PageOne();
	po_player->PageOne_Initialize(this);
}

Scene_PageOne::	~Scene_PageOne() {
	delete po_player;
}

void Scene_PageOne::Update() {
	po_player->PageOne_Update();
}
void Scene_PageOne::Draw() {
	po_player->PageOne_Draw();
}


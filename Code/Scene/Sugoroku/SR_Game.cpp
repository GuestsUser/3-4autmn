#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Map.h"
#include "SR_Game.h"
#include "SR_Saikoro.h"

SR_Game::SR_Game() {
	SR_MAP = LoadGraph("Resource/image/SR_MAP.png");
	saikoro = new SR_Saikoro();
	map = new SR_Map();
}

void SR_Game::Update() {
	saikoro->Update();
	map->Update();
}

void SR_Game::Draw() {
	DrawGraph(0, 0, SR_MAP, false);
	saikoro->Draw();	
	map->Draw();
}
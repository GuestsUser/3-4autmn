#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "MapLoad.h"
#include "SR_Game.h"
#include "SR_Saikoro.h"

SR_Game::SR_Game() {
	SR_MAP = LoadGraph("Resource/image/SR_MAP.png");
	saikoro = new SR_Saikoro();
}

void SR_Game::Update() {
	saikoro->Update();
}

void SR_Game::Draw() {
	DrawGraph(0, 0, SR_MAP,false);
	saikoro->Draw();
}
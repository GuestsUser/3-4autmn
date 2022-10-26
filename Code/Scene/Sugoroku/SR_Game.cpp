#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "MapLoad.h"
#include "SR_Game.h"
#include "SR_Saikoro.h"

SR_Game::SR_Game() {
	SR_MAP = LoadGraph("Resource/image/SR_MAP.png");
}

void SR_Game::Update() {
	&SR_Saikoro::Update;
}

void SR_Game::Draw() {
	//DrawGraph(0, 0, SR_MAP,true);
}
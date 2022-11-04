#include "SR_Map.h"
#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"

SR_Map::SR_Map() {
	MassX[0] = 50; MassY[0] = 500;
	Player1 = LoadGraph("Resource/image/SR_Player1.png");
}

void SR_Map::Update() {
}

void SR_Map::Draw() {
	DrawGraph(MassX[0], MassY[0], Player1, true);
	//DrawGraph(100,100, Player1, true);
}

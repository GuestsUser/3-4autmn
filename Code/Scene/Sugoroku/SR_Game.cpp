#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Map.h"
#include "SR_Game.h"
#include "SR_Saikoro.h"

SR_Game::SR_Game(){
	SR_BGM = LoadSoundMem("Resource/bgm/SR_BGM.wav"); //ƒQ[ƒ€’†‚ÌBGM
	SR_MAP = LoadGraph("Resource/image/SR_MAP.png");
	saikoro = new SR_Saikoro(this);
	map = new SR_Map();
//	PlaySoundMem(SR_BGM, DX_PLAYTYPE_BACK);

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
#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "MapLoad.h"
#include "SR_Title.h"
#include "SR_Game.h"
#include "SR_Saikoro.h"

SR_Title::SR_Title() {
	Rule = LoadGraph("Resource/image/SR_Rule.png");	/*画像読み込み*/
}

void SR_Title::Update() {
	if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //Aボタン(緑ボタン)が押された瞬間
		SetNext((new SR_Game));
	}
	Draw();
}

void SR_Title::Draw() {
	DrawGraph(0, 0, Rule, false);
	DrawString(0, 0, "双六ルール説明画像", GetColor(255, 255, 255));
}
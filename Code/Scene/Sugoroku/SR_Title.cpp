#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "MapLoad.h"
#include "SR_Title.h"

SR_Title::SR_Title() {
	Rule = LoadGraph("./../../Scene/SR_Title/SR_TitleImages/Rule.png");	/*画像読み込み*/
}

void SR_Title::Update() {
	if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //Aボタン(緑ボタン)が押された瞬間
		//SetNext((new 00000));
	}
	Draw();
}

void SR_Title::Draw() {
	DrawGraph(0, 0, Rule, false);
	DrawString(0, 0, "双六ルール説明画像", GetColor(255, 255, 255));
}
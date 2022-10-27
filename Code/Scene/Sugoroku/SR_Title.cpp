#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "MapLoad.h"
#include "SR_Title.h"
#include "SR_Game.h"
#include "SR_Saikoro.h"

SR_Title::SR_Title() {
	Rule = LoadGraph("Resource/image/SR_Rule.png");	/*�摜�ǂݍ���*/
}

void SR_Title::Update() {
	if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //A�{�^��(�΃{�^��)�������ꂽ�u��
		SetNext((new SR_Game));
	}
	Draw();
}

void SR_Title::Draw() {
	DrawGraph(0, 0, Rule, false);
	DrawString(0, 0, "�o�Z���[�������摜", GetColor(255, 255, 255));
}
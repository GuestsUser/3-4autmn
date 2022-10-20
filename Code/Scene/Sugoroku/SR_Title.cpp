#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "MapLoad.h"
#include "SR_Title.h"

SR_Title::SR_Title() {
	Rule = LoadGraph("./../../Scene/SR_Title/SR_TitleImages/Rule.png");	/*�摜�ǂݍ���*/
}

void SR_Title::Update() {
	if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //A�{�^��(�΃{�^��)�������ꂽ�u��
		//SetNext((new 00000));
	}
	Draw();
}

void SR_Title::Draw() {
	DrawGraph(0, 0, Rule, false);
	DrawString(0, 0, "�o�Z���[�������摜", GetColor(255, 255, 255));
}
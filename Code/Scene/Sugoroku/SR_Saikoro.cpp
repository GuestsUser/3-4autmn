#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Map.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"
#include <stdio.h>
#include <stdlib.h>

SR_Saikoro::SR_Saikoro() {
	LoadDivGraph("Resource/image/SR_Saikoro1.png", 6, 6, 1, 75, 75, SR_Saikoro1, true);	/*�T�C�R���摜�ǂݍ���*/
	LoadDivGraph("Resource/image/SR_Saikoro2.png", 6, 6, 1, 75, 75, SR_Saikoro2, true);	/*�T�C�R���摜�ǂݍ���*/
	y = 0, d = 0, i = 0;	/*�e��ϐ�������*/
	count = 0;
	SRand(123456); // �����̏����l��123456�ɐݒ肷��
	Player1sum = 0;
}

void SR_Saikoro::Update() {
	count++;
	GetMousePoint(&MouseX, &MouseY);
	//if (Click == true) {	/*�T�C�R���摜�N���b�N�ۃt���O*/
	if (MouseX >= 1020 && MouseY >= 580 && MouseX <= 1250 && MouseY <= 700) {
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*�������N���b�N������*/
			Shuffle = true;	/*�V���b�t���t���O��ON��*/
		}
		else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {
			Player1sum += Sum;
			Shuffle = false;
		}
	}
	if ((count / 4) % 2 == 0&& Shuffle == true) {
		y = GetRand(5);
		d = GetRand(5);
	}
	Sum = y + d + 2;	/*�T�C�R���̍��v�l*/
}

void SR_Saikoro::Draw() {
	DrawString(0, 0, "�o�Z���[�������摜", GetColor(255, 255, 255));
	DrawFormatString(900, 600, GetColor(255, 255, 255), "%d", Sum);
	/*DrawGraph(1050, 600, SR_Saikoro1[y], true);
	DrawGraph(1140, 600, SR_Saikoro2[d], true);*/
	DrawFormatString(700, 600, GetColor(255, 255, 255), "%d", count);
	DrawFormatString(500, 600, GetColor(255, 255, 255), "%d", y);
	DrawFormatString(600, 600, GetColor(255, 255, 255), "%d", d);
	DrawFormatString(400, 600, GetColor(255, 255, 255), "%d", Player1sum);
}
#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Map.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"
#include "SR_Result.h"
#include <stdio.h>
#include <stdlib.h>

int Player1sum;
int Player2sum;
int Player3sum;
int Player4sum;

SR_Saikoro::SR_Saikoro() {
	LoadDivGraph("Resource/image/SR_Saikoro1.png", 6, 6, 1, 75, 75, SR_Saikoro1, true);	/*�T�C�R���摜�ǂݍ���*/
	LoadDivGraph("Resource/image/SR_Saikoro2.png", 6, 6, 1, 75, 75, SR_Saikoro2, true);	/*�T�C�R���摜�ǂݍ���*/
	y = 0, d = 0, i = 0;	/*�e��ϐ�������*/
	count = 0;
	countdiff = 0;
	countmi = 0;
	num = 1;
	Click = true;
	SRand(count); // �����̏����l��123456�ɐݒ肷��

	Player1sum = 0;
	Player2sum = 0;
	Player3sum = 0;
	Player4sum = 0;
}

void SR_Saikoro::Update() {
	count++;
	GetMousePoint(&MouseX, &MouseY);/*�}�E�X���W�擾�i���j*/
	/*�S�[��������*/
	if (Player1sum >= 64|| Player2sum >= 64 || Player3sum >= 64 || Player4sum >= 64) {
		Goal();	/*�܂����g�͂Ȃ�*/
		Player1sum = 64; Player2sum = 64; Player3sum = 64; Player4sum = 64;
	}

	/*���X�^�[�g�܂��ɏ������*/
	if (Player1sum == 24 || Player2sum == 24 || Player3sum == 24 || Player4sum == 24) {
		Restart();
	}

	switch (num) {
		case 1 :	/*�v���C���[�̎�*/
			//DrawString(500, 600, "Player�̃^�[��", GetColor(0, 0, 0));
			if (Click == true) {
				if (MouseX >= 1020 && MouseY >= 580 && MouseX <= 1250 && MouseY <= 700 && Whoisplay == true) {
					if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*�������N���b�N������*/
						Shuffle = true;	/*�V���b�t���t���O��ON��*/
					}
					else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {
						Player1sum += Sum;
						Shuffle = false;
						countdiff = count;
						Whoisplay = false;
					}
				}
			}
			if (count - countdiff == 100 && countdiff != 0) { countdiff = count;  num = 2;  Whoisplay = true; }	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 2:
			//DrawString(500, 600, "AI1�̃^�[��", GetColor(0, 0, 0));
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;
				Shuffle = true;
				Sumflg = true;
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player2sum += Sum;
				}
			}
			if (count - countdiff == 400 && countdiff != 0) { countdiff = count;  num = 3; p = 0;  Sumflg = false; Whoisplay = true;}	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 3:
			//DrawString(500, 600, "AI2�̃^�[��", GetColor(0, 0, 0));
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;
				Shuffle = true;
				Sumflg = true;
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player3sum += Sum;
				}
			}
			if (count - countdiff == 400 && countdiff != 0) { countdiff = count;  num = 4; p = 0; Sumflg = false; Whoisplay = true;}	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 4:
			//DrawString(500, 600, "AI3�̃^�[��", GetColor(0, 0, 0));
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;
				Shuffle = true;
				Sumflg = true;
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player4sum += Sum;
				}
			}
			if (count - countdiff == 400 && countdiff != 0) { countdiff = 0;  num = 1; p = 0; Sumflg = false; Whoisplay = true;}	/*count��100�i�߂Ύ��̃^�[��*/
			break;
	}

	if ((count / 4) % 2 == 0&& Shuffle == true) {
		y = GetRand(5);
		d = GetRand(5);
	}
	Sum = y + d + 2;	/*�T�C�R���̍��v�l*/
}

void SR_Saikoro::Draw() {
	DrawGraph(1050, 600, SR_Saikoro1[y], true);
	DrawGraph(1140, 600, SR_Saikoro2[d], true);
  
	switch (num) {
	case 1:	/*�v���C���[�̎�*/
		if (Whoisplay == true) { DrawString(500, 600, "Player�̃^�[��", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "�v���C���[��%d�i��", Sum); }
		else if(Shuffle == true){ DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		
		break;
	case 2:
		if (Whoisplay == true) { DrawString(500, 600, "Player2�̃^�[��", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) {DrawFormatString(500,600,GetColor(0, 0, 0),"AI1��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 3:
		if (Whoisplay == true) { DrawString(500, 600, "Player3�̃^�[��", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "AI2��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 4:
		if (Whoisplay == true) { DrawString(500, 600, "Player4�̃^�[��", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "AI3��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 5:
		if (Goalflg == true) {
			DrawString(500, 600, "Goal!!", GetColor(0, 0, 0));
		}
		break;
	}

}

void SR_Saikoro::SR_Enemy1() {	/*AI1*/
	
	Shuffle = true;
}
void SR_Saikoro::SR_Enemy2() {	/*AI2*/
	Shuffle = true;
}
void SR_Saikoro::SR_Enemy3() {	/*AI3*/
	Shuffle = true;
}

void SR_Saikoro::Restart() {
	Player1sum -= 24;
	Player2sum -= 24;
	Player3sum -= 24;
	Player4sum -= 24;
}

void SR_Saikoro::Goal() {
	num = 5;
	Goalflg = true;
//	SetNext((new SR_Result));
}
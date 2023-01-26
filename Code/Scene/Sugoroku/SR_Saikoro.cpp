#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Map.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"
#include "SR_Result.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include<iostream>
#include "./../Title/Scene_Select.h"

using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;

int Player1sum;
int Player2sum;
int Player3sum;
int Player4sum;

SR_Saikoro::SR_Saikoro(Scene*scene) {
	parent = scene;
	LoadDivGraph("Resource/image/SR_Saikoro1.png", 6, 6, 1, 75, 75, SR_Saikoro1, true);	/*�T�C�R���摜�ǂݍ���*/
	LoadDivGraph("Resource/image/SR_Saikoro2.png", 6, 6, 1, 75, 75, SR_Saikoro2, true);	/*�T�C�R���摜�ǂݍ���*/
	SR_BGM = LoadSoundMem("Resource/bgm/SR_BGM.wav"); //�Q�[������BGM
	SR_saikoro = LoadSoundMem("Resource/se/SR_saikoro.wav"); //�Q�[������BGM
	SR_idou = LoadSoundMem("Resource/se/SR_idou.wav"); //�Q�[������BGM
	SR_resaikoro = LoadSoundMem("Resource/se/SR_cursor.wav"); //�T�C�R����BGM

	SR_GOAL = LoadGraph("Resource//image/SR_GOAL.png");
	Pause_Button = LoadGraph("Resource/image/PauseButton.png");
	Pause_Back = LoadGraph("Resource/image/PauseBack.png");
	Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
	Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);
	y = 0, d = 0, i = 0;	/*�e��ϐ�������*/
	count = 0;
	countdiff = 0;
	countmi = 0;
	num = 1;
	Click = true;
	//SRand(count); // �����̏����l��count�ɐݒ肷��
	srand((unsigned int)time(NULL));

	Player1sum = 0;
	Player2sum = 0;
	Player3sum = 0;
	Player4sum = 0;
	
}

void SR_Saikoro::Update() {
	if (count == 1) {
		PlaySoundMem(SR_BGM, DX_PLAYTYPE_LOOP);

		ChangeVolumeSoundMem(155 * 80 / 100, SR_BGM);
	}
	GetMousePoint(&MouseX, &MouseY);/*�}�E�X���W�擾�i���j*/
	if (PauseFlg == false) {
		count++;
		/*�S�[��������*/
		if (Player1sum >= 62 || Player2sum >= 62 || Player3sum >= 62 || Player4sum >= 62) {
			if (Player1sum >= 62) { Player1sum = 62; }
			else if (Player2sum >= 62) { Player2sum = 62; }
			else if (Player3sum >= 62) { Player3sum = 62; }
			else if (Player4sum >= 62) { Player4sum = 62; }
			Goal();	/*�܂����g�͂Ȃ�*/
		}
		array[0] = Player1sum; array[1] = Player2sum; array[2] = Player3sum; array[3] = Player4sum;
		if (Shuffle == true) {
			if (count % 4 == 0) {
				PlaySoundMem(SR_resaikoro, DX_PLAYTYPE_BACK);
			}
			//PlaySoundFile("Resource/se/SR_saikoro.wav", DX_PLAYTYPE_BACK);
		}
		switch (num) {
		case 1:	/*�v���C���[�̃^�[��*/
			current = 1;
			if (Click == true) {
				Replay = false;
				if (MouseX >= 1020 && MouseY >= 580 && MouseX <= 1250 && MouseY <= 700 && Whoisplay == true) {
					if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*�������N���b�N������*/
						Shuffle = true;	/*�V���b�t���t���O��ON��*/
					}
					else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true && move == false) {	//�V���b�t�����~�߂�
						countdiff = count;
						move = true; Shuffle = false; 
						Whoisplay = false; Replay = false;	/*�t���O�֘A*/
					}
				}
				if (move == true && Back == false) {
					if (o < Sum) {
						//if ((count / 40) % 2 == 0) {
						if (count % 6 ==0) {
							PlaySoundMem(SR_idou, DX_PLAYTYPE_BACK);
							Player1sum += 1;
							o += 1;
						}
					}
				}
				else if (move == true && Back == true) {
					if (o < Sum) {
						if (count % 6 == 0) {
							PlaySoundMem(SR_idou, DX_PLAYTYPE_BACK);
							Player1sum -= 1;
							o += 1;
						}
					}
					else {
						Back = false;
					}
				}
				if (o - Sum == 0) {
					if (Player1sum == 22) { Restart(); }
					if (Player1sum == 12 || Player1sum == 48) { Plus(); text = 1; }
					if (Player1sum == 8 || Player1sum == 27 ||Player1sum == 40) { Replay = true; }
					if (Player1sum == 19 ) { Replay = true; Back = true; }
					if (Player1sum == 34) { Minus(); }
				}
			}
			if (Replay == true && count - countdiff == 100 && countdiff != 0) { num = 6; countdiff = count; Whoisplay = true;  move = false; o = 0; }
			else if (Replay == false && count - countdiff == 100 && countdiff != 0) { countdiff = count;  num = 2;  Whoisplay = true; move = false; o = 0; }	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 2:
			current = 2;
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;	/*�e�L�X�g���点�Ȃ��悤�ɂ���*/
				Shuffle = true;		/*�T�C�R�����V���b�t������*/
				Sumflg = true;		/*�T�C�R���̍��v�l�𑫂�*/
			}
			else if(count - countdiff > 301){	/*cont300�𒴂�����*/
				Shuffle = false;	/*�V���b�t�����~�߂�*/
				move = true;
				Replay = false;
				p += 1;
			}
			if (move == true && Back == false) {
				if (o < Sum) {
					if (count % 6 == 0) {
						PlaySoundMem(SR_idou, DX_PLAYTYPE_BACK);
						Player2sum += 1;
						o += 1;
					}
				}
			}
			else if (move == true && Back == true) {
				if (o < Sum) {
					if (count % 6 == 0) {
						PlaySoundMem(SR_idou, DX_PLAYTYPE_BACK);
						Player2sum -= 1;
						o += 1;
					}
				}
				else {
					Back = false;
				}
			}
			if (o - Sum == 0) {
				if (Player2sum == 8 || Player2sum == 27 || Player2sum == 40) { Replay = true; }	/*�������v���C�܂��ɏ������*/
				if (Player2sum == 12 || Player2sum == 48) { Plus(); }
				if (Player2sum == 22) { Restart(); }
				if (Player2sum == 19) { Replay = true; Back = true; }
				if (Player2sum == 34) { Minus(); }
			}
			if (Replay == true && count - countdiff > 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true; move = false; o = 0; }		/**/
			else if (Replay == false && count - countdiff > 400 && countdiff != 0) { countdiff = count;  num = 3; p = 0;  Sumflg = false; Whoisplay = true; move = false; o = 0; }	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 3:
			current = 3;
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false; Shuffle = true; Sumflg = true;
			}
			else if (count - countdiff > 301) {	/*cont300�𒴂�����*/
				Shuffle = false;	/*�V���b�t�����~�߂�*/
				move = true;
				Replay = false;
				p += 1;
			}
			if (move == true && Back == false) {
				if (o < Sum) {
					if (count % 6 == 0) {
						PlaySoundMem(SR_idou, DX_PLAYTYPE_BACK);
						Player3sum += 1;
						o += 1;
					}
				}
			}
			else if (move == true && Back == true) {
				if (o < Sum) {
					if (count % 6 == 0) {
						PlaySoundMem(SR_idou, DX_PLAYTYPE_BACK);
						Player3sum -= 1;
						o += 1;
					}
				}
				else {
					Back = false;
				}
			}
			if (o - Sum == 0) {
				if (Player3sum == 8 || Player3sum == 27 || Player3sum == 40) { Replay = true; }
				if (Player3sum == 12 || Player3sum == 48) { Plus(); }
				if (Player3sum == 22) { Restart(); }
				if (Player3sum == 34) { Minus(); }
				if (Player3sum == 19) { Replay = true; Back = true; }
			}
			if (Replay == true && count - countdiff > 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true; move = false;  o = 0; }
			else if (Replay == false && count - countdiff > 400 && countdiff != 0) { countdiff = count;  num = 4; p = 0; Sumflg = false; Whoisplay = true; move = false; o = 0; }	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 4:
			current = 4;
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;Shuffle = true;Sumflg = true;
			}
			else if (count - countdiff > 301) {	/*cont300�𒴂�����*/
				Shuffle = false;	/*�V���b�t�����~�߂�*/
				move = true;
				Replay = false;
				p += 1;
			}
			if (move == true && Back == false) {
				if (o < Sum) {
					if (count % 6 == 0) {
						PlaySoundMem(SR_idou, DX_PLAYTYPE_BACK);
						Player4sum += 1;
						o += 1;
					}
				}
			}
			else if (move == true && Back == true) {
				if (o < Sum) {
					if (count % 6 == 0) {
						PlaySoundMem(SR_idou, DX_PLAYTYPE_BACK);
						Player4sum -= 1;
						o += 1;
					}
				}
				else {
					Back = false;
				}
			}
			if (o - Sum == 0) {
				if (Player4sum == 8 || Player4sum == 27 || Player4sum == 40) { Replay = true; }
				if (Player4sum == 12 || Player4sum == 48) { Plus(); }
				if (Player4sum == 22) { Restart(); }
				if (Player4sum == 34) { Minus(); }
				if (Player4sum == 19) { Replay = true; Back = true; }
			}
			if (Replay == true && count - countdiff > 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true; move = false; o = 0; }
			else if (Replay == false && count - countdiff > 400 && countdiff != 0) { countdiff = 0;  num = 1; p = 0; Sumflg = false; Whoisplay = true; move = false; o = 0; }	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 5:
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*�������N���b�N������*/
				StopSoundMem(SR_BGM);
				parent->SetNext(new Scene_Select());
			}
			break;
		case 6:
			if (current == 1) { countdiff = 0;  num = 1; p = 0; Sumflg = false; Whoisplay = true; }
			else if (current == 2) { countdiff = count;  num = 2;  Whoisplay = true; move = false; o = 0; }
			else if (current == 3) { countdiff = count;  num = 3; p = 0;  Sumflg = false; Whoisplay = true; }
			else if (current == 4) { countdiff = count;  num = 4; p = 0; Sumflg = false; Whoisplay = true; }
			break;
		}

		if ((count / 4) % 2 == 0 && Shuffle == true) {
			y = GetRand(5);
			d = GetRand(5);
		}
		Sum = y + d + 2;	/*�T�C�R���̍��v�l*/
		if ((20 <= MouseX && MouseX <= 200 && 25 <= MouseY && MouseY <= 105)) {
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PULL) {
				PauseFlg = true;
			}
		}

	}else {
		SR_Pose_Update();
	}
}

void SR_Saikoro::Draw() {
	Sort();
	DrawGraph(1050, 600, SR_Saikoro1[y], true);
	DrawGraph(1140, 600, SR_Saikoro2[d], true);
	switch (num) {
	case 1:	/*�v���C���[�̎�*/
		if (Whoisplay == true && Shuffle == false) {
			if (Player1sum == 8 || Player1sum == 19 ||Player1sum == 27 || Player1sum == 40) {
				DrawString(454, 620, "������x�T�C�R����U��", GetColor(0, 0, 0));
			}
			else if (Player1sum == 12 || Player1sum == 48) {
				DrawString(454, 620, "4�i��", GetColor(0, 0, 0));
			}
			else if (Player1sum == 22) {
				DrawString(454, 620, "�X�^�[�g�n�_�ɖ߂�", GetColor(0, 0, 0));
			}
			else if (Player1sum == 34) {
				DrawString(454, 620, "4�߂�", GetColor(0, 0, 0));
			}
			else {
				DrawString(454, 620, "Player1�̃^�[��", GetColor(0, 0, 0));
			}
		}
		else if (Shuffle == false && Whoisplay == false && Back == false) { DrawFormatString(454, 620, GetColor(0, 0, 0), "Player1��%d�i��", Sum); }
		else if (Shuffle == true ) { DrawString(454, 620, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 2:
		if (Whoisplay == true && Shuffle == false) {
			if (Player2sum == 8 || Player2sum == 19 || Player2sum == 27 || Player2sum == 40) {
				DrawString(454, 620, "������x�T�C�R����U��", GetColor(0, 0, 0));
			}
			else if (Player2sum == 12 || Player2sum == 48) {
				DrawString(454, 620, "4�i��", GetColor(0, 0, 0));
			}
			else if (Player2sum == 22) {
				DrawString(454, 620, "�X�^�[�g�n�_�ɖ߂�", GetColor(0, 0, 0));
			}
			else if (Player2sum == 34) {
				DrawString(454, 620, "4�߂�", GetColor(0, 0, 0));
			}
			else {
				DrawString(454, 620, "Player2�̃^�[��", GetColor(0, 0, 0));
			}
		}
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(454, 620, GetColor(0, 0, 0), "Player2��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(454, 620, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 3:
		if (Whoisplay == true && Shuffle == false) {
			if (Player3sum == 8 || Player3sum == 19 || Player3sum == 27 || Player3sum == 40) {
				DrawString(454, 620, "������x�T�C�R����U��", GetColor(0, 0, 0));
			}
			else if (Player3sum == 12 || Player3sum == 48) {
				DrawString(454, 620, "4�i��", GetColor(0, 0, 0));
			}
			else if (Player3sum == 22) {
				DrawString(454, 620, "�X�^�[�g�n�_�ɖ߂�", GetColor(0, 0, 0));
			}
			else if (Player3sum == 34) {
				DrawString(454, 620, "4�߂�", GetColor(0, 0, 0));
			}
			else {
				DrawString(454, 620, "Player3�̃^�[��", GetColor(0, 0, 0));
			}
		}
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(454, 620, GetColor(0, 0, 0), "Player3��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(454, 620, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 4:
		if (Whoisplay == true && Shuffle == false) {
			if (Player4sum == 8 || Player4sum == 19 || Player4sum == 27 || Player4sum == 40) {
				DrawString(454, 620, "������x�T�C�R����U��", GetColor(0, 0, 0));
			}
			else if (Player4sum == 12 || Player4sum == 48) {
				DrawString(454, 620, "4�i��", GetColor(0, 0, 0));
			}
			else if (Player4sum == 22) {
				DrawString(454, 620, "�X�^�[�g�n�_�ɖ߂�", GetColor(0, 0, 0));
			}
			else if (Player4sum == 34) {
				DrawString(454, 620, "4�߂�", GetColor(0, 0, 0));
			}
			else {
				DrawString(454, 620, "Player4�̃^�[��", GetColor(0, 0, 0));
			}
		}
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(454, 620, GetColor(0, 0, 0), "Player4��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(454, 620, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 5:
		if (Goalflg == true) {
			DrawGraph(0, 0, SR_GOAL, true);
		}
		StopSoundFile();
		if (Player1sum == 62) { DrawString(500, 360, "Player1�̏����I�I", GetColor(0, 0, 0)); }
		else if (Player2sum == 62) { DrawString(500, 360, "Player2�̏����I�I", GetColor(0, 0, 0)); }
		else if (Player3sum == 62) { DrawString(500, 360, "Player3�̏����I�I", GetColor(0, 0, 0)); }
		else if (Player4sum == 62) { DrawString(500, 360, "Player4�̏����I�I", GetColor(0, 0, 0)); }
		break;
	}

	//�|�[�Y�{�^��
	DrawRotaGraph(110, 65, 0.9, 0, Pause_Button, TRUE);
	if (PauseFlg == true) {
		DrawRotaGraph(650, 380, 1.15, 0, Pause_Back, TRUE);
		if (450 <= MouseX && MouseX <= 850 && 320 <= MouseY && MouseY <= 440) {
			if (nowKey == KEY_HOLD) {
				DrawRotaGraph(650, 380, 0.9, 0, pause_continue[1], TRUE);
			}
			else {
				DrawRotaGraph(650, 380, 1.0, 0, pause_continue[1], TRUE);
			}
		}
		else {
			DrawRotaGraph(650, 380, 1.0, 0, pause_continue[0], TRUE);
		}
		if (450 <= MouseX && MouseX <= 850 && 470 <= MouseY && MouseY <= 590) {
			if (nowKey == KEY_HOLD) {
				DrawRotaGraph(650, 530, 0.9, 0, pause_select[1], TRUE);
			}
			else {
				DrawRotaGraph(650, 530, 1.0, 0, pause_select[1], TRUE);
			}
		}
		else {
			DrawRotaGraph(650, 530, 1.0, 0, pause_select[0], TRUE);
		}
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

void SR_Saikoro::Plus() {
	DrawString(500, 600,"Player�͒ǉ��łS�i��", GetColor(0, 0, 0));
	if (current == 1) { Player1sum += 4; }
	else if (current == 2) { Player2sum += 4; }
	else if (current == 3) { Player3sum += 4; }
	else if (current == 4) { Player4sum += 4; }
}

void SR_Saikoro::Minus() {
	if (current == 1) { Player1sum -= 5; }
	else if (current == 2) { Player2sum -= 5;}
	else if (current == 3) { Player3sum -= 5;}
	else if (current == 4) { Player4sum -= 5;}
}

void SR_Saikoro::ReDice() {
}

void SR_Saikoro::Restart() {
	if (current == 1 && Player1sum == 22) { Player1sum -= 22; }
	else if (current == 2 && Player2sum == 22) { Player2sum -= 22; }
	else if (current == 3 && Player3sum == 22) { Player3sum -= 22; }
	else if (current == 4 && Player4sum == 22) { Player4sum -= 22; }
}

void SR_Saikoro::Goal() {
	num = 5;
	Goalflg = true;
	//SetNext((new SR_Result));
}

void SR_Saikoro::Frontback() {
	//if (array[3] == 24) { /*�����N���Ȃ�*/; }

	//if (array[2] == 24) {
	//	if (current == 1) {
	//		if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {	/*�T�C�R�����o���������߂�}�X�p�iback�t���O������j*/
	//			array[3] -= Sum;
	//			Shuffle = false;
	//			countdiff = count;
	//			Whoisplay = false;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//	else {
	//		Shuffle = false;
	//		if (Sumflg == true && p == 0) {
	//			p += 1;
	//			array[3] -= Sum;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//}

	//if (array[1] == 24) { 
	//	if (current == 1) {
	//		if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {	/*�T�C�R�����o���������߂�}�X�p�iback�t���O������j*/
	//			array[3] -= Sum;
	//			Shuffle = false;
	//			countdiff = count;
	//			Whoisplay = false;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//	else {
	//		Shuffle = false;
	//		if (Sumflg == true && p == 0) {
	//			p += 1;
	//			array[3] -= Sum;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//}

	//if (array[0] == 24) { 
	//	if (current == 1) {
	//		if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {	/*�T�C�R�����o���������߂�}�X�p�iback�t���O������j*/
	//			array[3] -= Sum;
	//			Shuffle = false;
	//			countdiff = count;
	//			Whoisplay = false;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//	else {
	//		Shuffle = false;
	//		if (Sumflg == true && p == 0) {
	//			p += 1;
	//			array[3] -= Sum;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//}

	//if (array[3] == 24) { DrawString(500, 550, "�����N���Ȃ�", GetColor(0, 0, 0)); }

	//if (array[2] == 24) {
	//	array[3] -= 5;
	//}

	//if (array[1] == 24) {
	//	array[2] -= 5;
	//}

	//if (array[0] == 24) {
	//	array[1] -= 5;
	//}

	/*for (v = 0; v < 4; v++) {}*/
}

void SR_Saikoro::Sort() {
	sort(array, array + 4);
}
void SR_Saikoro::SR_Pose_Update() {
	GetMousePoint(&MouseX, &MouseY);
	nowKey = key->GetKeyState(REQUEST_MOUSE_LEFT); //���݂̃}�E�X���{�^���̓��͏�Ԃ̎擾
	// �|�[�Y�{�^������������|�[�Y��ʂ��J���t���O��true�ɂ��� /
		if ((20 <= MouseX && MouseX <= 200 && 25 <= MouseY && MouseY <= 105) || ((450 <= MouseX && MouseX <= 850 && 320 <= MouseY && MouseY <= 440) && PauseFlg)) {
			//PauseFlg = true;
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {
				//PauseFlg = true;
				PauseFlg = !PauseFlg;
				//pose = true;
			}
		}
	if (PauseFlg) {

		if (450 <= MouseX && MouseX <= 850 && 470 <= MouseY && MouseY <= 590) {
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
				//StopSoundMem(CF_GameBGM);
				parent->SetNext(new Scene_Select());
				StopSoundMem(SR_BGM);
			}
		}
	}
	OldKey = nowKey; //�O�ɓ��͂��Ă����L�[�������͂��Ă����L�[�ɏ㏑������
}
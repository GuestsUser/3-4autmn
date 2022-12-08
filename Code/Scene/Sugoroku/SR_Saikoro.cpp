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

using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;

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
	//SRand(count); // �����̏����l��count�ɐݒ肷��
	srand((unsigned int)time(NULL));

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
		if (Player1sum >= 64) { Player1sum = 64; }
		else if (Player2sum >= 64) { Player2sum = 64; }
		else if (Player3sum >= 64) { Player3sum = 64; }
		else if (Player4sum >= 64) { Player4sum = 64; }
		Goal();	/*�܂����g�͂Ȃ�*/
	}
	/*���X�^�[�g�܂��ɏ������*/
	/*if (Player1sum == 22 || Player2sum == 22 || Player3sum == 22 || Player4sum == 22) {
		Restart();
	}*/
	/*�v���X4�}�X�Ɏ~�܂����� 12 50*/
	if (Player1sum == 12 || Player2sum == 12 || Player3sum == 12 || Player4sum == 12 || Player1sum == 50 || Player2sum == 50 || Player3sum == 50 || Player4sum == 50) {
		Plus();	/*+4����*/
	}
	/*�}�C�i�X4�}�X�Ɏ~�܂����� 36*/
	if (Player1sum == 36 || Player2sum == 36 || Player3sum == 36 || Player4sum == 36) {
		Minus();	/*-4����*/
	}
	/*�O�̃v���C���[��߂�*/
	if (Player1sum == 24 || Player2sum == 24 || Player3sum == 24 || Player4sum == 24) {
		Frontback();
		//if (array[3] == 24) { DrawString(500, 550, "�����N���Ȃ�", GetColor(0, 0, 0)); }
		//DrawString(500, 550, "�����N���Ȃ�", GetColor(0, 0, 0));
	}
	array[0] = Player1sum;array[1] = Player2sum;array[2] = Player3sum;array[3] = Player4sum;
	switch (num) {
		case 1 :	/*�v���C���[�̃^�[��*/
			current = 1;
			if (Click == true) {
				Replay = false;
				if (MouseX >= 1020 && MouseY >= 580 && MouseX <= 1250 && MouseY <= 700 && Whoisplay == true) {
					if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*�������N���b�N������*/
						Shuffle = true;	/*�V���b�t���t���O��ON��*/
					}
					else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true && Back == true && move == false) {	/*�T�C�R�����o���������߂�}�X�p�iback�t���O������j*/
						Player1sum -= Sum;
						Shuffle = false;
						countdiff = count;
						Whoisplay = false;
						Replay = false;
						Back = false;
					}
					else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true && move == false) {
						Player1sum += Sum;
						move = true;
						Shuffle = false;
						countdiff = count;
						Whoisplay = false;
						Replay = false;
					}
				}
				/*if (move == true) {
					if (o < Sum) {
						if ((count / 4) % 2 == 0) {
							Player1sum += 1;
							o += 1;
						}
					}
				}*/
				if (Player1sum == 8 || Player1sum == 30) {Replay = true;}
				if (Player1sum == 19) { Replay = true; Back = true; }
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
			else if(Back == true){	/*Back�t���O��true�̎�*/
				Shuffle = false;	/*�V���b�t�����~�߂�*/
				if (Sumflg == true && p == 0) {		
					p += 1;
					Player2sum -= Sum;		/*�T�C�R���̍��v�l�𑫂�*/
					Replay = false;
					Back = false;
				}
			}
			else {	/*cont300�𒴂�����*/
				Shuffle = false;	/*�V���b�t�����~�߂�*/
				if (Sumflg == true && p == 0) {
					p += 1;
					Player2sum += Sum;		/*�T�C�R���̍��v�l�𑫂�*/
					Replay = false;
				}
			}
			if (Player2sum == 8 || Player2sum == 30) {	/*�������X�^�[�g�܂��ɏ������*/
				Replay = true;		/*���X�^�[�g�t���Oture*/
			}
			if (Player2sum == 19) { Replay = true; Back = true; }
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true;}		/**/
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = count;  num = 3; p = 0;  Sumflg = false; Whoisplay = true;  }	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 3:
			current = 3;
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;
				Shuffle = true;
				Sumflg = true;
			}
			else if(Back == true){
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player3sum -= Sum;
					Replay = false;
					Back = false;
				}
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player3sum += Sum;
					Replay = false;
				}
			}
			if (Player3sum == 8 || Player3sum == 30) {
				Replay = true;
			}
			if (Player3sum == 19) { Replay = true; Back = true; }
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true;  }
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = count;  num = 4; p = 0; Sumflg = false; Whoisplay = true;}	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 4:
			current = 4;
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;
				Shuffle = true;
				Sumflg = true;
			}
			else if(Back == true){
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player4sum -= Sum;
					Replay = false;
					Back = false;
				}
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player4sum += Sum;
					Replay = false;
				}
			}
			if (Player4sum == 8 || Player4sum == 30) {
				Replay = true;
			}
			if (Player4sum == 19) { Replay = true; Back = true; }
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true; }
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = 0;  num = 1; p = 0; Sumflg = false; Whoisplay = true;  }	/*count��100�i�߂Ύ��̃^�[��*/
			break;
		case 5:

			break;
		case 6:
			if (current == 1) { num = 1; }
			else if (current == 2) { num = 2; }
			else if (current == 3) { num = 3; }
			else if (current == 4) { num = 4; }
			break;
	}

	if ((count / 4) % 2 == 0&& Shuffle == true) {
		y = GetRand(5);
		d = GetRand(5);
	}

	/********************�f�o�b�O�p**************************/
	//if ((count / 4) % 2 == 0 && Shuffle == true) {
	//	y = GetRand(0);
	//	//d = GetRand(1);
	//}
	/********************�f�o�b�O�p**************************/

	/*if ((count / 4) % 2 == 0) {
		if (Player1sum <= Sum) {
			Player1sum += 1;
		}
		else if (Player2sum <= Sum) {
			Player2sum += 1;
		}
		else if (Player3sum <= Sum) {
			Player3sum += 1;
		}
		else if (Player4sum <= Sum) {
			Player4sum += 1;
		}
	}*/
	Sum = y + d + 2;	/*�T�C�R���̍��v�l*/
}

void SR_Saikoro::Draw() {
	Sort();
	DrawGraph(1050, 600, SR_Saikoro1[y], true);
	DrawGraph(1140, 600, SR_Saikoro2[d], true);
	//DrawFormatString(300, 650, GetColor(255, 255, 255), "%d", array[3]);
	//DrawFormatString(400, 650, GetColor(255, 255, 255), "%d", array[2]);
	//DrawFormatString(500, 650, GetColor(255, 255, 255), "%d", array[1]);
	//DrawFormatString(600, 650, GetColor(255, 255, 255), "%d", array[0]);
	//switch (num) {
	//case 1:	/*�v���C���[�̎�*/
	//	if (Whoisplay == true) { DrawString(500, 600, "Player�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "�v���C���[��%d�i��", Sum); }
	//	else if(Shuffle == true){ DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	
	//	break;
	//case 2:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player2�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) {DrawFormatString(500,600,GetColor(0, 0, 0),"Player2��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 3:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player3�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player3��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 4:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player4�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player4��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 5:
	//	if (Goalflg == true) {
	//		DrawString(500, 600, "Goal!!", GetColor(0, 0, 0));
	//	}
	//	break;
	//}
	//if (array[3] == 24) { DrawString(500, 550, "�����N���Ȃ�", GetColor(0, 0, 0)); }
	//case 1:	/*�v���C���[�̎�*/
	//	if (Whoisplay == true) { DrawString(500, 600, "Player�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "�v���C���[��%d�i��", Sum); }
	//	else if(Shuffle == true){ DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	
	//	break;
	//case 2:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player2�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) {DrawFormatString(500,600,GetColor(0, 0, 0),"Player2��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 3:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player3�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player3��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 4:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player4�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player4��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 5:
	//	if (Goalflg == true) {
	//		DrawString(500, 600, "Goal!!", GetColor(0, 0, 0));
	//	}
	//	break;
	//}
	//if (array[3] == 24) { DrawString(500, 550, "�����N���Ȃ�", GetColor(0, 0, 0)); }
	//switch (num) {
	//case 1:	/*�v���C���[�̎�*/
	//	if (Whoisplay == true) { DrawString(500, 600, "Player�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "�v���C���[��%d�i��", Sum); }
	//	else if(Shuffle == true){ DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	
	//	break;
	//case 2:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player2�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) {DrawFormatString(500,600,GetColor(0, 0, 0),"Player2��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 3:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player3�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player3��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 4:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player4�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player4��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 5:
	//	if (Goalflg == true) {
	//		DrawString(500, 600, "Goal!!", GetColor(0, 0, 0));
	//	}
	//	break;
	//}
	//if (array[3] == 24) { DrawString(500, 550, "�����N���Ȃ�", GetColor(0, 0, 0)); }
	//case 1:	/*�v���C���[�̎�*/
	//	if (Whoisplay == true) { DrawString(500, 600, "Player�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "�v���C���[��%d�i��", Sum); }
	//	else if(Shuffle == true){ DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	
	//	break;
	//case 2:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player2�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) {DrawFormatString(500,600,GetColor(0, 0, 0),"Player2��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 3:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player3�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player3��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 4:
	//	if (Whoisplay == true) { DrawString(500, 600, "Player4�̃^�[��", GetColor(0, 0, 0)); }
	//	if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player4��%d�i��", Sum); }
	//	else if (Shuffle == true) { DrawString(500, 600, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
	//	break;
	//case 5:
	//	if (Goalflg == true) {
	//		DrawString(500, 600, "Goal!!", GetColor(0, 0, 0));
	//	}
	//	break;
	//}
	//if (array[3] == 24) { DrawString(500, 550, "�����N���Ȃ�", GetColor(0, 0, 0)); }


	switch (num) {
	case 1:	/*�v���C���[�̎�*/
		if (Whoisplay == true && Shuffle == false) { DrawString(484,620,"Player�̃^�[��", GetColor(0, 0, 0)); }
		else if (Shuffle == false && Whoisplay == false) { DrawFormatString(484, 620, GetColor(0, 0, 0), "�v���C���[��%d�i��", Sum); }
		else if(Shuffle == true){ DrawString(484, 620, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		if (Player1sum) {

		}
		break;
	case 2:
		if (Whoisplay == true) { DrawString(484, 620, "Player2�̃^�[��", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) {DrawFormatString(484, 620, GetColor(0, 0, 0),"Player2��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(484, 620, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 3:
		if (Whoisplay == true) { DrawString(484, 620, "Player3�̃^�[��", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(484, 620, GetColor(0, 0, 0), "Player3��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(484, 620, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 4:
		if (Whoisplay == true) { DrawString(484, 620, "Player4�̃^�[��", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(484, 620, GetColor(0, 0, 0), "Player4��%d�i��", Sum); }
		else if (Shuffle == true) { DrawString(484, 620, "�T�C�R���R���R��", GetColor(0, 0, 0)); }
		break;
	case 5:
		if (Goalflg == true) {
			DrawString(484, 620, "Goal!!", GetColor(0, 0, 0));
		}
		if(Player1sum == 64){ DrawString(500, 200, "Player1�̏����I�I", GetColor(0, 0, 0)); }
		else if(Player2sum == 64){ DrawString(500, 200, "Player2�̏����I�I", GetColor(0, 0, 0)); }
		else if(Player3sum == 64){ DrawString(500, 200, "Player3�̏����I�I", GetColor(0, 0, 0)); }
		else if(Player4sum == 64){ DrawString(500, 200, "Player4�̏����I�I", GetColor(0, 0, 0)); }
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
//void SR_Saikoro::SR_Pose_Update() {
//
//	nowKey = key->GetKeyState(REQUEST_MOUSE_LEFT); //���݂̃}�E�X���{�^���̓��͏�Ԃ̎擾
//	// �|�[�Y�{�^������������|�[�Y��ʂ��J���t���O��true�ɂ��� /
//	if ((20 <= MouseX && MouseX <= 200 && 25 <= MouseY && MouseY <= 105) || ((450 <= MouseX && MouseX <= 850 && 320 <= MouseY && MouseY <= 440) && PauseFlg)) {
//		//PauseFlg = true;
//		if (OldKey != KEY_FREE && nowKey == KEY_PULL) {
//			//PauseFlg = true;
//			PauseFlg = !PauseFlg;
//			//pose = true;
//			//pose = PauseFlg;
//		}
//	}
//	if (PauseFlg) {
//
//		if (450 <= MouseX && MouseX <= 850 && 470 <= MouseY && MouseY <= 590) {
//			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
//				//StopSoundMem(CF_GameBGM);
//				//parent->SetNext(new Scene_Select());
//			}
//		}
//	}
//	OldKey = nowKey; //�O�ɓ��͂��Ă����L�[�������͂��Ă����L�[�ɏ㏑������
//}
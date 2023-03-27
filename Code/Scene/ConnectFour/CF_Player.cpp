#include"CF_Player.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"
#include<time.h>
#include "../../SceneManager.h"
#include"Scene_ConnectFour.h"
#include "./../Scene.h"
#include "../Title/Title.h"
#include "./../Title/Title_Select.h"


//CF_Player cf_player;
void CF_Player::CF_Player_Initialize(Scene* scene) {
	this->parent = scene;

	CF_Back = LoadGraph("Resource/image/CF_Back.png"); //�w�i
	CF_Panel = LoadGraph("Resource/image/CF_Panel.png"); //�p�l��
	CF_PCoin = LoadDivGraph("Resource/image/Player_Coin.png",2,2,1,400,400, pcoin); //�v���C���[�R�C��
	CF_CCoin = LoadDivGraph("Resource/image/CPU_Coin.png", 2, 2, 1, 400, 400, ccoin); //CPU�R�C��
	Pause_Button = LoadGraph("Resource/image/PauseButton.png");
	Pause_Back = LoadGraph("Resource/image/PauseBack.png");
	Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
	Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);
	CF_GameBGM = LoadSoundMem("Resource/bgm/CF_BGM.wav"); //�Q�[������BGM
	CF_StartSE = LoadSoundMem("Resource/se/CF_SoundofCollision.wav"); //��U��U�̕�����\�����鎞��SE
	CF_CoinFallSE = LoadSoundMem("Resource/se/CF_CoinFallSound.wav"); //�R�C�����Ԃ������Ƃ���SE
	CF_ClickSE = LoadSoundMem("Resource/se/CF_ClickSound.wav"); //�}�E�X���N���b�N�����Ƃ���SE
	Pause_Cursol = LoadSoundMem("Resource/se/Pause_Cursor.wav");
	Pause_Click = LoadSoundMem("Resource/se/Pause_Click.wav");
	Player_Y = 50; //�R�C����Y���W�̏����l
	k = 1;
	Yajirusi_Y = 100; //���̏����l
	Yajirusi_Move = 0.5f; //���̃A�j���[�V�����̏����l
	yadd = 0.0f; //�d�͉����x�̏����l
	FallCount = 0.0f; //�R�C����������܂ł̎��Ԃ̏����l;
	DlayCount = 0; //
	Mouse_Push = false; //���N���b�N���ꂽ���̃t���O�̏����l
	CF_Clear = false; //�N���A�t���O�̏����l
	CF_ClearText = false;
	CF_Draw = false; //�h���[�t���O�̏����l
	CF_Start = false; //�Q�[�����X�^�[�g�������̃t���O�̏����l
	FallSEflg = false; //CoinFallSE���������ǂ����̃t���O
	PauseFlg = false; //�|�[�Y��ʂ�\�����邩�ǂ����̃t���O
	Board_Init();//�p�l�����̏�����
	srand((unsigned int)time(NULL)); //���������ݎ����̏��ŏ�����
	PlayUser = rand() % 2 + 1; //�v���C���[�̐�U��U�������_���Ŏ擾
	CPU_j = rand() % 7;
	CPU_Position = 99;
	CPU_Start = 0;
	OldKey = KEY_FREE;

	Pause_OneClick = false;
	Pause_OneCursol = false;

	Coin_Switch = 0;
}
void CF_Player::CF_Player_Finalize() {
	DeleteGraph(CF_Back); //�摜�폜����
	DeleteGraph(CF_Panel);
}
void CF_Player::CF_Player_Update() {
	nowKey = key->GetKeyState(REQUEST_MOUSE_LEFT); //���݂̃}�E�X���{�^���̓��͏�Ԃ̎擾
	if (CF_Start == false) {
		DlayCount++;
		if (DlayCount % 40 == 0 && DlayCount <= 120) {
			PlaySoundMem(CF_StartSE, DX_PLAYTYPE_BACK);
		}
		if (DlayCount > 240) {
			DlayCount = 0;
			CF_Start = true;
		}
	}
	if (Mouse_Push == false) {
		GetMousePoint(&Mouse_X, &Mouse_Y); //�}�E�X�̍��W�擾
	}
	if (CF_Clear == false && CF_Draw == false && CF_Start == true && PauseFlg == false) {
		if (CheckSoundMem(CF_GameBGM) == 0) {
			ChangeVolumeSoundMem(110, CF_GameBGM);
			PlaySoundMem(CF_GameBGM, DX_PLAYTYPE_LOOP);
		}
		
		if (PlayUser == Coin_Player) {
			Player_X = Mouse_X;
		}
		else if (PlayUser == Coin_CPU) {
			CPU_X = CPU_j * 114 + 306;
		}
		if (Player_X <= 306) {
			Player_X = 306;
		}
		else if (Player_X >= 990) {
			Player_X = 990;
		}
		Yajirusi_Y += Yajirusi_Move;
		if (100 >= Yajirusi_Y) {
			Yajirusi_Y = 100;
			Yajirusi_Move = -Yajirusi_Move;
		}
		else if (Yajirusi_Y >= 115) {
			Yajirusi_Y = 115;
			Yajirusi_Move = -Yajirusi_Move;
		}
		/*�|�[�Y�{�^������������|�[�Y��ʂ��J���t���O��true�ɂ���*/
		if (20 <= Mouse_X && Mouse_X <= 200 && 25 <= Mouse_Y && Mouse_Y <= 105) {
			if(OldKey != KEY_FREE && nowKey == KEY_PULL) {
				PauseFlg = true;
			}
		}
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (PlayUser == Coin_CPU) {
					CPU_CoinCheck(CF_Board, j, i);
					if (j * 114 + 306 - 48 < CPU_X && CPU_X < j * 114 + 306 + 48) {
						if (CF_Board[j][0] != Coin_Space) {
							if (CF_Board[1][0] == Coin_Space || CF_Board[2][0] == Coin_Space || CF_Board[3][0] == Coin_Space || CF_Board[4][0] == Coin_Space || CF_Board[5][0] == Coin_Space) {
								while (CPU_j == j)
								{
									CPU_j = rand() % 5 + 1;
									if (CPU_j != j) {
										Coin_Fall();
										break;
									}
								}
							}
							else {
								while (CPU_j == j)
								{
									CPU_j = rand() % 7;
									if (CPU_j != j) {
										Coin_Fall();
										break;
									}
								}
							}
						}
						else {
							Coin_Fall();
						}
					}
				}
				else if (PlayUser == Coin_Player) {
					if (30 > Mouse_X || Mouse_X > 147 || 35 > Mouse_Y || Mouse_Y > 89) {
						if (j * 114 + 306 - 48 < Player_X && Player_X < j * 114 + 306 + 48) { //���͈̔͂ɃR�C������������
							if (CF_Board[j][0] == Coin_Space) {
								if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
									if (CheckSoundMem(CF_ClickSE) == 0 && Mouse_Push == false) {
										ChangeVolumeSoundMem(200, CF_ClickSE);
										PlaySoundMem(CF_ClickSE, DX_PLAYTYPE_BACK);
									}
									Mouse_Push = true;
								}
								if (Mouse_Push == true) {
									Coin_Fall(); //�R�C����z�u����
								}
							}
							Yajirusi_Col[j] = 0xffffff;
						}
						else {
							Yajirusi_Col[j] = 0xff0000;
						}
					}
				}
				if (ClearCheck(CF_Board, j, i)) {
					CF_Clear = true;
				}
				if (DrawCheck(CF_Board)) {
					CF_Draw = true;
				}
				
			}
		}
	}
	else if (CF_Draw == true) {
		DlayCount++;
		if (DlayCount > 90) {
			CF_ClearText = true;
		}
	}
	else if (CF_Clear == true) {
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (ClearCheck(CF_Board, j, i)) {
				}
			}
		}
		DlayCount++;
		if (DlayCount > 90) {
			CF_ClearText = true;
		}
		/*�|�[�Y��ʂ̓��e*/
	}else if (PauseFlg == true) {
		if ((450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) ||(20 <= Mouse_X && Mouse_X <= 200 && 25 <= Mouse_Y && Mouse_Y <= 105)) {
			if (Pause_OneCursol == false) {
				PlaySoundMem(Pause_Cursol, DX_PLAYTYPE_BACK);
				Pause_OneCursol = true;
			}
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�}�E�X�̍��L�[�𗣂�����
				PlaySoundMem(Pause_Click, DX_PLAYTYPE_BACK);
				PauseFlg = false;
			}
		}
		else {
			Pause_OneCursol = false;
		}
		if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
			if (Pause_OneClick == false) {
				PlaySoundMem(Pause_Cursol, DX_PLAYTYPE_BACK);
				Pause_OneClick = true;
			}
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�}�E�X�̍��L�[�𗣂�����
				PlaySoundMem(Pause_Click, DX_PLAYTYPE_BACK);
				parent->SetNext(new Title_Select());
				StopSoundMem(CF_GameBGM);
			}
		}
		else {
			Pause_OneClick = false;
		}
	}
	if (CF_ClearText == true) {
		if (485 <= Mouse_X && Mouse_X <= 909 && 340 <= Mouse_Y && Mouse_Y <= 398) {
			if (Pause_OneCursol == false) {
				PlaySoundMem(Pause_Cursol, DX_PLAYTYPE_BACK);
				Pause_OneCursol = true;
			}
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�}�E�X�̍��L�[�𗣂�����
				PlaySoundMem(Pause_Click, DX_PLAYTYPE_BACK);
				StopSoundMem(CF_GameBGM);
				CF_Player_Initialize(parent);
			}
		}
		else {
			Pause_OneCursol = false;
		}
		if (465 <= Mouse_X && Mouse_X <= 927 && 490 <= Mouse_Y && Mouse_Y <= 558) {
			if (Pause_OneClick == false) {
				PlaySoundMem(Pause_Cursol, DX_PLAYTYPE_BACK);
				Pause_OneClick = true;
			}
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�}�E�X�̍��L�[�𗣂�����
				PlaySoundMem(Pause_Click, DX_PLAYTYPE_BACK);
				parent->SetNext(new Title_Select());
				StopSoundMem(CF_GameBGM);
			}
		}
		else {
			Pause_OneClick = false;
		}
	}
	OldKey = nowKey; //�O�ɓ��͂��Ă����L�[�������͂��Ă����L�[�ɏ㏑������
}
void CF_Player::CF_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, CF_Back, TRUE);
	if (CF_Start == false) {
		SetFontSize(160);
		if (DlayCount > 40){
			DrawFormatString(50, 200, 0xffffff, "���Ȃ�");
			DrawFormatString(50, 400, 0xffffff, "�b�o�t");
			DrawRotaGraph(700, 280, 0.45, 0, pcoin[0], TRUE);
			DrawRotaGraph(700, 480, 0.45, 0, ccoin[0], TRUE);
		}
		if (DlayCount > 80) {
			if (PlayUser == Coin_Player) {
				DrawFormatString(850, 200, 0xff0000, "��U");
			}
			else if (PlayUser == Coin_CPU) {
				DrawFormatString(850, 400, 0xff0000, "��U");
			}
		}
		if (DlayCount > 120) {
			if (PlayUser == Coin_Player) {
				DrawFormatString(850, 400, 0xffffff, "��U");
			}
			else if (PlayUser == Coin_CPU) {
				DrawFormatString(850, 200, 0xffffff, "��U");
			}
		}
	}
	else{
		SetFontSize(24);
		if (CF_Clear == false) {
			//�|�[�Y�{�^��
			DrawRotaGraph(110, 65, 0.9, 0, Pause_Button, TRUE);
			if (CF_Draw == false) {
				if (PlayUser == Coin_Player) {
					DrawFormatString(1080, 50, 0x000000, "���Ȃ��̔Ԃł�");
					DrawRotaGraph(Player_X, Player_Y, 0.17, 0, pcoin[0], TRUE);
				}
				else {
					DrawFormatString(1080, 50, 0x000000, "�b�o�t�̔Ԃł�");
					DrawRotaGraph(CPU_X, Player_Y, 0.17, 0, ccoin[0], TRUE);
				}
			}
		}
		SetFontSize(16);
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (CF_Board[j][0] == Coin_Space && PlayUser == Coin_Player && CF_Draw == false && CF_Clear == false) {
					DrawFormatString(297 + j * 114.5, Yajirusi_Y, Yajirusi_Col[j], "��");
				}
				if (CF_Board[j][i] == Coin_Player) {
					DrawRotaGraph(j * 114 + 306, i * 79 + 209, Coin_Exp[j][i], 0, pcoin[0], TRUE);
				}
				else if (CF_Board[j][i] == Coin_CPU) {
					DrawRotaGraph(j * 114 + 306, i * 79 + 209, Coin_Exp[j][i], 0, ccoin[0], TRUE);
				}
			}
		}
		DrawRotaGraph(640, 420, 0.8, 0, CF_Panel, TRUE); 
		if (CF_Clear == true) {
			for (i = 0; i < Board_Ysize; i++) {
				for (j = 0; j < Board_Xsize; j++) {
					if (CF_CircleBoard[j][i] == 1) {
						Coin_Switch++;
						if (60 >= Coin_Switch) {
							if (CF_Board[j][i] == Coin_Player) {
								DrawRotaGraph(j * 114 + 306, i * 79 + 209, Coin_Exp[j][i], 0, pcoin[1], TRUE);
							}
							else if (CF_Board[j][i] == Coin_CPU) {
								DrawRotaGraph(j * 114 + 306, i * 79 + 209, Coin_Exp[j][i], 0, ccoin[1], TRUE);
							}
						}
						else if (120 >= Coin_Switch && Coin_Switch >= 60) {
							if (CF_Board[j][i] == Coin_Player) {
								DrawRotaGraph(j * 114 + 306, i * 79 + 209, Coin_Exp[j][i], 0, pcoin[0], TRUE);
							}
							else if (CF_Board[j][i] == Coin_CPU) {
								DrawRotaGraph(j * 114 + 306, i * 79 + 209, Coin_Exp[j][i], 0, ccoin[0], TRUE);
							}
						}
						else {
							Coin_Switch = 0;
						}
						
					}
				}
			}
		}
		/*�|�[�Y��ʂ̉摜*/
		if (PauseFlg == true) {
			DrawRotaGraph(650, 380, 1.15, 0, Pause_Back, TRUE);
			if (450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) {
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
			if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
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
	if (CF_ClearText == true) {
		SetFontSize(72);
		if (CF_Clear == true) {
			if (PlayUser != Coin_Player) {
				DrawFormatString(400, 50, 0xffffff, "�v���C���[�̏����I");
			}
			else {
				DrawFormatString(420, 50, 0xffffff, "�b�o�t�̏����I");
			}
		}
		else if (CF_Draw == true) {
			DrawFormatString(500, 50, 0xffffff, "�� �� �� ��");
		}
		SetFontSize(48);
		if (485 <= Mouse_X && Mouse_X <= 909 && 340 <= Mouse_Y && Mouse_Y <= 398) {
			if (nowKey == KEY_HOLD) {
				SetFontSize(40);
				DrawBox(512, 350, 862, 410, 0xdcdcdc, TRUE);
				DrawFormatString(527, 360, 0x000000, "������x�Â���"); 
				SetFontSize(48);
			}
			else {
				DrawBox(485, 340, 909, 408, 0xdcdcdc, TRUE);
				DrawFormatString(500, 350, 0x000000, "������x�Â���");
			}
		}
		else {
			DrawBox(485, 340, 909, 408, 0xffffff, TRUE);
			DrawFormatString(500, 350, 0x000000, "������x�Â���");
		}
		if (465 <= Mouse_X && Mouse_X <= 927 && 490 <= Mouse_Y && Mouse_Y <= 558) {
			if (nowKey == KEY_HOLD) {
				SetFontSize(40);
				DrawBox(492, 500, 882, 564, 0xdcdcdc, TRUE);
				DrawFormatString(507, 510, 0x000000, "�Z���N�g��ʂɖ߂�");
			}
			else {
				DrawBox(465, 490, 927, 558, 0xdcdcdc, TRUE);
				DrawFormatString(480, 500, 0x000000, "�Z���N�g��ʂɖ߂�");
			}
		}
		else {
			DrawBox(465, 490, 927, 558, 0xffffff, TRUE);
			DrawFormatString(480, 500, 0x000000, "�Z���N�g��ʂɖ߂�");
		}
	}
	SetFontSize(16);

}

void CF_Player:: Coin_Fall() { //�R�C����z�u���鏈��
	if (PlayUser == Coin_Player) {
		Player_X = j * 114 + 306;
	}
	else if (PlayUser == Coin_CPU) {
		j = CPU_j;
		CPU_X = j * 114 + 306;
	}
	if (FallCount++ > 90) {
		if(CF_Board[j][Board_Ysize - k] != Coin_Space && Board_Ysize - k >= 0) { //�󔒂���Ȃ��Ȃ�A���ɒu��
			while (CF_Board[j][Board_Ysize - k] != Coin_Space && Board_Ysize - k >= 0) {
				k += 1;
			}
		}
		else if (CF_Board[j][Board_Ysize - k + 1] == Coin_Space && Board_Ysize - k + 1 < Board_Ysize) { //�����󔒂Ȃ�A������Ƃ���܂ŉ��ɉ�����
			while (CF_Board[j][Board_Ysize - k + 1] == Coin_Space && Board_Ysize - k + 1 < Board_Ysize) {
				k -= 1;
			}
		}
		else { //����ȊO�Ȃ炻�̏�ɒu��
			k = k;
		}
		if (Player_Y < (Board_Ysize - k) * 79 + 209) {
			Player_Y += yadd;
			yadd += 0.04f;
		}
		else {
			Player_Y = (Board_Ysize - k) * 79 + 209;
			yadd = 0;
			if (CheckSoundMem(CF_CoinFallSE) == 0 && FallSEflg == false) {
				PlaySoundMem(CF_CoinFallSE, DX_PLAYTYPE_BACK);
				FallSEflg = true;
			}
			if (DlayCount++ > 90) {
				FallCount = 0;
				if (CF_Board[j][Board_Ysize - k] == Coin_Space) {
					if (PlayUser == Coin_Player) {
						CF_Board[j][Board_Ysize - k] = Coin_Player;
					}
					else {
						CF_Board[j][Board_Ysize - k] = Coin_CPU;
					}
				}
				Mouse_Push = false;
				FallSEflg = false;
				CPU_Position = 99;
				Player_Y = 50;
				DlayCount = 0;
				ChangeTurn(&PlayUser);
			}
		}
	}
}
void CF_Player::Board_Init() { //�p�l�����̏�����
	for (i = 0; i < Board_Ysize; i++) {
		for (j = 0; j < Board_Xsize; j++) {
			if (i == 6) {
				CF_Board[j][i] = 99;
			}
			else {
				CF_Board[j][i] = Coin_Space;
			}
			Coin_Exp[j][i] = 0.17f;
			CF_CircleBoard[j][i] = 0;
		}
	}
}
int CF_Player::ClearCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {//�N���A���菈��
	int a, b, ClearFlg;
	int dx[] = { 0,1,1 ,-1};
	int dy[] = { 1,0,1 ,1};
	for (a = 0; a < 4; a++) { //0�̎��͏�A1�̎��͉E�A2�̎��͉E��,3�̎��͍���̔Ֆʂ�����
		for (b = 1, ClearFlg = 1; b <= 3; b++) { //�w�肵�����W����4�}�X����
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] ||( 0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize || 0 >(y - b * dy[a])|| (y - b * dy[a]) >= Board_Ysize) || board[x + b * dx[a]][y - b * dy[a]] == Coin_Space || board[x + b * dx[a]][y - b * dy[a]] == 99) {
				ClearFlg = 0;
			}
		}
		if (ClearFlg == 1) { //4�}�X�Ƃ��������̂ł�������N���A��Ԃ�
			for (b = 1; b <= 3; b++) {
				CF_CircleBoard[x][y] = 1;
				CF_CircleBoard[x + b * dx[a]][y - b * dy[a]] = 1;
			}
			return 1;
		}
	}
	return 0;
}

void CF_Player::ChangeTurn(int *PlayUser) {
	if (*PlayUser == Coin_Player) {
		*PlayUser = Coin_CPU;
	}
	else {
		*PlayUser = Coin_Player;
	}
}
int CF_Player::DrawCheck(int board[Board_Xsize][Board_Ysize]) {
	int a, b, DrawFlg;
	for (b = 0, DrawFlg = 1; b < Board_Xsize; b++) {
		if (board[b][0] == Coin_Space) {
			DrawFlg = 0;
		}
	}
	if (DrawFlg == 1) {
		return 1;
	}
	else {
		return 0;
	}
}
void CF_Player::CPU_CoinCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {
	int a, b, CoinCheck, DoubleCheck;
	int dx[] = { 0,1,1 ,-1 };
	int dy[] = { 1,0,1 ,1 };
	for (a = 0; a < 4; a++) { //0�̎��͏�A1�̎��͉E�A2�̎��͉E��,3�̎��͍���̔Ֆʂ�����
		for (b = 1, CoinCheck = 1,DoubleCheck = 1; b <= 2; b++) { //�w�肵�����W����3�}�X����
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] || ((0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize) || (0 > (y - b * dy[a]) || (y - b * dy[a]) >= Board_Ysize)) || board[x][y] == Coin_Space || board[x][y] == 99) {
				if (b == 1) {
					DoubleCheck = 0;
					CoinCheck = 0;
				}
				else if(b == 2){
					CoinCheck = 0;
				}
			}
		}
		SpaceCheck(board, x, y);
		if (CoinCheck == 1) { //3�}�X�Ƃ��������̂���������
			DoubleCheck = 0;
			if (board[x][y] == Coin_CPU) {
				if (a == 0 && board[x + b * dx[a]][y - b * dy[a] - 1] == Coin_Space && 0 <= y - (b * dy[a]) - 1) { //���3�����Ă��āA���̏�ɉ����Ȃ��Ȃ�
					if (CPU_Position == 99) {
						CPU_j = x;
						CPU_Position = 0;
					}
				}
				//��3�����Ă��ĉE�[�̈�E�ɉ����Ȃ������A�E�΂߂�3�����Ă��Ă��̉E��ɉ����Ȃ���
				else if (((a == 1 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) || ((a == 2 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space)) {
					if (CPU_Position == 99) {
						CPU_j = x + (b * dx[a]);
						CPU_Position = 0;
					}
				}
				//����3�����Ă��Ă��̍��ɉ����Ȃ������A�E�΂߂�3�����Ă��Ă��̍����ɉ����Ȃ���
				else if (((a == 1 && board[x - 1][y] == Coin_Space) && board[x - 1][y + 1] != Coin_Space && 0 <= (x - 1)) || ((a == 2 && board[x - 1][y + 1] == Coin_Space) && board[x - 1][y + 2] != Coin_Space && 0 <= (x - 1) && (y + 2) < Board_Ysize)) {
					if (CPU_Position == 99) {
						CPU_j = x - 1;
						CPU_Position = 0;
					}
				}
				//���΂߂�3�����Ă��āA���̍���ɉ����Ȃ���
				else if (a == 3 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) {
					if (CPU_Position == 99) {
						CPU_j = x + (b * dx[a]);
						CPU_Position = 0;
					}
				}
				//���΂߂�3�����Ă��āA���̉E���ɉ����Ȃ���
				else if (a == 3 && board[x + 1][y + 1] == Coin_Space && board[x + 1][y + 2] != Coin_Space && x + 1 < Board_Xsize && y + 2 < Board_Ysize) {
					if (CPU_Position == 99) {
						CPU_j = x + 1;
						CPU_Position = 0;
					}
				}
			}
			else if (board[x][y] == Coin_Player) {
				if (a == 0 && board[x + b * dx[a]][y - b * dy[a] - 1] == Coin_Space && 0 <= y - (b * dy[a]) - 1) { //���3�����Ă��āA���̏�ɉ����Ȃ��Ȃ�
					if (CPU_Position == 99) {
						CPU_j = x;
						CPU_Position = 0;
					}
				}
				//��3�����Ă��ĉE�[�̈�E�ɉ����Ȃ������A�E�΂߂�3�����Ă��Ă��̉E��ɉ����Ȃ���
				else if (((a == 1 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) || ((a == 2 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space)) {
					if (CPU_Position == 99) {
						CPU_j = x + (b * dx[a]);
						CPU_Position = 0;
					}
				}
				//����3�����Ă��Ă��̍��ɉ����Ȃ������A�E�΂߂�3�����Ă��Ă��̍����ɉ����Ȃ���
				else if (((a == 1 && board[x - 1][y] == Coin_Space) && board[x - 1][y + 1] != Coin_Space && 0 <= (x - 1)) || ((a == 2 && board[x - 1][y + 1] == Coin_Space) && board[x - 1][y + 2] != Coin_Space && 0 <= (x - 1) && (y + 2) < Board_Ysize)) {
					if (CPU_Position == 99) {
						CPU_j = x - 1;
						CPU_Position = 0;
					}
				}
				//���΂߂�3�����Ă��āA���̍���ɉ����Ȃ���
				else if (a == 3 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) {
					if (CPU_Position == 99) {
						CPU_j = x + (b * dx[a]);
						CPU_Position = 0;
					}
				}
				//���΂߂�3�����Ă��āA���̉E���ɉ����Ȃ���
				else if (a == 3 && board[x + 1][y + 1] == Coin_Space && board[x + 1][y + 2] != Coin_Space && x + 1 < Board_Xsize && y + 2 < Board_Ysize) {
					if (CPU_Position == 99) {
						CPU_j = x + 1;
						CPU_Position = 0;
					}
				}
			}
		}
		SpaceDoubleCheck(board, x, y);
		if (DoubleCheck == 1 && CoinCheck == 0) { //2�����Ă��āA3�����Ă�����̂��Ȃ���
			if (board[x][y] == Coin_CPU) {
				//���2�����Ă��āA���̏�ɉ����Ȃ��Ȃ�
				if (a == 0 && board[x + b * dx[a]][(y - (b * dy[a]) - 1)] == Coin_Space && 0 <= (y - (b * dy[a]) - 1)) {
					if (CPU_Position == 99) {
						CPU_j = x;
						CPU_Position = 0;
					}
				}
				//��2�����Ă��ĉE�[�̈�E�ɉ����Ȃ������A�E�΂߂�2�����Ă��Ă��̉E��ɉ����Ȃ���
				else if (((a == 1 && board[x + (b * dx[a]) - 1][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a] - 1][y - b * dy[a] + 1] != Coin_Space) || ((a == 2 && board[x + b * dx[a] - 1][y - b * dy[a] + 1] == Coin_Space) && board[x + b * dx[a] - 1][y - b * dy[a] + 2] != Coin_Space)) {
					if (CPU_Position == 99) {
						CPU_j = x + (b * dx[a]) - 1;
						CPU_Position = 0;
					}
				}
				//����2�����Ă��Ă��̍��ɉ����Ȃ������A�E�΂߂�2�����Ă��Ă��̍����ɉ����Ȃ���
				else if (((a == 1 && board[x - 1][y] == Coin_Space) && board[x - 1][y + 1] != Coin_Space && 0 <= (x - 1)) || ((a == 2 && board[x - 1][y + 1] == Coin_Space) && board[x - 1][y + 2] != Coin_Space && 0 <= (x - 1) && (y + 2) < Board_Ysize)) {
					if (CPU_Position == 99) {
						CPU_j = x - 1;
						CPU_Position = 0;
					}
				}
				//���΂߂�2�����Ă��āA���̍���ɉ����Ȃ���
				else if (a == 3 && board[x + b * dx[a] + 1][y - b * dy[a] + 1] == Coin_Space && board[x + b * dx[a] + 1][y - b * dy[a] + 2] != Coin_Space) {
					if (CPU_Position == 99) {
						CPU_j = x + (b * dx[a]) + 1;
						CPU_Position = 0;
					}
				}
				//���΂߂�2�����Ă��āA���̉E���ɉ����Ȃ���
				else if (a == 3 && board[x + 1][y + 1] == Coin_Space && board[x + 1][y + 2] != Coin_Space && x + 1 < Board_Xsize && y + 2 < Board_Ysize) {
					if (CPU_Position == 99) {
						CPU_j = x + 1;
						CPU_Position = 0;
					}
				}
			}
			else if (board[x][y] == Coin_Player) {
				//��2�����Ă��ĉE�[�̈�E�ɉ����Ȃ������A�E�΂߂�2�����Ă��Ă��̉E��ɉ����Ȃ���
				if (a == 0 && board[x + b * dx[a]][(y - (b * dy[a]) - 1)] == Coin_Space && 0 <= (y - (b * dy[a]) - 1)) {
					if (CPU_Position == 99) {
						CPU_j = x;
						CPU_Position = 0;
					}
				}
				else if (((a == 1 && board[x + (b * dx[a]) - 1][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a] - 1][y - b * dy[a] + 1] != Coin_Space) || ((a == 2 && board[x + b * dx[a] - 1][y - b * dy[a] + 1] == Coin_Space) && board[x + b * dx[a] - 1][y - b * dy[a] + 2] != Coin_Space)) {
					if (CPU_Position == 99) {
						CPU_j = x + (b * dx[a]) - 1;
						CPU_Position = 0;
					}
				}
				//����2�����Ă��Ă��̍��ɉ����Ȃ������A�E�΂߂�2�����Ă��Ă��̍����ɉ����Ȃ���
				else if (((a == 1 && board[x - 1][y] == Coin_Space) && board[x - 1][y + 1] != Coin_Space && 0 <= (x - 1)) || ((a == 2 && board[x - 1][y + 1] == Coin_Space) && board[x - 1][y + 2] != Coin_Space && 0 <= (x - 1) && (y + 2) < Board_Ysize)) {
					if (CPU_Position == 99) {
						CPU_j = x - 1;
						CPU_Position = 0;
					}
				}
				//���΂߂�2�����Ă��āA���̍���ɉ����Ȃ���
				else if (a == 3 && board[x + b * dx[a] + 1][y - b * dy[a] + 1] == Coin_Space && board[x + b * dx[a] + 1][y - b * dy[a] + 2] != Coin_Space) {
					if (CPU_Position == 99) {
						CPU_j = x + (b * dx[a]) + 1;
						CPU_Position = 0;
					}
				}
				//���΂߂�2�����Ă��āA���̉E���ɉ����Ȃ���
				else if (a == 3 && board[x + 1][y + 1] == Coin_Space && board[x + 1][y + 2] != Coin_Space && x + 1 < Board_Xsize && y + 2 < Board_Ysize) {
					if (CPU_Position == 99) {
						CPU_j = x + 1;
						CPU_Position = 0;
					}
				}
			}
		}
		if (CPU_Position == 99) {
			CPU_RandomFall();
		}
	}
}
void CF_Player::SpaceCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {
	int a, b;
	int dx[] = {1,1 ,-1 };
	int dy[] = {0,1 ,1 };
	for (a = 0; a < 3; a++) { //0�̎��͉E�A1�̎��͉E��,2�̎��͍���̔Ֆʂ�����
		for (b = 1; b <= 3; b++) { //�w�肵�����W����4�}�X����
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) {
				if (((0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize) || (0 > (y - b * dy[a]) || (y - b * dy[a]) >= Board_Ysize)) || board[x + b * dx[a]][y - b * dy[a]] == 99) {
					
				}else{
					if (board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) {
						if (board[x][y] == Coin_CPU) {
							if (a == 0) { //�E�����Ă���Ƃ�
								//1�E���󂢂Ă��邩2�E���󂢂Ă���Ƃ�
								if ((b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]] && board[x][y] == board[x + b * dx[a] + 2][y - b * dy[a]])|| (b == 2 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]])) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
							else if (a == 1) { //�E������Ă���Ƃ�
								//1�E�オ�󂢂Ă��邩2�E�オ�󂢂Ă���Ƃ�
								if ((b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1] && board[x][y] == board[x + b * dx[a] + 2][y - b * dy[a] - 2])|| (b == 2 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1])) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
							else if (a == 2) { //��������Ă���Ƃ�
								//1���オ�󂢂Ă��邩2���オ�󂢂Ă���Ƃ�
								if ((b == 1 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1] && board[x][y] == board[x + b * dx[a] - 2][y - b * dy[a] - 2]) || (b == 2 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1])) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
						}else if (board[x][y] == Coin_Player) {
							if (a == 0) { //�E�����Ă���Ƃ�
								//1�E���󂢂Ă��邩2�E���󂢂Ă���Ƃ�
								if ((b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]] && board[x][y] == board[x + b * dx[a] + 2][y - b * dy[a]]) || (b == 2 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]])) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
							else if (a == 1) { //�E������Ă���Ƃ�
								//1�E�オ�󂢂Ă��邩2�E�オ�󂢂Ă���Ƃ�
								if ((b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1] && board[x][y] == board[x + b * dx[a] + 2][y - b * dy[a] - 2]) || (b == 2 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1])) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
							else if (a == 2) { //��������Ă���Ƃ�
								//1���オ�󂢂Ă��邩2���オ�󂢂Ă���Ƃ�
								if ((b == 1 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1] && board[x][y] == board[x + b * dx[a] - 2][y - b * dy[a] - 2]) || (b == 2 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1])) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void CF_Player::SpaceDoubleCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {
	int a, b;
	int dx[] = { 1,1 ,-1 };
	int dy[] = { 0,1 ,1 };
	for (a = 0; a < 3; a++) { //0�̎��͉E�A1�̎��͉E��,2�̎��͍���̔Ֆʂ�����
		for (b = 1; b <= 2; b++) { //�w�肵�����W����3�}�X����
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) {
				if (((0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize) || (0 > (y - b * dy[a]) || (y - b * dy[a]) >= Board_Ysize)) || board[x + b * dx[a]][y - b * dy[a]] == 99) {

				}
				else {
					if (board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) {
						if (board[x][y] == Coin_CPU) {
							if (a == 0) { //�E�����Ă���Ƃ�
								//1�E���󂢂Ă���Ƃ�
								if (b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]]) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
							else if (a == 1) { //�E������Ă���Ƃ�
								//1�E�オ�󂢂Ă���Ƃ�
								if (b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1]) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
							else if (a == 2) { //��������Ă���Ƃ�
								//1���オ�󂢂Ă���Ƃ�
								if (b == 1 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1]) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
						}
						else if (board[x][y] == Coin_Player) {
							if (a == 0) { //�E�����Ă���Ƃ�
								//1�E���󂢂Ă���Ƃ�
								if (b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]]) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
							else if (a == 1) { //�E������Ă���Ƃ�
								//1�E�オ�󂢂Ă���Ƃ�
								if (b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1]) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
							else if (a == 2) { //��������Ă���Ƃ�
								//1���オ�󂢂Ă���Ƃ�
								if (b == 1 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1]) {
									if (CPU_Position == 99) {
										CPU_j = x + b * dx[a];
										CPU_Position = 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void CF_Player::CPU_RandomFall() {
	if (DlayCount == 0) {
		if (CPU_Start == 0) {
			CPU_Start++;
			CPU_j = 3;
		}
		else {
			if (CF_Board[1][0] == Coin_Space || CF_Board[2][0] == Coin_Space || CF_Board[3][0] == Coin_Space || CF_Board[4][0] == Coin_Space ||CF_Board[5][0] == Coin_Space ) {
				CPU_j = rand() % 5 + 1;
				while (CF_Board[CPU_j][0] != Coin_Space)
				{
					CPU_j = rand() % 5 + 1;
					if (CF_Board[CPU_j][0] == Coin_Space) {
						Coin_Fall();
						break;
					}
				}
			}
			else {
				CPU_j = rand() % 7;
			}
		}
		DlayCount = 1;
	}
}

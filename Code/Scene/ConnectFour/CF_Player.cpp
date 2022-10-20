#include"CF_Player.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"

//CF_Player cf_player;
void CF_Player::CF_Player_Initialize() {
	CF_Back = LoadGraph("Resource/image/CF_Back.png"); //�w�i
	CF_Panel = LoadGraph("Resource/image/CF_Panel.png"); //�p�l��
	CF_PCoin = LoadGraph("Resource/image/Player_Coin.png"); //�v���C���[�R�C��
	CF_CCoin = LoadGraph("Resource/image/CPU_Coin.png"); //CPU�R�C��
	Player_Y = 50; //�v���C���[��Y���W�̏����l
	k = 1;
	Yajirusi_Y = 100; //���̏����l
	Yajirusi_Move = 0.5f; //���̃A�j���[�V�����̏����l
	yadd = 0.0f;
	FallCount = 0.0f;
	Mouse_Push = false; //���N���b�N���ꂽ���̃t���O�̏����l
	CF_Clear = false;
	for (i = 0; i < 7; i++) {
		Yajirusi_Col[i] = 0xff0000; //���̐F�̏����l
	}
	Board_Init();//�p�l�����̏�����
}
void CF_Player::CF_Player_Finalize() {
	DeleteGraph(CF_Back); //�摜�폜����
	DeleteGraph(CF_Panel);
}
void CF_Player::CF_Player_Update() {
		if (Mouse_Push == false) {
			GetMousePoint(&Mouse_X, &Mouse_Y); //�}�E�X�̍��W�擾
		}
		Player_X = Mouse_X;
		if (Player_X <= 306) {
			Player_X = 306;
		}
		else if (Player_X >= 965) {
			Player_X = 965;
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
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (297 + j * 110 - 48 < Player_X && Player_X < 297 + j * 110 + 48) { //���͈̔͂ɃR�C������������
					if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
						if (CF_Board[j][0] == Coin_Space) {
							Mouse_Push = true;
						}
					}
					if (Mouse_Push == true) {
						if (CF_Board[j][0] == Coin_Space) {
							Coin_Fall(); //�R�C����z�u����
						}
					}
					Yajirusi_Col[j] = 0xffffff;
				}
				else {
					Yajirusi_Col[j] = 0xff0000;
				}
				if (CF_Board[j][i] == Coin_Space) continue;
				if (ClearCheck(CF_Board, j, i)) {
					CF_Clear = true;
				}
			}
		}
	
}
void CF_Player::CF_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, CF_Back, TRUE);
	DrawFormatString(100, 50, 0xffffff, "%d", Player_X);
	DrawRotaGraph(Player_X, Player_Y, 0.165, 0, CF_PCoin, TRUE);
	for (i = 0; i < Board_Ysize; i++) {
		for (j = 0; j < Board_Xsize; j++) {
			DrawFormatString(297 + j * 114.5, Yajirusi_Y, Yajirusi_Col[j], "��");
			if (CF_Board[j][i] == Coin_Player) {
				DrawRotaGraph(j * 114 + 306, i * 79 + 209, 0.17, 0, CF_PCoin, TRUE);
			}else if(CF_Board[j][i] == Coin_CPU){
				DrawRotaGraph(j * 110 + 298, i * 78 + 200, 0.17, 0, CF_CCoin, TRUE);
			}
			DrawFormatString(j * 114+ 303, i * 79 + 200, 0xffffff, "%d", CF_Board[j][i]);
		}
	}
	DrawRotaGraph(640, 420, 0.8, 0, CF_Panel, TRUE);
	if (CF_Clear == true) {
		SetFontSize(36);
		DrawFormatString(640, 360, 0x0000ff, "�����I");
		SetFontSize(16);
	}
}

void CF_Player:: Coin_Fall() { //�R�C����z�u���鏈��
	Player_X = j * 114 + 306;
	if (FallCount++ > 60) {
		if (Player_Y < 604) {
			Player_Y += yadd;
			yadd += 0.1f;
		}
		else {
			Player_Y = 50;
			yadd = 0;
			FallCount = 0;
			if (CF_Board[j][Board_Ysize - k] != Coin_Space && Board_Ysize - k >= 0) {
				k += 1;
			}
			else {
				k = 1;
			}
			if (CF_Board[j][Board_Ysize - k] == Coin_Space) {
				CF_Board[j][Board_Ysize - k] = Coin_Player;
			}
			Mouse_Push = false;
		}
	}
}
void CF_Player::Board_Init() { //�p�l�����̏�����
	for (i = 0; i < Board_Ysize; i++) {
		for (j = 0; j < Board_Xsize; j++) {
			CF_Board[j][i] = Coin_Space;
		}
	}
}
int CF_Player::ClearCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {//�N���A���菈��
	int a, b, ClearFlg;
	int dx[] = { 0,1,1 };
	int dy[] = { 1,0,1 };

	for (a = 0; a < 3; a++) {
		for (b = 1, ClearFlg = 1; b <= 3; b++) {
			if (board[y][x] != board[y + b * dy[a]][x + b * dx[a]] || board[y + j * dy[a]][x + j * dx[a]] == Coin_Space) {
				ClearFlg = 0;
			}
		}
		if (ClearFlg == 1) {
			return 1;
		}
	}
	return 0;
}
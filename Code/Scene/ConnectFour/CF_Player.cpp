#include"CF_Player.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"

//CF_Player cf_player;
void CF_Player::CF_Player_Initialize() {
	CF_Back = LoadGraph("Resource/image/CF_Back.png"); //背景
	CF_Panel = LoadGraph("Resource/image/CF_Panel.png"); //パネル
	CF_PCoin = LoadGraph("Resource/image/Player_Coin.png"); //プレイヤーコイン
	CF_CCoin = LoadGraph("Resource/image/CPU_Coin.png"); //CPUコイン
	Player_Y = 50;
	Yajirusi_Y = 100;
	Yajirusi_Move = 0.5f;
	for (i = 0; i < 7; i++) {
		Yajirusi_Col[i] = 0xff0000;
	}
}
void CF_Player::CF_Player_Finalize() {
	DeleteGraph(CF_Back);
	DeleteGraph(CF_Panel);
}
void CF_Player::CF_Player_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y);
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
	else if(Yajirusi_Y >= 115){
		Yajirusi_Y = 115;
		Yajirusi_Move = -Yajirusi_Move;
	}
	for (i = 0; i < 7; i++) {
		if (297 + i * 110 - 48 < Player_X && Player_X < 297 + i * 110 + 48) {
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
				Player_X = 297 + i * 110 - 48;
				if (Player_Y < 550) {
					Player_Y += 1;
				}
				else {
					Player_Y = 550;
				}
			}
			Yajirusi_Col[i] = 0xffffff;
		}
		else {
			Yajirusi_Col[i] = 0xff0000;
		}
	}
}
void CF_Player::CF_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, CF_Back, TRUE);
	for (i = 0; i < 7; i++) {
		DrawFormatString(297 + i * 110, Yajirusi_Y, Yajirusi_Col[i], "▼");
	}
	DrawFormatString(100, 50, 0xffffff, "%d", Player_X);
	DrawRotaGraph(Player_X, Player_Y, 0.16, 0, CF_PCoin, TRUE);
	DrawRotaGraph(640, 420, 0.8, 0, CF_Panel, TRUE);
}
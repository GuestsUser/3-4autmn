#include"PO_Player.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"

//CF_Player cf_player;
void PO_Player::PO_Player_Initialize() {
	LoadDivGraph("./../Resource/image/toranpu_all.png", 65, 5, 13, 200, 300, card_type);

	// iはスート、jはナンバー
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Card_obj[i + j] = Card(card_type[i + j], j, i, false);
		}
	}

	Card_obj[52] = Card(card_type[52], 0, 5, false);	//カードの裏面
	Card_obj[53] = Card(card_type[53], 99, 5, false);	//ジョーカー

	Player_Y = 50;
	Yajirusi_Y = 100;
	Yajirusi_Move = 0.5f;
	for (i = 0; i < 7; i++) {
		Yajirusi_Col[i] = 0xff0000;
	}
}

void PO_Player::PO_Player_Finalize() {
	DeleteGraph((int)card_type);
}

void PO_Player::PO_Player_Update() {

	for (int i = 0; i < 4; i++) {
		Player_card.push_back(Card_obj[rand() % sizeof(Card_obj)]);
	}

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
	else if (Yajirusi_Y >= 115) {
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
void PO_Player::PO_Player_Draw() {

	//int i = 0;
	//for (auto itr = Player_card.begin(); itr != Player_card.end(); itr++) {
	//	DrawRotaGraph(100 + i * Player_X, 100, 0.5, 0, *itr, TRUE);
	//	i++;
	//}
	DrawRotaGraph(100 + Player_X, 100, 0.5, 0, Card_obj[0].img, TRUE);

	for (i = 0; i < 7; i++) {
		DrawFormatString(297 + i * 110, Yajirusi_Y, Yajirusi_Col[i], "▼");
	}
	DrawFormatString(100, 50, 0xffffff, "%d", Player_X);
}
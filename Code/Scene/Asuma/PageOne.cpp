#include "DxLib.h"
#include "PageOne.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"
#include "./../../Worldval.h"
//#include <list>
//#include <vector>

void PageOne::PageOne_Initialize() {
	LoadDivGraph("Resource/image/toranpu_all.png", 54, 13, 5, 200, 300, card_type);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 13; j++) {
			Card_obj.push_back(Card(card_type[i + j], j, i));
		}
	}

	Card_back = Card(card_type[52], 0, 5);	//カードの裏面
	Card_joker = Card(card_type[53], 99, 5);	//ジョーカー

	Player_Y = 50;
	Yajirusi_Y = 100;
	Yajirusi_Move = 0.5f;
	for (i = 0; i < 7; i++) {
		Yajirusi_Col[i] = 0xff0000;
	}
}

void PageOne::PageOne_Finalize() {
	for (i = 0; i < 65; i++) {
		DeleteGraph(card_type[i]);
	}
}

void PageOne::PageOne_Update() {
	for (i = 0; i < 4; i++) {
		r = rand() % sizeof(Card_obj);
		Player_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);
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

void PageOne::PageOne_Draw() {
	//int i = 0;
	//for (auto itr = Player_card.begin(); itr != Player_card.end(); itr++) {
	//	DrawRotaGraph(100 + i * Player_X, 100, 0.5, 0, *itr, TRUE);
	//	i++;
	//}
	DrawRotaGraph(100 + Player_X, 100, 0.5, 0, Card_obj[0].img, TRUE);
}
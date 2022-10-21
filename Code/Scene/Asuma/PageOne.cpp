#include "DxLib.h"
#include "PageOne.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"
#include "./../../Worldval.h"

void PageOne::PageOne_Initialize() {
	LoadDivGraph("./../Resource/image/toranpu_all.png", 65, 5, 13, 200, 300, card_type);

	// iはスート、jはナンバー
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Card_obj[i + j] = Card::Card(card_type[i + j], j, i, false);
		}
	}

	Card_obj[52] = Card::Card(card_type[52], 0, 5, false);	//カードの裏面
	Card_obj[53] = Card::Card(card_type[53], 99, 5, false);	//ジョーカー
}

void PageOne::PageOne_Finalize() {
	DeleteGraph((int)card_type);
}

void PageOne::PageOne_Update() {
	for (int i = 0; i < 4; i++) {
		Player_card[i] = Card_obj[rand() % sizeof(Card_obj)];
	}
}

void PageOne::PageOne_Draw() {
	DrawRotaGraph(100, 100, 0.5, 0, Card_obj[53].img, TRUE);
	DrawRotaGraph(300, 100, 0.5, 0, Card_obj[53].img, TRUE);
	DrawRotaGraph(500, 100, 0.5, 0, Card_obj[53].img, TRUE);
	DrawRotaGraph(700, 100, 0.5, 0, Card_obj[53].img, TRUE);
}
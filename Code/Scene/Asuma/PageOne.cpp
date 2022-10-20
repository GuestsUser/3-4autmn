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
			Card_obj[i + j] = Card(card_type[i + j], j, i);
		}
	}

	Card_obj[52] = Card(card_type[52], 0, 5);
	Card_obj[53] = Card(card_type[53], 99, 5);
}

void PageOne::PageOne_Finalize() {

}

void PageOne::PageOne_Update() {

}

void PageOne::PageOne_Draw() {

}
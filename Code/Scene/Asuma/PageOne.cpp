#include"PageOne.h"
#include"DxLib.h"
//#include <list>
//#include <vector>

//int card_type[54];	//画像用ハンドル

void PageOne::PageOne_Initialize() {
	LoadDivGraph("Resource/image/toranpu_all.png", 54, 13, 5, 200, 300, card_type);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 13; j++) {
			Card_obj.push_back(Card(card_type[i + j], j, i));
			//Card_obj[i][j] = Card(card_type[i + j], j, i);
		}
	}

	Card_back = Card(card_type[52], 0, 5);	//カードの裏面
	Card_joker = Card(card_type[53], 99, 5);	//ジョーカー

	for (i = 0; i < 4; i++) {
		r = GetRand(sizeof(Card_obj));
		Player_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);
	}

}

void PageOne::PageOne_Finalize() {
	for (i = 0; i < 54; i++) {
		DeleteGraph(card_type[i]);
	}
}

void PageOne::PageOne_Update() {

}

void PageOne::PageOne_Draw() {
	int i = 0;
	for (auto itr = Player_card.begin(); itr != Player_card.end(); itr++) {
		DrawRotaGraph(100 + i * 100, 100, 0.5, 0, (*itr).img, TRUE);
		i++;
	}
	//DrawRotaGraph(500, 300, 1.0, 0, Card_obj[0][0].img, TRUE);
}
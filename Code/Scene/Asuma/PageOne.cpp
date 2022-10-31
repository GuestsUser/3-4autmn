#include"PageOne.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"

void PageOne::PageOne_Initialize() {
	LoadDivGraph("Resource/image/toranpu_all.png", 54, 13, 5, 200, 300, card_type);

	for (i = 0; i < 52; i++) {
			Card_obj.push_back(Card(card_type[i], i % 13, i / 13));
	}

	Card_back = Card(card_type[52], 0, 5);	//カードの裏面
	Card_joker = Card(card_type[53], 99, 5);	//ジョーカー

	for (i = 0; i < 4; i++) {
		r = GetRand(sizeof(Card_obj));
		Player_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);
	}

	for (i = 0; i < 4; i++) {
		r = GetRand(sizeof(Card_obj));
		NPC_card_1.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);
	}

	Deck_X = 100;
	Deck_Y = 400;

	Player_X = 150;
	Player_Y = 575;

	n = 0;
}

void PageOne::PageOne_Finalize() {
	for (i = 0; i < 54; i++) {
		DeleteGraph(card_type[i]);
	}
}

void PageOne::PageOne_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y);

	n++;	//山札からカード引くときのクールタイム（早すぎるとアクセス違反でるから）

	//プレイヤーがカード引く用
	if (n > 20) {
		if (Mouse_X > Deck_X - 50 && Mouse_X < Deck_X + 50 && Mouse_Y > Deck_Y - 75 && Mouse_Y < Deck_Y + 75) {
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
				r = GetRand(Card_obj.size());
				Player_card.push_back(Card_obj[r]);
				Card_obj.erase(Card_obj.begin() + r);
				n = 0;
			}
		}
	}

	j = GetColor(255, 255, 255);

	for (i = 0; i < Player_card.size(); i++) {
		//switch (i) {
		//case 0:
		//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h)) {
		//		j = GetColor(255, 0, 0);
		//	}
		//	break;
		//case 1:
		//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h)) {
		//		j = GetColor(0, 255, 0);
		//	}
		//	break;
		//case 2:
		//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h)) {
		//		j = GetColor(0, 0, 255);
		//	}
		//	break;
		//case 3:
		//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h)) {
		//		j = GetColor(255, 0, 255);
		//	}
		//	break;

		//default:
		//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h)) {
		//		j = GetColor(255, 255, 0);
		//	}			break;
		//}

		if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h)) {
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
				Field_card.push_back(Player_card.begin() + i);
			}
		}
	}

	//NPCがカード引く用_後で要改造
	if (n > 20) {
		if (Mouse_X > Deck_X - 50 && Mouse_X < Deck_X + 50 && Mouse_Y > Deck_Y - 75 && Mouse_Y < Deck_Y + 75) {
			if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
				r = GetRand(Card_obj.size());
				NPC_card_1.push_back(Card_obj[r]);
				Card_obj.erase(Card_obj.begin() + r);
				n = 0;
			}
		}
	}
}

void PageOne::PageOne_Draw() {
	player = 0;
	npc_1 = 0;

	//プレイヤーの手札描画
	for (auto itr = Player_card.begin(); itr != Player_card.end(); itr++) {
		DrawRotaGraph(Player_X + (player % 10) * (card_w * 0.5), Player_Y + (player / 10) * (card_h * 0.5), 0.5, 0, (*itr).img, TRUE);
		player++;
	}

	//NPC１号の手札描画
	for (auto itr = NPC_card_1.begin(); itr != NPC_card_1.end(); itr++) {
		//DrawRotaGraph(150 + (npc_1 % 5) * (card_w * 0.3), 75 + (npc_1 / 5) * (card_h * 0.3), 0.3, 0, Card_back.img, TRUE);
		DrawRotaGraph(150 + (npc_1 % 5) * (card_w * 0.3), 75 + (npc_1 / 5) * (card_h * 0.3), 0.3, 0, (*itr).img, TRUE);
		npc_1++;
	}

	DrawFormatString(120,300,GetColor(255,255,255),"デッキ枚数:%d", Card_obj.size());
	DrawRotaGraph(Deck_X, Deck_Y, 0.5, 0, Card_back.img, TRUE);

	DrawBox(500, 300, 550, 350, j, TRUE);
}
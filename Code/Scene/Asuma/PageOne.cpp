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

	flg_p = false;
	flg_1 = false;
	flg_2 = false;
	flg_3 = false;

	par = 1;

	random_shuffle(priority, 4);
}

void PageOne::PageOne_Finalize() {
	for (i = 0; i < 54; i++) {
		DeleteGraph(card_type[i]);
	}
}

void PageOne::PageOne_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y);

	n++;	//山札からカード引くときのクールタイム（早すぎるとアクセス違反でるから）
	j = GetColor(255, 255, 255);

	for (c = 0; c < 4; c++) {
		switch (priority[c]) {
		case PLAYER:
			//プレイヤーがカード引く用
			if (n > 10) {
				if (Mouse_X > Deck_X - 50 && Mouse_X < Deck_X + 50 && Mouse_Y > Deck_Y - 75 && Mouse_Y < Deck_Y + 75) {
					if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
						r = GetRand(Card_obj.size());
						Player_card.push_back(Card_obj[r]);
						Card_obj.erase(Card_obj.begin() + r);
						n = 0;
					}
				}
			}

			//プレイヤーの手札からカードだす
			for (i = 0; i < Player_card.size(); i++) {
				/*	X判定のみ	*/
				//switch (i) {
				//case 0:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h, 0.5)) {
				//		j = GetColor(255, 0, 0);
				//	}
				//	break;
				//case 1:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h, 0.5)) {
				//		j = GetColor(0, 255, 0);
				//	}
				//	break;
				//case 2:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h, 0.5)) {
				//		j = GetColor(0, 0, 255);
				//	}
				//	break;
				//case 3:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h, 0.5)) {
				//		j = GetColor(255, 0, 255);
				//	}
				//	break;
				//
				//default:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * i, Player_Y, card_w, card_h, 0.5)) {
				//		j = GetColor(255, 255, 0);
				//	}	
				// 	break;
				//}

				/*	Y判定のみ	*/
				//switch (i / 10) {
				//case 0:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X, Player_Y + (card_h / 2) * (i / 10), card_w, card_h)) {
				//		j = GetColor(255, 0, 0);
				//	}
				//	break;
				//case 1:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X, Player_Y + (card_h / 2) * (i / 10), card_w, card_h)) {
				//		j = GetColor(0, 255, 0);
				//	}
				//	break;
				//case 2:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X, Player_Y + (card_h / 2) * (i / 10), card_w, card_h)) {
				//		j = GetColor(0, 0, 255);
				//	}
				//	break;
				//case 3:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X, Player_Y + (card_h / 2) * (i / 10), card_w, card_h)) {
				//		j = GetColor(255, 0, 255);
				//	}
				//	break;
				//
				//default:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X, Player_Y + (card_h / 2) * (i / 10), card_w, card_h)) {
				//		j = GetColor(255, 255, 0);
				//	}	
				// 	break;
				//}

				/*	X判定&Y判定	*/
				//switch (i) {
				//case 0:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * (i % 10), Player_Y + (card_h / 2) * (i / 10), card_w, card_h, 0.5)) {
				//		j = GetColor(255, 0, 0);
				//	}
				//	break;
				//case 1:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * (i % 10), Player_Y + (card_h / 2) * (i / 10), card_w, card_h, 0.5)) {
				//		j = GetColor(0, 255, 0);
				//	}
				//	break;
				//case 2:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * (i % 10), Player_Y + (card_h / 2) * (i / 10), card_w, card_h, 0.5)) {
				//		j = GetColor(0, 0, 255);
				//	}
				//	break;
				//case 3:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * (i % 10), Player_Y + (card_h / 2) * (i / 10), card_w, card_h, 0.5)) {
				//		j = GetColor(255, 0, 255);
				//	}
				//	break;
				//
				//default:
				//	if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w / 2) * (i % 10), Player_Y + (card_h / 2) * (i / 10), card_w, card_h, 0.5)) {
				//		j = GetColor(255, 255, 0);
				//	}	
				// 	break;
				//}

				if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w * 0.5) * (i % 10), Player_Y + (card_h * pow(0.5, 2)) * (i / 10), card_w, card_h, 0.5)) {
					if (Field_card.empty() || Field_card[0].suit == Player_card[i].suit) {
						if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
							Field_card.push_back(Player_card[i]);
							Player_card.erase(Player_card.begin() + i);
							break;
						}
					}
				}
			}

		case NPC1:
			//NPCがカード引く用_後で要改造
			if (n > 10) {
				if (Mouse_X > Deck_X - 50 && Mouse_X < Deck_X + 50 && Mouse_Y > Deck_Y - 75 && Mouse_Y < Deck_Y + 75) {
					if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
						r = GetRand(Card_obj.size());
						NPC_card_1.push_back(Card_obj[r]);
						Card_obj.erase(Card_obj.begin() + r);
						n = 0;
					}
				}
			}

			//NPCの手札からカードだす(現在は手動で正確性もあまりよくない)
			for (i = 0; i < NPC_card_1.size(); i++) {
				if (Card::Hit(Mouse_X, Mouse_Y, 150 + (card_w * 0.3) * (i % 5), 75 + (card_h * pow(0.3, 2)) * (i / 5), card_w, card_h, 0.3)) {
					if (Field_card.empty() || Field_card[0].suit == NPC_card_1[i].suit) {
						if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
							Field_card.push_back(NPC_card_1[i]);
							NPC_card_1.erase(NPC_card_1.begin() + i);
							break;
						}
					}
				}
			}

			
		}
	}

	for (Card itr : Field_card) {

		if (itr.num == 0) {
			par = 0;
		}

		if (par != 0 && par < itr.num) {
			par = itr.num;
		}

		if (par == 0 && itr.num != 99) {
			par = 0;
		}
	}
}

void PageOne::PageOne_Draw() {
	field = 0;
	player = 0;
	npc_1 = 0;

	//場に出ているカードの描画
	for (Card itr:Field_card) {
		DrawRotaGraph(500 + field * 100, 350, 0.5, 0, itr.img, TRUE);
		field++;
	}

	//プレイヤーの手札描画
	for (Card itr:Player_card) {
		DrawRotaGraph(Player_X + (player % 10) * (card_w * 0.5), Player_Y + (player / 10) * (card_h * pow(0.5, 2)), 0.5, 0, itr.img, TRUE);
		player++;
	}

	//NPC１号の手札描画
	for (Card itr: NPC_card_1) {
		//DrawRotaGraph(150 + (npc_1 % 5) * (card_w * 0.3), 75 + (npc_1 / 5) * (card_h * 0.3), 0.3, 0, Card_back.img, TRUE);
		DrawRotaGraph(150 + (npc_1 % 5) * (card_w * 0.3), 75 + (npc_1 / 5) * (card_h * pow(0.3, 2)), 0.3, 0, itr.img, TRUE);
		npc_1++;
	}

	DrawFormatString(120,300,GetColor(255,255,255),"デッキ枚数:%d", Card_obj.size());
	DrawFormatString(50,300,GetColor(255,255,255),"par:%d", par);
	DrawRotaGraph(Deck_X, Deck_Y, 0.5, 0, Card_back.img, TRUE);

	DrawBox(500, 300, 550, 350, j, TRUE);

}
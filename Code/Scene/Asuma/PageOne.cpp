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

	pri = 1;

	priority = GetRand(MAX - 1);

}

void PageOne::PageOne_Finalize() {
	for (i = 0; i < 54; i++) {
		DeleteGraph(card_type[i]);
	}
}

void PageOne::PageOne_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y);
	static int test = 0;
	n++;	//山札からカード引くときのクールタイム（早すぎるとアクセス違反でるから）
	j = GetColor(255, 255, 255);

	switch (priority) {
	case 0:				// player
		if (flg_p == false) {
			//プレイヤーがカード引く用
			if ((Mouse_X > Deck_X - 50) && (Mouse_X < Deck_X + 50) && (Mouse_Y > Deck_Y - 75) && (Mouse_Y < Deck_Y + 75)) {
				if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
					r = GetRand((int)Card_obj.size() - 1);
					Player_card.push_back(Card_obj[r]);
					Card_obj.erase(Card_obj.begin() + r);
				}
			}

			//プレイヤーの手札からカードだす
			for (i = 0; i < Player_card.size(); i++) {
				if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w * 0.5) * (i % 10), Player_Y + (card_h * pow(0.5, 2)) * (i / 10), card_w, card_h, 0.5)) {
					if (Field_card.empty() || Field_card[0].suit == Player_card[i].suit) {
						if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
							Field_card.push_back(Player_card[i]);

							if (Player_card[i].num == 99) {
								pri = 99;
							}

							if (Player_card[i].num == 0) {
								pri = 0;
							}

							if (pri != 0 && pri < Player_card[i].num) {
								pri = Player_card[i].num;
							}

							if (pri == 0 && Player_card[i].num != 99) {
								pri = 0;
							}

							p_pow = Player_card[i].num;

							Player_card.erase(Player_card.begin() + i);
							priority++;
							flg_p = true;
						}
					}
				}
			}
		}
		else {
			priority++;
		}
		break;
	case 1:				// NPC1
		if (flg_1 == false) {
			//NPCがカード引く用_後で要改造
			if ((Mouse_X > Deck_X - 50) && (Mouse_X < Deck_X + 50) && (Mouse_Y > Deck_Y - 75) && (Mouse_Y < Deck_Y + 75)) {
				if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
					r = GetRand((int)Card_obj.size() - 1);
					NPC_card_1.push_back(Card_obj[r]);
					Card_obj.erase(Card_obj.begin() + r);
				}
			}

			//NPCの手札からカードだす(現在は手動で正確性もあまりよくない)
			for (i = 0; i < NPC_card_1.size(); i++) {
				if (Card::Hit(Mouse_X, Mouse_Y, 150 + (card_w * 0.3) * (i % 5), 75 + (card_h * pow(0.3, 2)) * (i / 5), card_w, card_h, 0.3)) {
					if (Field_card.empty() || Field_card[0].suit == NPC_card_1[i].suit) {
						if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
							Field_card.push_back(NPC_card_1[i]);

							if (NPC_card_1[i].num == 99) {
								pri = 99;
							}

							if (NPC_card_1[i].num == 0) {
								pri = 0;
							}

							if (pri != 0 && pri < NPC_card_1[i].num) {
								pri = NPC_card_1[i].num;
							}

							if (pri == 0 && NPC_card_1[i].num != 99) {
								pri = 0;
							}

							n1_pow = NPC_card_1[i].num;

							NPC_card_1.erase(NPC_card_1.begin() + i);
							priority++;
							flg_1 = true;
						}
					}
				}
			}
		}
		else {
			priority++;
		}
		break;
	case 2:				// NPC2
		priority++;
		break;
	case 3:				// NPC3
		priority++;
		break;
	case 4:
	default:
		// 1や２おわってるか？
		if (flg_p == false || flg_1 == false/* || flg_2 == false || flg_3 == false*/) {
			priority = 0;
		}
		else {
			if (pri == p_pow) {
				priority = 0;
			}
			if (pri == n1_pow) {
				priority = 1;
			}
		}
		flg_p = false;
		flg_1 = false;
		Field_card.erase(Field_card.begin(), Field_card.end());
		break;
	}
	
	DrawFormatString(300, 300, GetColor(255, 255, 255), "priority:%d", priority);

	//if (Player_card.size() == 0 || NPC_card_1.size() == 0) {

	//}
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
	DrawFormatString(50,300,GetColor(255,255,255),"par:%d", pri);
	DrawRotaGraph(Deck_X, Deck_Y, 0.5, 0, Card_back.img, TRUE);

	DrawBox(500, 300, 550, 350, j, TRUE);

}
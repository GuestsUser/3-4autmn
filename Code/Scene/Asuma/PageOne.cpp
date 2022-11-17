#include"PageOne.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"

void PageOne::PageOne_Initialize() {

	LoadDivGraph("Resource/image/toranpu_all.png", 54, 13, 5, 200, 300, card_type);
	background = LoadGraph("Resource/image/CareerPoker.png");
	Pass_Icon = LoadGraph("Resource/image/PageOne_Image/Pass.png");
	PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One.png");

	for (i = 0; i < 52; i++) {
		Card_obj.push_back(Card(card_type[i], i % 13, i / 13));
	}

	Card_obj.push_back(Card(card_type[53], 99, 5));	//ジョーカー

	Card_back = Card(card_type[52], 0, 0);	//カードの裏面

	for (i = 0; i < 6; i++) {
		r = GetRand(sizeof(Card_obj));
		Player_card.push_back(Card_obj[r]);
		Cemetery_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);

		r = GetRand(sizeof(Card_obj));
		NPC_card_1.push_back(Card_obj[r]);
		Cemetery_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);

		r = GetRand(sizeof(Card_obj));
		NPC_card_2.push_back(Card_obj[r]);
		Cemetery_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);

		r = GetRand(sizeof(Card_obj));
		NPC_card_3.push_back(Card_obj[r]);
		Cemetery_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);

	}


	Deck_X = 100;
	Deck_Y = 600;

	Field_X = 500;
	Field_Y = 350;

	Player_X = 300;
	Player_Y = 575;

	NPC1_X = 125;
	NPC1_Y = 75;

	NPC2_X = 550;
	NPC2_Y = 75;

	NPC3_X = 975;
	NPC3_Y = 75;

	n = 0;

	flg_p = false;
	flg_1 = false;
	flg_2 = false;
	flg_3 = false;

	lead = 0;
	pri = 1;
	draw = false;
	finish = false;

	priority = GetRand(MAX - 1);
}

void PageOne::PageOne_Finalize() {
	for (i = 0; i < 54; i++) {
		DeleteGraph(card_type[i]);
	}
}

void PageOne::PageOne_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y);
	DrawRotaGraph(640, 360, 1.0, 0, background, TRUE);

	n++;	//山札からカード引くときのクールタイム（早すぎるとアクセス違反でるから）
	count++;	//手札を出すときのクールタイム

	//デバッグ用
	//color = GetColor(255, 255, 255);

	if (draw == false) {
		DrawFormatString(700, 350, GetColor(255, 255, 255), "カードは引けないよ");
	}
	else {
		DrawFormatString(700, 350, GetColor(255, 255, 255), "カード引いていいよ");
	}

	if (finish == false) {
		switch (priority) {
		case 0:	// player
			DrawFormatString(700, 200, GetColor(255, 255, 255), "手番：プレイヤー");

			if (flg_p == false) {

				if (Field_card.empty() == false && Field_card[0].suit == 5) {
					lead = 1;
				}
				else {
					lead = 0;
				}

				if (Field_card.empty()) {
					draw = false;
				}
				else {
					for (i = 0; i < Player_card.size(); i++) {
						if (Player_card[i].suit == 5) {
							draw = false;
						}
						if (Field_card[lead].suit == Player_card[i].suit) {
							draw = false;
						}
					}
				}

				//プレイヤーがカード引く用
				if (draw == true && Card_obj.empty() == false) {
					if (n > 30) {
						if ((Mouse_X > Deck_X - (card_w * 0.7) / 2) && (Mouse_X < Deck_X + (card_w * 0.7) / 2) && (Mouse_Y > Deck_Y - (card_h * 0.7) / 2) && (Mouse_Y < Deck_Y + (card_h * 0.7) / 2)) {
							if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
								r = GetRand(sizeof(Card_obj));
								Player_card.push_back(Card_obj[r]);
								Card_obj.erase(Card_obj.begin() + r);
								n = 0;
							}

							//デバッグ用
							//color = GetColor(255, 0, 0);
						}
					}
				}

				//プレイヤーの手札からカードだす
				for (i = 0; i < Player_card.size(); i++) {

					//山札0枚＆手札に出せるカードがない場合パスをする
					if (Card_obj.empty() == true && Field_card.empty() == false && Field_card[lead].suit != Player_card[i].suit && Player_card[i].suit != 5) {
						//DrawBox(890, 440, 980, 500, color, TRUE);
						//DrawFormatString(900, 450, GetColor(255, 0, 0), "パス");
						DrawGraph(890, 440, Pass_Icon, true);
						if ((Mouse_X > 890) && (Mouse_X < 1040) && (Mouse_Y > 440) && (Mouse_Y < 515)) {
							if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
								flg_p = true;
								priority++;
								count = 0;
							}
						}
					}
					else {
						if (Field_card.empty() || Field_card[0].suit == 5 || Field_card[lead].suit == Player_card[i].suit || Player_card[i].suit == 5) {
							if (PageOne_flg == true) {
								DrawGraph(500, 400, PageOne_Icon, true);
								if ((Mouse_X > 500) && (Mouse_X < 800) && (Mouse_Y > 400) && (Mouse_Y < 500)) {
									if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
										PageOne_flg = false;
									}
								}
							}
							if (PageOne_flg == false) {
								if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w * 0.5) * (i % 10), Player_Y + (card_h * pow(0.5, 2)) * (i / 10), card_w, card_h, 0.5)) {
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
										p = i;
										priority++;
										draw = true;
										flg_p = true;
										count = 0;

										if (sizeof(Player_card) == 2) {
											PageOne_flg = true;
										}
									}
								}
							}
						}
					}
					if (flg_p == true) {
						Player_card.erase(Player_card.begin() + p);
					}
				}
			}
			else {
				priority++;
			}

			if (Player_card.empty()) {
				break;
			}
			break;

		case 1:	// NPC1
			DrawFormatString(700, 200, GetColor(255, 255, 255), "手番：NPC１号");

			if (flg_1 == false) {

				if (Field_card.empty() == false && Field_card[0].suit == 5) {
					lead = 1;
				}
				else {
					lead = 0;
				}

				if (Field_card.empty()) {
					draw = false;
				}
				else {
					for (i = 0; i < NPC_card_1.size(); i++) {
						if (NPC_card_1[i].suit == 5) {
							draw = false;
						}
						if (Field_card[lead].suit == NPC_card_1[i].suit) {
							draw = false;
						}
					}
				}

				//NPCがカード引く用
				if (draw == true && Card_obj.empty() == false) {
					if (n > 30) {
						r = GetRand(sizeof(Card_obj));
						NPC_card_1.push_back(Card_obj[r]);
						Card_obj.erase(Card_obj.begin() + r);
						n = 0;
					}
				}


				//NPCの手札からカードだす
				for (i = 0; i < NPC_card_1.size(); i++) {

					//山札0枚＆手札に出せるカードがない場合パスをする（手動）
					if (Card_obj.empty() == true && Field_card.empty() == false && Field_card[lead].suit != NPC_card_1[i].suit && NPC_card_1[i].suit != 5) {
						DrawBox(890, 440, 980, 500, color, TRUE);
						DrawFormatString(900, 450, GetColor(255, 0, 0), "パス");
						if ((Mouse_X > 890) && (Mouse_X < 980) && (Mouse_Y > 440) && (Mouse_Y < 500)) {
							if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
								flg_1 = true;
								priority++;
								count = 0;
							}
						}
					}
					else {
						if (count > 90) {

							if (Field_card.empty() || Field_card[0].suit == 5 || Field_card[lead].suit == NPC_card_1[i].suit || NPC_card_1[i].suit == 5) {
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
								n1 = i;
								priority++;
								draw = true;
								flg_1 = true;
								count = 0;
							}
						}
					}
				}
				if (flg_1 == true) {
					NPC_card_1.erase(NPC_card_1.begin() + n1);
				}
			}
			else {
				priority++;
			}

			if (NPC_card_1.empty()) {
				break;
			}
			break;

		case 2:	// NPC2
			DrawFormatString(700, 200, GetColor(255, 255, 255), "手番：NPC２号");

			if (flg_2 == false) {

				if (Field_card.empty() == false && Field_card[0].suit == 5) {
					lead = 1;
				}
				else {
					lead = 0;
				}

				if (Field_card.empty()) {
					draw = false;
				}
				else {
					for (i = 0; i < NPC_card_2.size(); i++) {
						if (NPC_card_2[i].suit == 5) {
							draw = false;
						}
						if (Field_card[lead].suit == NPC_card_2[i].suit) {
							draw = false;
						}
					}
				}

				//NPCがカード引く用
				if (draw == true && Card_obj.empty() == false) {
					if (n > 30) {
						r = GetRand(sizeof(Card_obj));
						NPC_card_2.push_back(Card_obj[r]);
						Card_obj.erase(Card_obj.begin() + r);
						n = 0;
					}
				}


				//NPCの手札からカードだす
				for (i = 0; i < NPC_card_2.size(); i++) {

					//山札0枚＆手札に出せるカードがない場合パスをする（手動）
					if (Card_obj.empty() == true && Field_card.empty() == false && Field_card[lead].suit != NPC_card_2[i].suit && NPC_card_2[i].suit != 5) {
						DrawBox(890, 440, 980, 500, color, TRUE);
						DrawFormatString(900, 450, GetColor(255, 0, 0), "パス");
						if ((Mouse_X > 890) && (Mouse_X < 980) && (Mouse_Y > 440) && (Mouse_Y < 500)) {
							if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
								flg_2 = true;
								priority++;
								count = 0;
							}
						}
					}
					else {
						if (count > 90) {
							if (Field_card.empty() || Field_card[0].suit == 5 || Field_card[lead].suit == NPC_card_2[i].suit || NPC_card_2[i].suit == 5) {
								Field_card.push_back(NPC_card_2[i]);

								if (NPC_card_2[i].num == 99) {
									pri = 99;
								}

								if (NPC_card_2[i].num == 0) {
									pri = 0;
								}

								if (pri != 0 && pri < NPC_card_2[i].num) {
									pri = NPC_card_2[i].num;
								}

								if (pri == 0 && NPC_card_2[i].num != 99) {
									pri = 0;
								}

								n2_pow = NPC_card_2[i].num;
								n2 = i;
								priority++;
								draw = true;
								flg_2 = true;
								count = 0;
							}
						}
					}
				}
				if (flg_2 == true) {
					NPC_card_2.erase(NPC_card_2.begin() + n2);
				}
			}
			else {
				priority++;
			}

			if (NPC_card_2.empty()) {
				break;
			}
			break;

		case 3:	// NPC3
			DrawFormatString(700, 200, GetColor(255, 255, 255), "手番：NPC３号");

			if (flg_3 == false) {

				if (Field_card.empty() == false && Field_card[0].suit == 5) {
					lead = 1;
				}
				else {
					lead = 0;
				}

				if (Field_card.empty()) {
					draw = false;
				}
				else {
					for (i = 0; i < NPC_card_3.size(); i++) {
						if (NPC_card_3[i].suit == 5) {
							draw = false;
						}
						if (Field_card[lead].suit == NPC_card_3[i].suit) {
							draw = false;
						}
					}
				}

				//NPCがカード引く用
				if (draw == true && Card_obj.empty() == false) {
					if (n > 30) {
						r = GetRand(sizeof(Card_obj));
						NPC_card_3.push_back(Card_obj[r]);
						Card_obj.erase(Card_obj.begin() + r);
						n = 0;
					}
				}

				//NPCの手札からカードだす
				for (i = 0; i < NPC_card_3.size(); i++) {

					//山札0枚＆手札に出せるカードがない場合パスをする（手動）
					if (Card_obj.empty() == true && Field_card.empty() == false && Field_card[lead].suit != NPC_card_3[i].suit && NPC_card_3[i].suit != 5) {
						DrawBox(890, 440, 980, 500, color, TRUE);
						DrawFormatString(900, 450, GetColor(255, 0, 0), "パス");
						if ((Mouse_X > 890) && (Mouse_X < 980) && (Mouse_Y > 440) && (Mouse_Y < 500)) {
							if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
								flg_3 = true;
								priority++;
								count = 0;
							}
						}
					}
					else {
						if (count > 90) {
							if (Field_card.empty() || Field_card[0].suit == 5 || Field_card[lead].suit == NPC_card_3[i].suit || NPC_card_3[i].suit == 5) {
								Field_card.push_back(NPC_card_3[i]);

								if (NPC_card_3[i].num == 99) {
									pri = 99;
								}

								if (NPC_card_3[i].num == 0) {
									pri = 0;
								}

								if (pri != 0 && pri < NPC_card_3[i].num) {
									pri = NPC_card_3[i].num;
								}

								if (pri == 0 && NPC_card_3[i].num != 99) {
									pri = 0;
								}

								n3_pow = NPC_card_3[i].num;

								n3 = i;
								priority++;
								draw = true;
								flg_3 = true;
								count = 0;
							}
						}
					}
				}
				if (flg_3 == true) {
					NPC_card_3.erase(NPC_card_3.begin() + n3);
				}
			}
			else {
				priority++;
			}

			if (NPC_card_3.empty()) {
				break;
			}
			break;

		case 4:
		default:
			// 全員の手番がおわってるか？
			if (flg_p == false || flg_1 == false || flg_2 == false || flg_3 == false) {
				priority = 0;
			}
			else {
				if (count < 90) {
					count++;
				}
				else if (count < 180) {
					Field_X += 20;
					count++;
				}
				else {

					if (pri == p_pow) {
						priority = 0;
						pri = 1;
					}
					if (pri == n1_pow) {
						priority = 1;
						pri = 1;
					}
					if (pri == n2_pow) {
						priority = 2;
						pri = 1;
					}
					if (pri == n3_pow) {
						priority = 3;
						pri = 1;
					}

					flg_p = false;
					flg_1 = false;
					flg_2 = false;
					flg_3 = false;

					for (i = 0; i < 4; i++) {
						Cemetery_card.push_back(Field_card[i]);
					}

					Field_card.erase(Field_card.begin(), Field_card.end());
					Field_X = 500;
					if (Card_obj.empty() == true) {
						Card_obj = Cemetery_card;
						Cemetery_card.erase(Cemetery_card.begin(), Cemetery_card.end());
					}

					count = 0;
				}

			}
			break;
		}
	}

	if (Player_card.size() == 0) {
		DrawFormatString(500, 500, GetColor(255, 255, 255), "PLAYER_WIN");
		finish = true;
	}
	if (NPC_card_1.size() == 0) {
		DrawFormatString(500, 500, GetColor(255, 255, 255), "NPC1_WIN");
		finish = true;
	}
	if (NPC_card_2.size() == 0) {
		DrawFormatString(500, 500, GetColor(255, 255, 255), "NPC2_WIN");
		finish = true;
	}
	if (NPC_card_3.size() == 0) {
		DrawFormatString(500, 500, GetColor(255, 255, 255), "NPC3_WIN");
		finish = true;
	}
}

void PageOne::PageOne_Draw() {
	field = 0;
	player = 0;
	npc_1 = 0;
	npc_2 = 0;
	npc_3 = 0;

	//DrawRotaGraph(640, 360, 1.0, 0, background, TRUE);

	//山札の描画
	if (Card_obj.empty() == false) {
		DrawRotaGraph(Deck_X, Deck_Y, 0.7, 0, Card_back.img, TRUE);
	}

	//場に出ているカードの描画
	for (i = 0; i < Field_card.size(); i++) {
		DrawRotaGraph(Field_X + field * 100, Field_Y, 0.5, 0, Field_card[i].img, TRUE);
		field++;
	}

	//プレイヤーの手札描画
	for (i = 0; i < Player_card.size(); i++) {
		DrawRotaGraph(Player_X + (player % 10) * (card_w * 0.5), Player_Y + (player / 10) * (card_h * pow(0.5, 2)), 0.5, 0, Player_card[i].img, TRUE);
		player++;
	}

	//NPC１号の手札描画
	for (i = 0; i < NPC_card_1.size(); i++) {
		//DrawRotaGraph(NPC1_X + (npc_1 % 5) * (card_w * 0.3), NPC1_Y + (npc_1 / 5) * (card_h * 0.3), 0.3, 0, Card_back.img, TRUE);
		DrawRotaGraph(NPC1_X + (npc_1 % 5) * (card_w * 0.3), NPC1_Y + (npc_1 / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_1[i].img, TRUE);
		npc_1++;
	}

	//NPC２号の手札描画
	for (i = 0; i < NPC_card_2.size(); i++) {
		//DrawRotaGraph(NPC2_X + (npc_2 % 5) * (card_w * 0.3), NPC2_Y + (npc_2 / 5) * (card_h * 0.3), 0.3, 0, Card_back.img, TRUE);
		DrawRotaGraph(NPC2_X + (npc_2 % 5) * (card_w * 0.3), NPC2_Y + (npc_2 / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_2[i].img, TRUE);
		npc_2++;
	}

	//NPC３号の手札描画
	for (i = 0; i < NPC_card_3.size(); i++) {
		//DrawRotaGraph(NPC3_X + (npc_3 % 5) * (card_w * 0.3), NPC3_Y + (npc_3 / 5) * (card_h * 0.3), 0.3, 0, Card_back.img, TRUE);
		DrawRotaGraph(NPC3_X + (npc_3 % 5) * (card_w * 0.3), NPC3_Y + (npc_3 / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_3[i].img, TRUE);
		npc_3++;
	}

	DrawFormatString(25, 50, GetColor(255, 255, 255), "NPC");
	DrawFormatString(25, 75, GetColor(255, 255, 255), "１号");

	DrawFormatString(450, 50, GetColor(255, 255, 255), "NPC");
	DrawFormatString(450, 75, GetColor(255, 255, 255), "２号");

	DrawFormatString(875, 50, GetColor(255, 255, 255), "NPC");
	DrawFormatString(875, 75, GetColor(255, 255, 255), "３号");

	DrawFormatString(700, 250, GetColor(255, 255, 255), "デッキ枚数:%d", Card_obj.size());
	DrawFormatString(700, 300, GetColor(255, 255, 255), "par:%d", pri);

	//デバッグ用
	//DrawBox(890, 440,980, 500, color, TRUE);
	//DrawFormatString(900, 450, GetColor(255, 0, 0), "パス");
	//DrawGraph(890, 430, Pass_Icon, true);
	//DrawGraph(500, 400, PageOne_Icon, true);
}
#include"DxLib.h"
#include"CP_Player.h"
#include"./../Code/GetKey.h"
//大富豪プレイヤー


void CareerPoker::CP_Player_Initialize(){
	//rule = LoadGraph("Code/Scene/daifugou/images/rule.png");//ルール画像
	stage = LoadGraph("Resource/image/CareerPoker.png");//背景画像
	LoadDivGraph("Resource/image/toranpu_all.png",53,13,5,200,300, card_type,TRUE);
	for (i = 0; i < 52; i++) {
		Card_obj.push_back(C(card_type[i], i % 13, i / 13));
	}
	Card_back = C(card_type[52], 0, 5);	//カードの裏面
	Card_joker = C(card_type[53], 99, 5);	//ジョーカー

	for (i = 0; i < 13; i++) {
		r = GetRand(sizeof(Card_obj));//ランドでカードオブジェのなんでもいいからデータを持ってくる
		Player_card.push_back(Card_obj[r]);//手札の配列にブチこぶ
		Card_obj.erase(Card_obj.begin() + r);//選んだ奴消してる
	}


	Player_X = 150;
	Player_Y = 575;
	Player_state = 0;
}



void CareerPoker::CP_Player_Finalize() {
	DeleteGraph(stage);
	for (i = 0; i < 53; i++) {
		DeleteGraph(card_type[i]);
	}
}



int Color;

void CareerPoker::CP_Player_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y);

	for (i = 1, j = 0; i < 5; j++) {//ダイヤの3からスタート
		if (j == 4) {
			j = 0;
			i++;
		}
		if (Player_card[i].suit || Player_card[2].num) {
			break;
		}
		order[0] = j;
		for (i = 1, j = +1; i <= 3; i++, j++) {
			if (j == 4) {
				j = 0;
				order[0] = j;
			}
		}
	}
	//if(C::Hit(Mouse_X, Mouse_Y, Player_X + (n%13) * (card_w * 0.3), Player_Y + (card_h * 0.3), card_w, card_h, 0.3)){
	if (Mouse_X > 100 && Mouse_X < 200 && Mouse_Y > 100 && Mouse_Y < 200) {
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
			r = GetRand(Card_obj.size() - 1);
			Player_card.push_back(Card_obj[r]);
			Card_obj.erase(Card_obj.begin() + r);
			n = 0;
		}
		Color = GetColor(255, 0, 0);

	}
	else {
		Color = GetColor(255, 255, 255);

	}
	switch (i)
	{
	default:
		break;
	}
	//プレイヤーの手札からカードだす
	for (i = 0; i < Player_card.size(); i++) {
		if (C::Hit(Mouse_X, Mouse_Y, Player_X + (card_w * 0.3) * (i % 13), Player_Y + (card_h * 0.3), card_w, card_h, 0.3)) {
			switch (i)
			{
			case 0:
				Color = GetColor(255, 0, 0);//R

				break;
			case 1:
				Color = GetColor(255, 0, 255);//P

				break;
			case 2:
				Color = GetColor(255, 255, 0);//Y


				break;
			case 3:
				Color = GetColor(0, 255, 255);//S

				break;
			default:
				Color = GetColor(0, 0, 255);//B

				break;
			}
			switch (Player_state) {
			case 0:
				DrawFormatString(700, 200, GetColor(255, 255, 255), "手番：プレイヤー");
				if (Field_card.empty() || Field_card[0].suit || Player_card[i].suit) {//適当に出せる
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
						Player_card.erase(Player_card.begin() + i);
					}
				}
				break;
			case 1:
				if (Field_card.empty() || Field_card[0].suit == Player_card[i].suit) {//スート縛り用
					DrawFormatString(700, 200, GetColor(255, 255, 255), "スートで縛るよ");
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


						Player_card.erase(Player_card.begin() + i);

					}
				}
				break;
			case 2:
				if (Field_card.empty() == Player_card[8].num) {//八切がしたい
					if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
						Field_card.push_back(Player_card[i]);
						Player_card.erase(Player_card.begin() + i);
						if (Player_card[8].num) {//8のトランプだったら場が流れる
							DrawFormatString(700, 200, GetColor(255, 255, 255), "八でぶったぎるよ～");
							break;
						}
					}
				}
			}
		}
	}
}
	/*if (C::Hit(Mouse_X, Mouse_Y, Player_X, Player_Y, card_w, card_h)) {
		j = GetColor(255, 0, 0);
	}
	else {
		j = GetColor(0, 0, 255);
	}*/

void CareerPoker::CP_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0 , 0, stage, TRUE);
	int field = 0;
	int i = 0;
	for (auto itr = Player_card.begin(); itr != Player_card.end(); itr++) {
		DrawRotaGraph(Player_X + i * (card_w * 0.3), Player_Y + (card_h * 0.3), 0.3, 0, (*itr).img, TRUE);
		i++;
	}

	for (i = 0; i < Field_card.size(); i++) {
		DrawRotaGraph(500 + field * 100, 350, 0.5, 0, Field_card[i].img, TRUE);
		field++;
		if (Field_card.empty() || Field_card[0].suit || Player_card[i].suit) {
			//DrawFormatString(700, 200, GetColor(255, 255, 255), "適当に出せる");
		}else if(Field_card.empty() || Field_card[0].suit == Player_card[8].num){
			DrawFormatString(700, 200, GetColor(255, 255, 255), "八切り");
		}
			//DrawFormatString(700, 200, GetColor(255, 255, 255), "二が出たよ");
	}
	DrawBox(100, 100, 200, 200, Color, TRUE);
}


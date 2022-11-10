#include"DxLib.h"
#include"CP_Player.h"
#include"./../Code/GetKey.h"
//大富豪プレイヤー



void CareerPoker::CP_Player_Initialize(){
	//rule = LoadGraph("Code/Scene/daifugou/images/rule.png");//ルール画像
	stage = LoadGraph("Resource/image/CareerPoker.png");//背景画像
	LoadDivGraph("Resource/image/toranpu_all.png",53,13,5,200,300, card_type,TRUE);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 51; j++) {
			Card_obj.push_back(C(card_type[i + j], j, i));
		}
	}
	Card_back = C(card_type[52], 0, 5);	//カードの裏面
	Card_joker = C(card_type[53], 99, 5);	//ジョーカー

	for (i = 0; i < 13; i++) {
		r = GetRand(Card_obj.size());
		Player_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);
	}


	Player_X = 150;
	Player_Y = 575;
}
void CareerPoker::onesec(void) {
	time_t t1;
	srand(time(NULL));

	t1 = time(NULL);
	while (1 != time(NULL) - t1);
}

void CareerPoker::CP_Player_Finalize() {
	DeleteGraph(stage);
	for (i = 0; i < 53; i++) {
		DeleteGraph(card_type[i]);
	}
}

void CareerPoker::deckmake() {
	int i;
	for (i = 0; i <= 53; i++)
		T_cards[i] = i + 1;
}
int Color;
void CareerPoker::CP_Player_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y);

	for (n = 0; n < 13; n++) {
		//if(C::Hit(Mouse_X, Mouse_Y, Player_X + (n%13) * (card_w * 0.3), Player_Y + (card_h * 0.3), card_w, card_h, 0.3)){
		if(Mouse_X>100 && Mouse_X < 200 && Mouse_Y > 100 && Mouse_Y < 200){
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
				r = GetRand(Card_obj.size());
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

	}
	/*if (C::Hit(Mouse_X, Mouse_Y, Player_X, Player_Y, card_w, card_h)) {
		j = GetColor(255, 0, 0);
	}
	else {
		j = GetColor(0, 0, 255);
	}*/
}

void CareerPoker::CP_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0 , 0, stage, TRUE);
	
	int i = 0;
	for (auto itr = Player_card.begin(); itr != Player_card.end(); itr++) {
		DrawRotaGraph(Player_X + i * (card_w * 0.3), Player_Y + (card_h * 0.3), 0.3, 0, (*itr).img, TRUE);
		i++;
	}
	DrawBox(100, 100, 200, 200, Color, TRUE);
}


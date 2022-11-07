#include"DxLib.h"
#include"CP_Player.h"
#include"./../Code/GetKey.h"
//大富豪プレイヤー



void CareerPoker::CP_Player_Initialize(){
	//rule = LoadGraph("Code/Scene/daifugou/images/rule.png");//ルール画像
	stage = LoadGraph("Resource/image/CareerPoker.png");//背景画像
	LoadDivGraph("Resource/image/toranpu_all.png",53,13,5,200,300, card_type,TRUE);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 51; j++) {
			Card_obj.push_back(C(card_type[i + j], j, i));
		}
	}
	Card_back = C(card_type[52], 0, 5);	//カードの裏面
	Card_joker = C(card_type[53], 99, 5);	//ジョーカー

	for (i = 0; i < 13; i++) {
		r = GetRand(sizeof(Card_obj));
		Player_card.push_back(Card_obj[r]);
		Card_obj.erase(Card_obj.begin() + r);
	}
}

void CareerPoker::CP_Player_Finalize() {
	DeleteGraph(stage);
	for (i = 0; i < 54; i++) {
		DeleteGraph(card_type[i]);
	}
}

void CareerPoker::deckmake() {
	int i;
	for (i = 0; i <= 53; i++)
		T_cards[i] = i + 1;
}

void CareerPoker::CP_Player_Update() {
	
}

void CareerPoker::CP_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0 , 0, stage, TRUE);
	int i = 0;
	for (auto itr = Player_card.begin(); itr != Player_card.end(); itr++) {
		DrawRotaGraph(100 + i * 45, 500, 0.3, 0, (*itr).img, TRUE);
		i++;
	}
}


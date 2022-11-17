#include"DxLib.h"
#include"CP_Player.h"
#include"./../Code/GetKey.h"
//大富豪プレイヤー

struct player {
	char name[20]; /* 名前 */
	int hand[15]; /* 手札 */
	int fin; /* 終了 */
	int pass; /* パス */
};

struct player data[4] = {
{"あなた",0,0,0},
{"NP1" ,0,0,0},
{"NP2" ,0,0,0},
{"NP3" ,0,0,0},
};

int num(int num_x) {
	int x;
	x = (num_x - 1) % 13 + 1;
	return x;
}
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

void CareerPoker::datareset(void) {
	data[0].fin = data[1].fin = data[2].fin = data[3].fin = 0;
	data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0;
	pc = -1;
}
void CareerPoker::deckshuffle(void){
	/* 山札をシャッフル */
	int i, x, y, z;
	for (i = 0; i < 500; i++) {
		x = rand() % 54;
		y = rand() % 54;
		z = *cards[x];
		*cards[x] = *cards[y];
		*cards[y] = z;
	}
	onesec();
	printf("山札をシャッフルしました\n");
}
int Color;

void CareerPoker::CP_Player_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y);

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
			/*switch (i)
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
			}*/

			if (Field_card.empty() || Field_card[0].suit == Player_card[i].suit) {
				if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
					Field_card.push_back(Player_card[i]);

					/*if (Player_card[i].num == 99) {
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
					}*/


					Player_card.erase(Player_card.begin() + i);

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
}
void CareerPoker::expend(int n) {
	/* 手札がなくなった場合 */
	int i;

	if (data[n].hand[0] == 0) {
		onesec();
		data[n].fin = 1;
		for (i = 1; i <= trash[0]; i++) {
			if (num - (trash[i]) == 8 ||(trash[i]) == 'J') {
				printf("%sは反則あがりました\n", data[n].name);
				break;
			}
			if (i == trash[0])
				printf("%sはあがりました\n", data[n].name);
		}
	}
}
void CareerPoker::slash8(int n) {
/* 8切り */
	int i;

	for (i = 1; i <= trash[0]; i++) {
		if (num - (trash[i]) == 8) {
			pc = n;
			data[0].pass = data[1].pass = data[2].pass = data[3].pass = 1;
			data[n].pass = 0;
			break;
		}
	}
}

void  CareerPoker::phase(int n) {
	/* ターンが回ってくる前に行う動作 */

	/* 自分がトラッシュに出したカードが換わらずに1週してきたら */
	if (n == pc) {
		onesec();
		//printf("場が流れました\n\n");
		pc = -1;
		//eback = 0; /* 11バックをリセット */
		trash[0] = 0; /* ﾄﾗｯｼｭをリセット */
		data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0; /* パスをリセット */
	}
}

void CareerPoker::pl_routine(int n) {
	/* プレイヤー用 */
	int i;


	/* 0で決定、選択しているカードが真か関数judgに送る */
	while (1) {

		/* 入力処理 */
		cards[0][0] = 0;
		i = 1;
		while (1) {
			printf("%2d枚目のカード : ", i);
			scanf_s("%d", &cards[0][i]);
			if (cards[0][i] == 0)
				break;
			cards[0][0]++;
			i++;
		}
		/* 初めから0が入力されたら */
		if (cards[0][0] == 0) {
			//printf("→%sはパスしました\n", data[n].name);
			data[n].pass++;
			break;
		}
	}
}

void CareerPoker::turn(int n) {

	phase(n);

	if (data[n].fin == 0 && data[n].pass == 0) {

		if (n == 0)
			pl_routine(n);
		else
			//cp_routine(n);

		expend(n);
		slash8(n);
	}
}

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
		DrawFormatString(700, 200, GetColor(255, 255, 255), "スート縛り中(何で？？)	");
		//if (Field_card[i].img == Card_obj[0]) {
			//DrawFormatString(700, 200, GetColor(255, 255, 255), "二が出たよ");
	}
	DrawBox(100, 100, 200, 200, Color, TRUE);
}


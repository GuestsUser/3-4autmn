#include"DxLib.h"
#include"CP_Player.h"
#include"./../Code/GetKey.h"
//��x���v���C���[

struct player {
	char name[20]; /* ���O */
	int hand[15]; /* ��D */
	int fin; /* �I�� */
	int pass; /* �p�X */
};

struct player data[4] = {
{"���Ȃ�",0,0,0},
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
	//rule = LoadGraph("Code/Scene/daifugou/images/rule.png");//���[���摜
	stage = LoadGraph("Resource/image/CareerPoker.png");//�w�i�摜
	LoadDivGraph("Resource/image/toranpu_all.png",53,13,5,200,300, card_type,TRUE);
	for (i = 0; i < 52; i++) {
		Card_obj.push_back(C(card_type[i], i % 13, i / 13));
	}
	Card_back = C(card_type[52], 0, 5);	//�J�[�h�̗���
	Card_joker = C(card_type[53], 99, 5);	//�W���[�J�[

	for (i = 0; i < 13; i++) {
		r = GetRand(sizeof(Card_obj));//�����h�ŃJ�[�h�I�u�W�F�̂Ȃ�ł���������f�[�^�������Ă���
		Player_card.push_back(Card_obj[r]);//��D�̔z��Ƀu�`����
		Card_obj.erase(Card_obj.begin() + r);//�I�񂾓z�����Ă�
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
	/* �R�D���V���b�t�� */
	int i, x, y, z;
	for (i = 0; i < 500; i++) {
		x = rand() % 54;
		y = rand() % 54;
		z = *cards[x];
		*cards[x] = *cards[y];
		*cards[y] = z;
	}
	onesec();
	printf("�R�D���V���b�t�����܂���\n");
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
	//�v���C���[�̎�D����J�[�h����
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
	/* ��D���Ȃ��Ȃ����ꍇ */
	int i;

	if (data[n].hand[0] == 0) {
		onesec();
		data[n].fin = 1;
		for (i = 1; i <= trash[0]; i++) {
			if (num - (trash[i]) == 8 ||(trash[i]) == 'J') {
				printf("%s�͔���������܂���\n", data[n].name);
				break;
			}
			if (i == trash[0])
				printf("%s�͂�����܂���\n", data[n].name);
		}
	}
}
void CareerPoker::slash8(int n) {
/* 8�؂� */
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
	/* �^�[��������Ă���O�ɍs������ */

	/* �������g���b�V���ɏo�����J�[�h������炸��1�T���Ă����� */
	if (n == pc) {
		onesec();
		//printf("�ꂪ����܂���\n\n");
		pc = -1;
		//eback = 0; /* 11�o�b�N�����Z�b�g */
		trash[0] = 0; /* �ׯ�������Z�b�g */
		data[0].pass = data[1].pass = data[2].pass = data[3].pass = 0; /* �p�X�����Z�b�g */
	}
}

void CareerPoker::pl_routine(int n) {
	/* �v���C���[�p */
	int i;


	/* 0�Ō���A�I�����Ă���J�[�h���^���֐�judg�ɑ��� */
	while (1) {

		/* ���͏��� */
		cards[0][0] = 0;
		i = 1;
		while (1) {
			printf("%2d���ڂ̃J�[�h : ", i);
			scanf_s("%d", &cards[0][i]);
			if (cards[0][i] == 0)
				break;
			cards[0][0]++;
			i++;
		}
		/* ���߂���0�����͂��ꂽ�� */
		if (cards[0][0] == 0) {
			//printf("��%s�̓p�X���܂���\n", data[n].name);
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
		DrawFormatString(700, 200, GetColor(255, 255, 255), "�X�[�g���蒆(���ŁH�H)	");
		//if (Field_card[i].img == Card_obj[0]) {
			//DrawFormatString(700, 200, GetColor(255, 255, 255), "�񂪏o����");
	}
	DrawBox(100, 100, 200, 200, Color, TRUE);
}


#pragma once
#include <list>
#include <vector>

class Card {
public:
	int img;	//�摜�p�̕ϐ�
	int num;	//�J�[�h�̐���
	int suit;	//�J�[�h�̃X�[�g(�}�[�N)

	//Card(�摜�A���l�A�X�[�g�A�g�p�t���O)
	Card(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};

class PageOne{
public:

	Card Card_back;		//�J�[�h�̗��ʂ̏��
	Card Card_joker;	//�W���[�J�[�̏��

	std::vector<Card> Card_obj;		//�S�J�[�h�̏��
	std::list<Card> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��

	int card_type[65];	//�摜�p�n���h��

	int CF_Back;
	int CF_Panel;
	int CF_PCoin;
	int CF_CCoin;
	int CF_Yajirusi;

	float Yajirusi_Move;
	float Yajirusi_Y;

	int Yajirusi_Col[7];
	int Mouse_X; //�}�E�X��X���W
	int Mouse_Y; //�}�E�X��Y���W
	int Player_X; //�v���C���[��X���W
	int Player_Y; //�v���C���[��Y���W

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

	int i;
	int j;
	int r;
};

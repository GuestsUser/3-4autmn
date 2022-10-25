#pragma once
#include <list>

class Card {
public:
	int img;	//�摜�p�̕ϐ�
	int num;	//�J�[�h�̐���
	int suit;	//�J�[�h�̃X�[�g(�}�[�N)
	bool flg;	//�g�p�������ǂ���(false:�g���ĂȂ��@true:�g���Ă�)

	//Card(�摜�A���l�A�X�[�g�A�g�p�t���O)
	Card(int i, int n, int s, bool f) {
		img = i;
		num = n;
		suit = s;
		flg = f;
	}
};

class PO_Player {
private:

	Card Card_obj[54];	//�J�[�h�̏��

	std::list<Card> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��

	int card_type[65];	//�摜�p�n���h��

	int i;

	float Yajirusi_Move;
	float Yajirusi_Y;

	int Yajirusi_Col[7];
	int Mouse_X; //�}�E�X��X���W
	int Mouse_Y; //�}�E�X��Y���W
	int Player_X; //�v���C���[��X���W
	int Player_Y; //�v���C���[��Y���W
public:
	void PO_Player_Initialize();
	void PO_Player_Finalize();
	void PO_Player_Update();
	void PO_Player_Draw();
};
//
//extern CF_Player cf_player;
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

class PageOne {
private:

	int card_type[54];	//�摜�p�n���h��
	Card Card_back;		//�J�[�h�̗��ʂ̏��
	Card Card_joker;	//�W���[�J�[�̏��

	Card Card_obj[4][13];		//�S�J�[�h�̏��
	//std::vector<Card> Card_obj;		//�S�J�[�h�̏��
	std::list<Card> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��

	int i;
	int j;
	int r;
	int n;

public:

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

};

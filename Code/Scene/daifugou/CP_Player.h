#pragma once
#include<random>
#include<algorithm>
#include <vector>
#include <list>

class C{
public:
	C() {}

	int img;	//�摜�p�̕ϐ�
	int num;	//�J�[�h�̐���
	int suit;	//�J�[�h�̃X�[�g(�}�[�N)

	//Card(�摜�A���l�A�X�[�g�A�g�p�t���O)
	C(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};
class CareerPoker {
private:
	int i, x, r, j;
	int rule;//���[���̉摜
	int stage;//�X�e�[�W�̉摜
	int T_cards[54];//�R�D
	int cards[5][13];//�g�����v�摜
	int hand[15];//��D
	int order[4];//�N����n�߂邩
	int pass;//�ς�
	int rev;//�v��

	int card_type[54];	//�摜�p�n���h��

	C Card_back;		//�J�[�h�̗��ʂ̏��
	C Card_joker;	//�W���[�J�[�̏��

	//Card Card_obj[4][13];		//�S�J�[�h�̏��
	std::vector<C> Card_obj;		//�S�J�[�h�̏��
	std::list<C> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��
	
public:
	void CP_Player_Initialize();
	void CP_Player_Finalize();
	void CP_Player_Update();
	void CP_Player_Draw();
	void deckmake();
	
};
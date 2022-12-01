#pragma once
#include<random>
#include<algorithm>
#include<time.h>
#include <vector>
#include <list>
#define MAX (4U)

class C{
public:
	C() {}

	int card_w = 200;	//�J�[�h�P���̕�
	int card_h = 300;	//�J�[�h�P���̍���
	int img;	//�摜�p�̕ϐ�
	int num;	//�J�[�h�̐���
	int suit;	//�J�[�h�̃X�[�g(�}�[�N)

	bool Hit(int mx, int my, int cx, int cy, int cw, int ch, double ExRate) {
		if (mx > cx - (cw * ExRate) / 2 && mx < cx + (cw * ExRate) / 2 && my > cy - (ch * ExRate) / 2 && my < cy + (ch * ExRate) / 2) {
			return true;
		}
		else {
			return false;
		}
	}

	//Card(�摜�A���l�A�X�[�g�A�g�p�t���O)
	C(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};
class CareerPoker : public C{
private:
	int pri = 1;
	int i, x, r, j;
	int n;
	int rule;//���[���̉摜
	int stage;//�X�e�[�W�̉摜
	int cards[5][13];//�g�����v�摜
	int hand[15];//��D
	int Player_state;//switch���p�̂Ȃ�

	int T_cards[54];//�R�D
	int order[4];//�N����n�߂邩
	int trash[15] = { 0 };//�̂ĎD
	int rev = 0;//�v��
	
	
	
	int pass;//�ς�
	int pc = -1; //�Ō�ɒN���o�������J�E���g
	int Mouse_X;	//�}�E�X��X���W
	int Mouse_Y;    //�}�E�X��Y���W
	int Player_X;
	int Player_Y;
	int player;
	int card_type[54];	//�摜�p�n���h��


	C Card_back;		//�J�[�h�̗��ʂ̏��
	C Card_joker;	//�W���[�J�[�̏��

	//Card Card_obj[4][13];		//�S�J�[�h�̏��
	std::vector<C> Card_obj;		//�S�J�[�h�̏��E�摜�̏��E�}�[�N�̏��E�����̏��
	std::vector<C> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��
	std::vector<C> Field_card;  //��ɏo������

public:
	void CP_Player_Initialize();
	void CP_Player_Finalize();
	void CP_Player_Update();
	void CP_Player_Draw();	
};

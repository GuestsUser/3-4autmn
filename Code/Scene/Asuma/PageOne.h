#pragma once
#include <vector>

#define SWAP(type,a,b)          { type work = a; a = b; b = work; }

class Card {
public:
	Card(){}

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

	//Card(�摜�A���l�A�X�[�g)
	Card(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};

class PageOne : public Card{
private:
	enum Priority {PLAYER, NPC1, NPC2, NPC3};	//�e�����߂�D��x
	Priority pri;
	int priority[4];

	int card_type[54];	//�摜�p�n���h��
	
	Card Card_back;		//�J�[�h�̗��ʂ̏��
	Card Card_joker;	//�W���[�J�[�̏��

	//Card Card_obj[4][13];		//�S�J�[�h�̏��
	std::vector<Card> Card_obj;		//�S�J�[�h�̏��
	std::vector<Card> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��

	std::vector<Card> Field_card;		//��ɏo�Ă���J�[�h

	std::vector<Card> NPC_card_1;		//NPC�P���̎����Ă���J�[�h�̏��
	std::vector<Card> NPC_card_2;		//NPC�Q���̎����Ă���J�[�h�̏��
	std::vector<Card> NPC_card_3;		//NPC�R���̎����Ă���J�[�h�̏��

	int field;

	int par;

	int player;
	bool flg_p;

	int npc_1;
	bool flg_1;

	int npc_2;
	bool flg_2;

	int npc_3;
	bool flg_3;

	int i;
	int j;
	int r;
	int n;
	int c;

	int Mouse_X;	//�}�E�X��X���W
	int Mouse_Y;	//�}�E�X��Y���W
	
	int Deck_X;		//�R�D��X���W
	int Deck_Y;		//�R�D��Y���W

	int Player_X;		//�v���C���[�̎�D��X���W
	int Player_Y;		//�v���C���[�̎�D��Y���W

	void random_shuffle(int* array, size_t size)
	{
		for (size_t i = size; i > 1; --i) {
			size_t a = i - 1;
			size_t b = rand() % i;
			SWAP(int, array[a], array[b]);
		}
	}

public:
	PageOne() {}

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

};

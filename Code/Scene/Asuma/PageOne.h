#pragma once
#include <list>
#include <vector>

class Card {
public:
	Card(){}

	int card_w = 200;	//�J�[�h�P���̕�
	int card_h = 300;	//�J�[�h�P���̍���

	int img;	//�摜�p�̕ϐ�
	int num;	//�J�[�h�̐���
	int suit;	//�J�[�h�̃X�[�g(�}�[�N)

	bool Hit(int mx, int my, int cx, int cy, int cw, int ch) {
		if (mx > cx - (cw / 2) && mx < cx + (cw / 2) && my > cy - (ch / 2) && my < cy + (ch / 2)) {
			return true;
		}
		else {
			return false;
		}
	}

	//Card(�摜�A���l�A�X�[�g�A�g�p�t���O)
	Card(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};

class PageOne : public Card{
private:

	int card_type[54];	//�摜�p�n���h��
	
	Card Card_back;		//�J�[�h�̗��ʂ̏��
	Card Card_joker;	//�W���[�J�[�̏��

	//Card Card_obj[4][13];		//�S�J�[�h�̏��
	std::vector<Card> Card_obj;		//�S�J�[�h�̏��
	std::list<Card> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��

	std::list<Card> NPC_card_1;		//NPC�P���̎����Ă���J�[�h�̏��
	std::list<Card> NPC_card_2;		//NPC�Q���̎����Ă���J�[�h�̏��
	std::list<Card> NPC_card_3;		//NPC�R���̎����Ă���J�[�h�̏��

	int player;
	int npc_1;
	int npc_2;
	int npc_3;

	int i;
	int j;
	int r;
	int n;

	int Mouse_X;	//�}�E�X��X���W
	int Mouse_Y;	//�}�E�X��Y���W
	
	int Deck_X;		//�R�D��X���W
	int Deck_Y;		//�R�D��Y���W

	int Player_X;		//�v���C���[�̎�D��X���W
	int Player_Y;		//�v���C���[�̎�D��Y���W

public:
	PageOne() {}

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

};

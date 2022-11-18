#pragma once
#include <vector>

#define MAX (4U)

class Card {
public:
	Card() {}

	int card_w = 200;	//�J�[�h�P���̕�
	int card_h = 300;	//�J�[�h�P���̍���

	int img;	//�摜�p�̕ϐ�
	int num;	//�J�[�h�̐���
	int suit;	//�J�[�h�̃X�[�g(�}�[�N)

	//�J�[�h���Ƃ̓����蔻��i�}�E�XX���W�A�}�E�XY���W�A�J�[�hX���W�A�J�[�hY���W�A�J�[�h�̕��A�J�[�h�̍����A�J�[�h�̉摜�{���j
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

class PageOne : public Card {
private:
	int card_type[54];	//�摜�p�n���h��
	int background;	//�w�i

	Card Card_back;		//�J�[�h�̗��ʂ̏��
	Card Card_joker;	//�W���[�J�[�̏��

	//Card Card_obj[4][13];		//�S�J�[�h�̏��
	std::vector<Card> Card_obj;		//�S�J�[�h�̏��(�R�D)
	std::vector<Card> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��

	std::vector<Card> Field_card;		//��ɏo�Ă���J�[�h
	std::vector<Card> Cemetery_card;	//�g�p�ς݂̃J�[�h

	std::vector<Card> NPC_card_1;		//NPC�P���̎����Ă���J�[�h�̏��
	std::vector<Card> NPC_card_2;		//NPC�Q���̎����Ă���J�[�h�̏��
	std::vector<Card> NPC_card_3;		//NPC�R���̎����Ă���J�[�h�̏��

	int Pass_Icon;		//�p�X�̃A�C�R���摜
	int PageOne_Icon;	//�y�[�W�����錾�̃A�C�R���摜

	bool PageOne_flg;	//�y�[�W�����錾���������ǂ���(true:����	false:���ĂȂ�)

	bool PageOne_player;	//�v���C���[�̃y�[�W�����錾
	bool PageOne_npc1;	//NPC�P���̃y�[�W�����錾
	bool PageOne_npc2;	//NPC�Q���̃y�[�W�����錾
	bool PageOne_npc3;	//NPC�R���̃y�[�W�����錾

	int priority;	//��Ԃ����߂�D��x
	int field;		//��ɏo�Ă���J�[�h�̖���

	int pri;		//�e�����߂邽�߂̕ϐ�
	bool draw;		//�J�[�h�������邩�ǂ��������߂邽�߂̃t���O
	bool finish;	//�Q�[���I���t���O

	int player;		//�v���C���[�̎�D�̖���
	bool flg_p;		//�v���C���[�̎�Ԃ��I��������ǂ���

	int npc_1;		//NPC�P���̎�D�̖���
	bool flg_1;		//NPC�P���̎�Ԃ��I��������ǂ���

	int npc_2;		//NPC�Q���̎�D�̖���
	bool flg_2;		//NPC�Q���̎�Ԃ��I��������ǂ���

	int npc_3;		//NPC�R���̎�D�̖���
	bool flg_3;		//NPC�R���̎�Ԃ��I��������ǂ���

	int p_pow;		//�v���C���[���o�����J�[�h�̋���
	int n1_pow;		//NPC�P�����o�����J�[�h�̋���
	int n2_pow;		//NPC�Q�����o�����J�[�h�̋���
	int n3_pow;		//NPC�R�����o�����J�[�h�̋���

	int lead;	//��̃X�[�g�̊�ɂ���J�[�h�̏��ԁi��{�͐擪�i0�Ԗځj�j

	int p;		//�v���C���[�̎�D���� p �Ԗڂɂ���J�[�h
	int n1;		//NPC�P���̎�D���� n1 �Ԗڂɂ���J�[�h
	int n2;		//NPC�Q���̎�D���� n2 �Ԗڂɂ���J�[�h
	int n3;		//NPC�R���̎�D���� n3 �Ԗڂɂ���J�[�h

	int i;	//���[�v�Ɏg���Ă���ϐ�
	int r;	//�����_���p�ϐ�

	int n;	//�N�[���^�C���p�ϐ�

	int Mouse_X;	//�}�E�X��X���W
	int Mouse_Y;	//�}�E�X��Y���W

	int Deck_X;		//�R�D��X���W
	int Deck_Y;		//�R�D��Y���W

	int Field_X;		//��ɏo�����J�[�h��X���W
	int Field_Y;		//��ɏo�����J�[�h��Y���W

	int Player_X;	//�v���C���[�̎�D��X���W
	int Player_Y;	//�v���C���[�̎�D��Y���W

	int NPC1_X;		//NPC1�̎�D��X���W
	int NPC1_Y;		//NPC1�̎�D��Y���W

	int NPC2_X;		//NPC2�̎�D��X���W
	int NPC2_Y;		//NPC2�̎�D��Y���W

	int NPC3_X;		//NPC3�̎�D��X���W
	int NPC3_Y;		//NPC3�̎�D��Y���W

	int color;	//�f�o�b�O�p
public:
	PageOne() {}

	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();

};

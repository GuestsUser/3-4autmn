#pragma once
#include "./../Scene.h"
#include<list>
#include<vector>

#define MAX (4U)

class Card {
public:

	int card_w = 200;	//�J�[�h�P���̕�
	int card_h = 300;	//�J�[�h�P���̍���

	int img;	//�摜�p�̕ϐ�
	int num;	//�J�[�h�̐���
	int suit;	//�J�[�h�̃X�[�g(�}�[�N)


	int card_x;
	int card_y;

	Card() {}

	//�J�[�h���Ƃ̓����蔻��i�}�E�XX���W�A�}�E�XY���W�A�J�[�hX���W�A�J�[�hY���W�A�J�[�h�̕��A�J�[�h�̍����A�J�[�h�̉摜�{���j
	bool Hit(int mx, int my, int cx, int cy, int cw, int ch, double ExRate) {
		if (mx > cx - (cw * ExRate) / 2 && mx < cx + (cw * ExRate) / 2 && my > cy - (ch * ExRate) / 2 && my < cy + (ch * ExRate) / 2) {
			return true;
		}
		else {
			return false;
		}
	}

	//Set_Card(�摜�A���l�A�X�[�g�A�J�[�h���Ƃ�X���W�A�J�[�h���Ƃ�Y���W�A�g�p�t���O(0:�g���ĂȂ��@1:�g���Ă���))
	Card(int i, int n, int s, int x, int y) {
		img = i;
		num = n;
		suit = s;

		card_x = x;
		card_y = y;

	}
};

class PageOne : public Card {
private:
	int card_type[54];	//�摜�p�n���h��
	int background;	//�w�i

	//std::vector <Card> Card_obj[53];		//�S�J�[�h�̏��(�R�D)
	//std::vector <Card> Player_card[53];	//�v���C���[�̎����Ă���J�[�h�̏��

	//std::vector <Card> Field_card[4];		//��ɏo�Ă���J�[�h
	//std::vector <Card> Cemetery_card[53];		//��ɏo�Ă���J�[�h

	//std::vector <Card> NPC_card_1[53];		//NPC�P���̎����Ă���J�[�h�̏��
	//std::vector <Card> NPC_card_2[53];		//NPC�Q���̎����Ă���J�[�h�̏��
	//std::vector <Card> NPC_card_3[53];		//NPC�R���̎����Ă���J�[�h�̏��
	
	std::list <Card> Card_obj;		//�S�J�[�h�̏��(�R�D)
	std::list <Card> Player_card;	//�v���C���[�̎����Ă���J�[�h�̏��

	std::list <Card> Field_card;		//��ɏo�Ă���J�[�h
	std::list <Card> Cemetery_card;		//��ɏo�Ă���J�[�h

	std::list <Card> NPC_card_1;		//NPC�P���̎����Ă���J�[�h�̏��
	std::list <Card> NPC_card_2;		//NPC�Q���̎����Ă���J�[�h�̏��
	std::list <Card> NPC_card_3;		//NPC�R���̎����Ă���J�[�h�̏��

	std::list <Card>::iterator itr;
	std::list <Card>::iterator f_itr;

	std::list <Card>::iterator p_itr;
	std::list <Card>::iterator n1_itr;
	std::list <Card>::iterator n2_itr;
	std::list <Card>::iterator n3_itr;

	//�X�[�gUI
	int Spade;	//�X�y�[�h
	int Heart;	//�n�[�g
	int Diamond;//�_�C��
	int Club;	//�N���u
	int free;	//���ł��悢

	//�|�[�YUI
	int Pause_Button;
	int Pause_Back;
	int Pause_Continue;
	int Pause_Select;
	int pause_continue[2];
	int pause_select[2];

	bool Pause_Flg;
	int Now_key;
	int Old_key;

	//���U���g�w�i
	int Result;

	//�e��SE
	int pass_SE;
	int pageone_SE;
	int card_SE_1;	//�J�[�h������
	int card_SE_2;	//�J�[�h���o��
	int card_SE_3;	//�J�[�h���ړ�����
	int win_SE;	//��������SE

	int Cursor_SE;	//�J�[�\����SE
	int Select_SE;	//����{�^����SE

	int BGM;	//BGM�ۑ��p�ϐ�

	bool OneShot;	//�������ǂ����i��񂾂��炷�̂Ɏg���j

	Scene* select;

	int Card_back;		//�J�[�h�̗��ʂ̏��
	int card_img;	//�J�[�h�摜
	//int card_num;	//�J�[�h����

	int PlayerCrown;		//�����̃A�C�R���摜
	int NPC1_Icon;		//�����̃A�C�R���摜
	int NPC2_Icon;		//�����̃A�C�R���摜
	int NPC3_Icon;		//�����̃A�C�R���摜

	int Player_Pass_Icon;		//�p�X�̃A�C�R���摜
	int NPC1_Pass_Icon;		//�p�X�̃A�C�R���摜
	int NPC2_Pass_Icon;		//�p�X�̃A�C�R���摜
	int NPC3_Pass_Icon;		//�p�X�̃A�C�R���摜

	int Player_PageOne_Icon;	//�y�[�W�����錾�̃A�C�R���摜
	int NPC1_PageOne_Icon;	//�y�[�W�����錾�̃A�C�R���摜
	int NPC2_PageOne_Icon;	//�y�[�W�����錾�̃A�C�R���摜
	int NPC3_PageOne_Icon;	//�y�[�W�����錾�̃A�C�R���摜

	bool Player_Pass_Flg;		//�v���C���[�p�X�t���O
	bool NPC1_Pass_Flg;		//NPC1�p�X�t���O
	bool NPC2_Pass_Flg;		//NPC2�p�X�t���O
	bool NPC3_Pass_Flg;		//NPC3�p�X�t���O

	bool PageOne_flg;	//�y�[�W�����錾���������ǂ���(true:����	false:���ĂȂ�)

	bool PageOne_player;	//�v���C���[�̃y�[�W�����錾
	bool PageOne_npc1;	//NPC�P���̃y�[�W�����錾
	bool PageOne_npc2;	//NPC�Q���̃y�[�W�����錾
	bool PageOne_npc3;	//NPC�R���̃y�[�W�����錾

	int priority;	//��Ԃ����߂�D��x
	int field;		//��ɏo�Ă���J�[�h�̖���
	int cemetery;	//�g�p�����J�[�h�̖���

	int pri;		//�e�����߂邽�߂̕ϐ�(�t�B�[���h�ň�ԋ����J�[�h���L�^�����)
	bool draw;		//�J�[�h�������邩�ǂ��������߂邽�߂̃t���O(false:�����Ȃ��@true:������)

	bool Player_setup;		//�v���C���[�����t���O
	bool NPC1_setup;		//NPC1�����t���O
	bool NPC2_setup;		//NPC2�����t���O
	bool NPC3_setup;		//NPC3�����t���O

	bool finish;	//�Q�[���I���t���O
	bool reset;	//�Ֆʃ��Z�b�g�t���O

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

	void PageOne_Initialize(Scene* scene);
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();
};

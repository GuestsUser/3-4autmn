#pragma once
#include "./../Scene.h"

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

class PageOne : public Scene{
private:
	Card Card_obj[54];	//�J�[�h�̏��

	int card_type[65];	//�摜�p�n���h��

	int Mouse_X; //�}�E�X��X���W
	int Mouse_Y; //�}�E�X��Y���W
	int Player_X; //�v���C���[��X���W
	int Player_Y; //�v���C���[��Y���W

public:
	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();
};

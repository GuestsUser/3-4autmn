#pragma once

class Card {
private:
	int img;	//�摜�p�̕ϐ�
	int num;	//�J�[�h�̐���
	int suit;	//�J�[�h�̃X�[�g(�}�[�N)

public:
	Card(int i, int n, int s) {
		img = i;
		num = n;
		suit = s;
	}
};

class PageOne {
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

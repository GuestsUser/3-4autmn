#pragma once

class CP {
private:
	int i, j, x, y;

public:

	int card_w = 200;	//�J�[�h�P���̕�
	int card_h = 300;	//�J�[�h�P���̍���
	int Mouse_X;	//�}�E�X��X���W
	int Mouse_Y;    //�}�E�X��Y���W
	int Player_X;
	int Player_Y;

	bool Hit(int mx, int my, int cx, int cy, int cw, int ch, double ExRate) {
		if (mx > cx - (cw * ExRate) / 2 && mx < cx + (cw * ExRate) / 2 && my > cy - (ch * ExRate) / 2 && my < cy + (ch * ExRate) / 2) {
			return true;
		}
		else {
			return false;
		}
	}

	void Player_Initialize();//��
	void Player_Finalize();//��
	void Player_Update();
	void Player_Draw();
	void onesec(void);//��
	void deckmake();//�R�D����//��
	void datareset();//�f�[�^�̐ݒ�
	void deckshuffle();//�V���b�t��
	void phase(int n);
	void turn(int n);
	//void sort(int sort_x, int* sort_y, int sort_z);//�\�[�g�����߂�
	void pl_routine(int n);
	void expend(int n);//��D�������Ȃ�����
	void slash8(int n);//8�؂�p
	void main();
	void dealcards();
	void d3start();
	void status(int n);
	void print(int n);
	void revolution();
	void elevenback();
	void cp_routine(int n);
	void arrange(int n);
	//void main(void);
};

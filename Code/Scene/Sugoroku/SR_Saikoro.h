#pragma once
#include "./../Scene.h"
	//extern int Player1sum;
class SR_Saikoro : public Scene {
private:
	int SR_Saikoro1[6];	/*�T�C�R���摜�P*/
	int SR_Saikoro2[6];	/*�T�C�R���摜�Q*/
	int array[4];
	int i, y, d, p, v;
	bool Shuffle = false;	/*�T�C�R���V���b�t���ۃt���O*/
	bool Click = true;	/*�T�C�R���N���b�N�ۃt���O*/
	bool Goalflg;	/*�S�[�����Ă��邩�̃t���O*/
	bool Sumflg;	/*Player�ړ��ʌv�Z����Ƃ��p�̃t���O*/
	bool Whoisplay = true;	/*�e�L�X�g�����Ȃ��悤�ɂ���t���O*/
	bool Replay = false;	/*�T�C�R����U��Ȃ����t���O*/
	bool Back = false;	/*�T�C�R����U�����������߂�t���O*/

	int count;
	int countdiff;
	int countmi;
	int Dice1, Dice2;
	int Sum;	/*�T�C�R���̖ڂ̍��v��*/
	int num; /*switch���悤�ϐ�*/
	int text;
	int current;
	/*��������������*/
	int MouseX, MouseY;	/*Mouse���W�擾�i�S�̂ł̂��o����܂Łj*/
	/*��������������*/
public:
	SR_Saikoro();
	void Update();
	void Draw();
	void Saikoro();
	void Dice();
	void Goal();
	void Sort();
	void Restart();
	void Plus();
	void Minus();
	void ReDice();
	void Frontback();
	void SR_Enemy1();
	void SR_Enemy2();
	void SR_Enemy3();
	void Countdiff();
};


#pragma once
#include "./../Scene.h"
	//extern int Player1sum;
class SR_Saikoro : public Scene {
private:
	int SR_Saikoro1[6];	/*�T�C�R���摜�P*/
	int SR_Saikoro2[6];	/*�T�C�R���摜�Q*/
	int i, y, d,p;

	bool Shuffle = false;	/*�T�C�R���V���b�t���ۃt���O*/
	bool Click = true;	/*�T�C�R���N���b�N�ۃt���O*/
	bool Goalflg;
	bool Sumflg;	/*Player�ړ��ʌv�Z����Ƃ��p�̃t���O*/
	bool Whoisplay = true;

	int count;
	int countdiff;
	int countmi;
	int Dice1, Dice2;
	int Sum;	/*�T�C�R���̖ڂ̍��v��*/
	int num; /*switch���悤�ϐ�*/
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
	void Restart();
	void SR_Enemy1();
	void SR_Enemy2();
	void SR_Enemy3();
	void Countdiff();
};


#pragma once
#include "./../Scene.h"
class SR_Saikoro{
private:
	int SR_Saikoro1[6];	/*�T�C�R���摜�P*/
	int SR_Saikoro2[6];	/*�T�C�R���摜�Q*/
	int i,y,d;
	bool Shuffle = false;	/*�T�C�R���V���b�t���ۃt���O*/
	bool Click = true;	/*�T�C�R���N���b�N�ۃt���O*/
	int count;
	int Dice1,Dice2;	
	int Sum;	/*�T�C�R���̖ڂ̍��v��*/
	/*��������������*/
	int MouseX, MouseY;	/*Mouse���W�擾�i�S�̂ł̂��o����܂Łj*/
	/*��������������*/
public:
	SR_Saikoro();
	void Update();
	void Draw();
	void Saikoro();
	void Dice();
};

#pragma once

#define KARU_MAX_X  5
#define KARU_MAX_Y  3

class Karu_Game{
private:
	int Karu_Bg;				//�Q�[���w�i
	int Karu_SideBg;			//�Q�[���w�i
	int Karu_fuda[10][10];		//���邽�̎D�摜�i�[�p

	int Karu_Efuda[KARU_MAX_Y][KARU_MAX_X];		//���邽�̊G�D�z�u�p

	float Karu_StartPosX = 105.0f;		//�G�D�̔z�u�J�n�ʒu
	float Karu_StartPosY = 132.5f;		//..
	float Karu_imgX = 150.0f;	//���邽�̉摜�̑傫��
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 20.0f;	//�G�D�ƊG�D�̊�

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

};
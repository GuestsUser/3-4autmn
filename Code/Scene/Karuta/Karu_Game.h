#pragma once

class Karu_Game{
private:
	int Karu_Bg;				//�Q�[���w�i
	int Karu_fuda[10][10];		//���邽�̎D�摜�i�[�p

	int Karu_Efuda[3][5];		//���邽�̊G�D�z�u�p
	int Karu_MaxX = 5, Karu_MaxY = 3;	//�\��������G�D�̖���

	float Karu_StartPosX = 75.0f;		//�G�D�̔z�u�J�n�ʒu
	float Karu_StartPosY = 102.5f;		//..
	float Karu_imgX = 150.0f;	//���邽�̉摜�̑傫��
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 10.0f;	//�G�D�ƊG�D�̊�

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

	int Karu_X, Karu_Y;	//�\��������G�D�̖���
};
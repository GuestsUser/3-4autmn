#pragma once

#define PI    3.1415926535897932384626433832795f

#define KARU_IMAGE_MAX_X  10	//���邽�̉摜�ő吔
#define KARU_IMAGE_MAX_Y  10	//..�c

#define KARU_MAX_X  5			//���邽�z�u�̉��̖���
#define KARU_MAX_Y  3			//..�c

class Karu_Game{
private:
	int Karu_Bg;				//�Q�[���w�i
	int Karu_SideBg;			//�Q�[���w�i
	int Karu_fuda[KARU_IMAGE_MAX_X][KARU_IMAGE_MAX_Y];		//���邽�̎D�摜�i�[�p

	float Karu_StartPosX = 105.0f;		//�G�D�̔z�u�J�n�ʒu
	float Karu_StartPosY = 132.5f;		//..
	float Karu_imgX = 150.0f;	//���邽�̉摜�̑傫��
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 20.0f;	//�G�D�ƊG�D�̊�

	int Mouse_X;	//�}�E�X��X���W
	int Mouse_Y;	//�}�E�X��Y���W

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

	void Efuda_Storage();
	void Yomifuda_Storage();
	void Mouse_HitBox();

	int Karu_Efuda[KARU_MAX_Y][KARU_MAX_X];		//���邽�̊G�D�z�u�p
};

struct EFUDA
{
	float x, y;	//���邽�̈ʒu
	int img;	//�G�D�̉摜�i�[�p
	int numX, numY;

	bool kara;	//����ċ󔒂ɂȂ��Ă��邩
};

extern struct EFUDA Efuda[KARU_MAX_Y][KARU_MAX_X];

struct YOMIFUDA
{
	float x, y;	//���邽�̈ʒu
	int img;	//�G�D�̉摜�i�[�p

	bool kara;	//�󔒂ɂȂ��Ă��邩
};

extern struct YOMIFUDA Yomifuda[KARU_MAX_Y][KARU_MAX_X];

struct FUDA
{
	bool get;	//����Ă邩
};

extern struct FUDA Fuda[100];
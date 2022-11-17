#pragma once

#define PI    3.1415926535897932384626433832795f

#define KARU_IMAGE_MAX_X  10	//���邽�̉摜�ő吔
#define KARU_IMAGE_MAX_Y  10	//..�c

#define KARU_MAX_X  5			//���邽�z�u�̉��̖���
#define KARU_MAX_Y  3			//..�c

#define HAND_ICON 2				//�J�[�\���A�C�R���̉摜�ő吔

#define OTETUKI_IMG 2			//����t���摜�ő吔
#define KARU_OTETUKI_MAX  2		//����t���̐���

#define CLICK_MAX_TIME 60.0f	//�N���b�N�P�\
#define TOUCH_MAX 1

#define NUM_IMG_MAX 10			//�����摜�ő吔

#define TOTAL_PLAYER 4			//�Q���l��

class Karu_Game{
private:
	int Karu_Bg;				//�Q�[���w�i
	int Karu_SideBg;			//�Q�[���w�i
	int Karu_Otetuki_img[OTETUKI_IMG];	//����t�����̉摜�i�[�p
	int Karu_getText;			//�l�������̃e�L�X�g�摜�i�[�p	
	int Karu_PlayerText;		//�v���C���[�̃e�L�X�g�摜�i�[�p
	int Karu_numImg[NUM_IMG_MAX];		//�����̃e�L�X�g�摜�i�[�p

	int Karu_CPU1_Text;		//CPU1�̃e�L�X�g�摜�i�[�p
	int Karu_CPU2_Text;		//CPU1�̃e�L�X�g�摜�i�[�p
	int Karu_CPU3_Text;		//CPU1�̃e�L�X�g�摜�i�[�p

	int Karu_fuda[KARU_IMAGE_MAX_X][KARU_IMAGE_MAX_Y];		//���邽�̎D�摜�i�[�p
	int Fuda_voice[KARU_IMAGE_MAX_X][KARU_IMAGE_MAX_Y];		//�ǂݏグ�����i�[�p

	float Karu_StartPosX = 105.0f;		//�G�D�̔z�u�J�n�ʒu
	float Karu_StartPosY = 132.5f;		//..
	float Karu_imgX = 150.0f;	//���邽�̉摜�̑傫��
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 20.0f;	//�G�D�ƊG�D�̊�

	int Mouse_X;	//�}�E�X��X���W
	int Mouse_Y;	//�}�E�X��Y���W

	int Player_HandIcon[HAND_ICON];	//�}�E�X�J�[�\���A�C�R���i�[�p
	int Enemy1_HandIcon[HAND_ICON];	//�}�E�X�J�[�\���A�C�R���i�[�p
	int Enemy2_HandIcon[HAND_ICON];	//�}�E�X�J�[�\���A�C�R���i�[�p
	int Enemy3_HandIcon[HAND_ICON];	//�}�E�X�J�[�\���A�C�R���i�[�p

	bool end;


public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

	void Efuda_Storage();
	void Yomifuda_Storage();
	void Voice_Storage();

	void Mouse_HitBox();

	void Click_Anim();
	void Otetuki_Anim();

	void Cpu_config();
	void Cpu_reset();

	void Player_Reset();

	void Karu_GameOver();

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

struct KARU_PLAYER
{
	int myFuda;	//����Ă閇��
	int Otetuki;
	int Rank;
};

extern struct KARU_PLAYER Karu_player;

struct KARU_CPU
{
	float x, y;
	int myFuda;	//����Ă閇��
	int setTime; 
	int minTime;
	int Time;
	int Rank;

	bool onClick;
};

extern struct KARU_CPU cpu_1;
extern struct KARU_CPU cpu_2;
extern struct KARU_CPU cpu_3;
#pragma once

#define PI    3.1415926535897932384626433832795f

#define KARU_IMAGE_MAX_X  10	//かるたの画像最大数
#define KARU_IMAGE_MAX_Y  10	//..縦

#define KARU_MAX_X  5			//かるた配置の横の枚数
#define KARU_MAX_Y  3			//..縦

#define HAND_ICON 2				//カーソルアイコンの画像最大数

#define OTETUKI_IMG 2			//お手付き画像最大数
#define KARU_OTETUKI_MAX  2		//お手付きの制限

#define CLICK_MAX_TIME 60.0f	//クリック猶予
#define TOUCH_MAX 1

#define NUM_IMG_MAX 10			//数字画像最大数

#define TOTAL_PLAYER 4			//参加人数

class Karu_Game{
private:
	int Karu_Bg;				//ゲーム背景
	int Karu_SideBg;			//ゲーム背景
	int Karu_Otetuki_img[OTETUKI_IMG];	//お手付き時の画像格納用
	int Karu_getText;			//獲得枚数のテキスト画像格納用	
	int Karu_PlayerText;		//プレイヤーのテキスト画像格納用
	int Karu_numImg[NUM_IMG_MAX];		//数字のテキスト画像格納用

	int Karu_CPU1_Text;		//CPU1のテキスト画像格納用
	int Karu_CPU2_Text;		//CPU1のテキスト画像格納用
	int Karu_CPU3_Text;		//CPU1のテキスト画像格納用

	int Karu_fuda[KARU_IMAGE_MAX_X][KARU_IMAGE_MAX_Y];		//かるたの札画像格納用
	int Fuda_voice[KARU_IMAGE_MAX_X][KARU_IMAGE_MAX_Y];		//読み上げ音声格納用

	float Karu_StartPosX = 105.0f;		//絵札の配置開始位置
	float Karu_StartPosY = 132.5f;		//..
	float Karu_imgX = 150.0f;	//かるたの画像の大きさ
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 20.0f;	//絵札と絵札の間

	int Mouse_X;	//マウスのX座標
	int Mouse_Y;	//マウスのY座標

	int Player_HandIcon[HAND_ICON];	//マウスカーソルアイコン格納用
	int Enemy1_HandIcon[HAND_ICON];	//マウスカーソルアイコン格納用
	int Enemy2_HandIcon[HAND_ICON];	//マウスカーソルアイコン格納用
	int Enemy3_HandIcon[HAND_ICON];	//マウスカーソルアイコン格納用

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
	float x, y;	//かるたの位置
	int img;	//絵札の画像格納用
	int numX, numY;

	bool kara;	//取って空白になっているか
};

extern struct EFUDA Efuda[KARU_MAX_Y][KARU_MAX_X];

struct YOMIFUDA
{
	float x, y;	//かるたの位置
	int img;	//絵札の画像格納用

	bool kara;	//空白になっているか
};

extern struct YOMIFUDA Yomifuda[KARU_MAX_Y][KARU_MAX_X];

struct FUDA
{
	bool get;	//取ってるか
};

extern struct FUDA Fuda[100];

struct KARU_PLAYER
{
	int myFuda;	//取ってる枚数
	int Otetuki;
	int Rank;
};

extern struct KARU_PLAYER Karu_player;

struct KARU_CPU
{
	float x, y;
	int myFuda;	//取ってる枚数
	int setTime; 
	int minTime;
	int Time;
	int Rank;

	bool onClick;
};

extern struct KARU_CPU cpu_1;
extern struct KARU_CPU cpu_2;
extern struct KARU_CPU cpu_3;
#pragma once

#define PI    3.1415926535897932384626433832795f

#define KARU_IMAGE_MAX_X  10	//かるたの画像最大数
#define KARU_IMAGE_MAX_Y  10	//..縦

#define KARU_MAX_X  5			//かるた配置の横の枚数
#define KARU_MAX_Y  3			//..縦

#define KARU_OTETUKI_MAX  2			//お手付きの制限

class Karu_Game{
private:
	int Karu_Bg;				//ゲーム背景
	int Karu_SideBg;			//ゲーム背景
	int Karu_Otetuki_img[2];	//お手付き時の画像格納用
	int Karu_getText;			//獲得枚数のテキスト画像格納用	
	int Karu_PlayerText;		//プレイヤーのテキスト画像格納用
	int Karu_numImg[10];		//数字のテキスト画像格納用

	int Karu_fuda[KARU_IMAGE_MAX_X][KARU_IMAGE_MAX_Y];		//かるたの札画像格納用
	int Fuda_voice[KARU_IMAGE_MAX_X][KARU_IMAGE_MAX_Y];		//読み上げ音声格納用

	float Karu_StartPosX = 105.0f;		//絵札の配置開始位置
	float Karu_StartPosY = 132.5f;		//..
	float Karu_imgX = 150.0f;	//かるたの画像の大きさ
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 20.0f;	//絵札と絵札の間

	int Mouse_X;	//マウスのX座標
	int Mouse_Y;	//マウスのY座標

	int Karu_Otetuki;

	bool end;

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

	void Efuda_Storage();
	void Yomifuda_Storage();
	void Mouse_HitBox();

	void Karu_GameOver();

	void Otetuki_Anim();

	int Karu_Efuda[KARU_MAX_Y][KARU_MAX_X];		//かるたの絵札配置用
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

	int MousePoint[2];//マウスポインターの画像格納用
};

extern struct KARU_PLAYER Karu_player;
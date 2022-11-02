#pragma once

#define PI    3.1415926535897932384626433832795f

#define KARU_IMAGE_MAX_X  10	//‚©‚é‚½‚Ì‰æ‘œÅ‘å”
#define KARU_IMAGE_MAX_Y  10	//..c

#define KARU_MAX_X  5			//‚©‚é‚½”z’u‚Ì‰¡‚Ì–‡”
#define KARU_MAX_Y  3			//..c

class Karu_Game{
private:
	int Karu_Bg;				//ƒQ[ƒ€”wŒi
	int Karu_SideBg;			//ƒQ[ƒ€”wŒi
	int Karu_fuda[KARU_IMAGE_MAX_X][KARU_IMAGE_MAX_Y];		//‚©‚é‚½‚ÌD‰æ‘œŠi”[—p

	float Karu_StartPosX = 105.0f;		//ŠGD‚Ì”z’uŠJnˆÊ’u
	float Karu_StartPosY = 132.5f;		//..
	float Karu_imgX = 150.0f;	//‚©‚é‚½‚Ì‰æ‘œ‚Ì‘å‚«‚³
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 20.0f;	//ŠGD‚ÆŠGD‚ÌŠÔ

	int Mouse_X;	//ƒ}ƒEƒX‚ÌXÀ•W
	int Mouse_Y;	//ƒ}ƒEƒX‚ÌYÀ•W

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

	void Mouse_HitBox();

	int Karu_Efuda[KARU_MAX_Y][KARU_MAX_X];		//‚©‚é‚½‚ÌŠGD”z’u—p
};

#pragma once

#define KARU_MAX_X  5
#define KARU_MAX_Y  3

class Karu_Game{
private:
	int Karu_Bg;				//ƒQ[ƒ€”wŒi
	int Karu_SideBg;			//ƒQ[ƒ€”wŒi
	int Karu_fuda[10][10];		//‚©‚é‚½‚ÌD‰æ‘œŠi”[—p

	int Karu_Efuda[KARU_MAX_Y][KARU_MAX_X];		//‚©‚é‚½‚ÌŠGD”z’u—p

	float Karu_StartPosX = 105.0f;		//ŠGD‚Ì”z’uŠJnˆÊ’u
	float Karu_StartPosY = 132.5f;		//..
	float Karu_imgX = 150.0f;	//‚©‚é‚½‚Ì‰æ‘œ‚Ì‘å‚«‚³
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 20.0f;	//ŠGD‚ÆŠGD‚ÌŠÔ

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

};
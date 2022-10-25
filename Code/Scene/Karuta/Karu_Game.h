#pragma once

class Karu_Game{
private:
	int Karu_Bg;				//ƒQ[ƒ€”wŒi
	int Karu_fuda[10][10];		//‚©‚é‚½‚ÌD‰æ‘œŠi”[—p

	int Karu_Efuda[3][5];		//‚©‚é‚½‚ÌŠGD”z’u—p
	int Karu_MaxX = 5, Karu_MaxY = 3;	//•\¦‚³‚¹‚éŠGD‚Ì–‡”

	float Karu_StartPosX = 75.0f;		//ŠGD‚Ì”z’uŠJnˆÊ’u
	float Karu_StartPosY = 102.5f;		//..
	float Karu_imgX = 150.0f;	//‚©‚é‚½‚Ì‰æ‘œ‚Ì‘å‚«‚³
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 10.0f;	//ŠGD‚ÆŠGD‚ÌŠÔ

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

	int Karu_X, Karu_Y;	//•\¦‚³‚¹‚éŠGD‚Ì–‡”
};
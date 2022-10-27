#pragma once

#define KARU_MAX_X  5
#define KARU_MAX_Y  3

class Karu_Game{
private:
	int Karu_Bg;				//ゲーム背景
	int Karu_SideBg;			//ゲーム背景
	int Karu_fuda[10][10];		//かるたの札画像格納用

	int Karu_Efuda[KARU_MAX_Y][KARU_MAX_X];		//かるたの絵札配置用

	float Karu_StartPosX = 105.0f;		//絵札の配置開始位置
	float Karu_StartPosY = 132.5f;		//..
	float Karu_imgX = 150.0f;	//かるたの画像の大きさ
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 20.0f;	//絵札と絵札の間

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

};
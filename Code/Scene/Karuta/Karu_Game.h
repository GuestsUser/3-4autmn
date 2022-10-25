#pragma once

class Karu_Game{
private:
	int Karu_Bg;				//ゲーム背景
	int Karu_fuda[10][10];		//かるたの札画像格納用

	int Karu_Efuda[3][5];		//かるたの絵札配置用
	int Karu_MaxX = 5, Karu_MaxY = 3;	//表示させる絵札の枚数

	float Karu_StartPosX = 75.0f;		//絵札の配置開始位置
	float Karu_StartPosY = 102.5f;		//..
	float Karu_imgX = 150.0f;	//かるたの画像の大きさ
	float Karu_imgY = 205.0f;	//..

	float Karu_Space = 10.0f;	//絵札と絵札の間

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();

	int Karu_X, Karu_Y;	//表示させる絵札の枚数
};
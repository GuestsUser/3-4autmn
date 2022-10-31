#pragma once
#include "./../Scene.h"
class SR_Saikoro{
private:
	int SR_Saikoro1[6];	/*サイコロ画像１*/
	int SR_Saikoro2[6];	/*サイコロ画像２*/
	int i,y,d;
	bool Shuffle = false;	/*サイコロシャッフル可否フラグ*/
	bool Click = true;	/*サイコロクリック可否フラグ*/
	int count;
	int Dice1,Dice2;	
	int Sum;	/*サイコロの目の合計数*/
	/*仮仮仮仮仮仮仮*/
	int MouseX, MouseY;	/*Mouse座標取得（全体でのが出来るまで）*/
	/*仮仮仮仮仮仮仮*/
public:
	SR_Saikoro();
	void Update();
	void Draw();
	void Saikoro();
	void Dice();
};

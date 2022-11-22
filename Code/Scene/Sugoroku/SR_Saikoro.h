#pragma once
#include "./../Scene.h"
	//extern int Player1sum;
class SR_Saikoro : public Scene {
private:
	int SR_Saikoro1[6];	/*サイコロ画像１*/
	int SR_Saikoro2[6];	/*サイコロ画像２*/
	int i, y, d,p;

	bool Shuffle = false;	/*サイコロシャッフル可否フラグ*/
	bool Click = true;	/*サイコロクリック可否フラグ*/
	bool Goalflg;
	bool Sumflg;	/*Player移動量計算するとき用のフラグ*/
	bool Whoisplay = true;

	int count;
	int countdiff;
	int countmi;
	int Dice1, Dice2;
	int Sum;	/*サイコロの目の合計数*/
	int num; /*switch文よう変数*/
	/*仮仮仮仮仮仮仮*/
	int MouseX, MouseY;	/*Mouse座標取得（全体でのが出来るまで）*/
	/*仮仮仮仮仮仮仮*/
public:
	SR_Saikoro();
	void Update();
	void Draw();
	void Saikoro();
	void Dice();
	void Goal();
	void Restart();
	void SR_Enemy1();
	void SR_Enemy2();
	void SR_Enemy3();
	void Countdiff();
};


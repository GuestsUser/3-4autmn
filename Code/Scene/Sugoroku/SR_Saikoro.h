#pragma once
#include "./../Scene.h"
	//extern int Player1sum;
class SR_Saikoro : public Scene {
private:
	Scene* parent;
	int SR_Saikoro1[6];	/*サイコロ画像１*/
	int SR_Saikoro2[6];	/*サイコロ画像２*/
	int pause_select[2];
	int pause_continue[2];
	int SR_GOAL;
	int Pause_Button;
	int Pause_Back;
	int Pause_Continue;
	int Pause_Select;
	int array[4];
	int i, y, d, p, v,o;
	bool Shuffle = false;	/*サイコロシャッフル可否フラグ*/
	bool Click = true;	/*サイコロクリック可否フラグ*/
	bool Goalflg;	/*ゴールしているかのフラグ*/
	bool Sumflg;	/*Player移動量計算するとき用のフラグ*/
	bool Whoisplay = true;	/*テキストが被らないようにするフラグ*/
	bool Replay = false;	/*サイコロを振りなおすフラグ*/
	bool Back = false;	/*サイコロを振った分だけ戻るフラグ*/
	bool PauseFlg;
	bool move;

	int count;
	int countdiff;
	int countmi;
	int Dice1, Dice2;
	int Sum;	/*サイコロの目の合計数*/
	int num; /*switch文よう変数*/
	int text;
	int current;
	int OldKey;
	int nowKey;
	/*仮仮仮仮仮仮仮*/
	int MouseX, MouseY;	/*Mouse座標取得（全体でのが出来るまで）*/
	/*仮仮仮仮仮仮仮*/
public:
	SR_Saikoro(Scene*scene);
	void Update();
	void Draw();
	void Saikoro();
	void Dice();
	void Goal();
	void Sort();
	void Restart();
	void Plus();
	void Minus();
	void ReDice();
	void Frontback();
	void SR_Enemy1();
	void SR_Enemy2();
	void SR_Enemy3();
	void Countdiff();
	void SR_Pose_Update();
};


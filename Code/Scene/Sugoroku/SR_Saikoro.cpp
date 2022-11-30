#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Map.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"
#include "SR_Result.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Player1sum;
int Player2sum;
int Player3sum;
int Player4sum;

SR_Saikoro::SR_Saikoro() {
	LoadDivGraph("Resource/image/SR_Saikoro1.png", 6, 6, 1, 75, 75, SR_Saikoro1, true);	/*サイコロ画像読み込み*/
	LoadDivGraph("Resource/image/SR_Saikoro2.png", 6, 6, 1, 75, 75, SR_Saikoro2, true);	/*サイコロ画像読み込み*/
	y = 0, d = 0, i = 0;	/*各種変数初期化*/
	count = 0;
	countdiff = 0;
	countmi = 0;
	num = 1;
	Click = true;
	//SRand(count); // 乱数の初期値をcountに設定する
	srand((unsigned int)time(NULL));

	Player1sum = 0;
	Player2sum = 0;
	Player3sum = 0;
	Player4sum = 0;
}

void SR_Saikoro::Update() {
	count++;
	GetMousePoint(&MouseX, &MouseY);/*マウス座標取得（仮）*/
	/*ゴールしたら*/
	if (Player1sum >= 64|| Player2sum >= 64 || Player3sum >= 64 || Player4sum >= 64) {
		Goal();	/*まだ中身はない*/
		Player1sum = 64; Player2sum = 64; Player3sum = 64; Player4sum = 64;
	}

	/*リスタートますに乗ったら*/
	if (Player1sum == 22 || Player2sum == 22 || Player3sum == 22 || Player4sum == 22) {
		Restart();
	}
	/*プラス4マスに止まったら 12 50*/
	if (Player1sum == 12 || Player2sum == 12 || Player3sum == 12 || Player4sum == 12 || Player1sum == 50 || Player2sum == 50 || Player3sum == 50 || Player4sum == 50) {
		Plus();	/*+4する*/
	}

	/*マイナス4マスに止まったら 36*/
	if (Player1sum == 36 || Player2sum == 36 || Player3sum == 36 || Player4sum == 36) {
		Minus();	/*-4する*/
	}

	switch (num) {
		case 1 :	/*プレイヤーのターン*/
			//DrawString(500, 600, "Playerのターン", GetColor(0, 0, 0));
			if (Click == true) {
				Replay = false;
				if (MouseX >= 1020 && MouseY >= 580 && MouseX <= 1250 && MouseY <= 700 && Whoisplay == true) {
					if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*もし左クリックしたら*/
						Shuffle = true;	/*シャッフルフラグをONに*/
					}
					else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true && Back == true) {	/*サイコロが出た分だけ戻るマス用（backフラグがある）*/
						Player1sum -= Sum;
						Shuffle = false;
						countdiff = count;
						Whoisplay = false;
						Replay = false;
						Back = false;
					}
					else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {
						Player1sum += Sum;
						Shuffle = false;
						countdiff = count;
						Whoisplay = false;
						Replay = false;
					}
				}
				if (Player1sum == 8 || Player1sum == 30) {
					Replay = true;
				}
				if (Player1sum == 19) { Replay = true; Back = true; }
			}
			if (Replay == true && count - countdiff == 100 && countdiff != 0) { current = 1; num = 6; countdiff = count; Whoisplay = true;}
			else if (Replay == false && count - countdiff == 100 && countdiff != 0) { countdiff = count;  num = 2;  Whoisplay = true;}	/*countが100進めば次のターン*/
			break;
		case 2:
			//DrawString(500, 600, "AI1のターン", GetColor(0, 0, 0));
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;	/*テキストを被らせないようにする*/
				Shuffle = true;		/*サイコロをシャッフルする*/
				Sumflg = true;		/*サイコロの合計値を足す*/
			}
			else {	/*cont300を超えたら*/
				Shuffle = false;	/*シャッフルを止める*/
				if (Sumflg == true && p == 0) {		
					p += 1;
					Player2sum += Sum;		/*サイコロの合計値を足す*/
					Replay = false;
				}
			}
			if (Player2sum == 8 || Player2sum == 30) {	/*もしリスタートますに乗ったら*/
				Replay = true;		/*リスタートフラグture*/
			}
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { current = 2; num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true;}		/**/
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = count;  num = 3; p = 0;  Sumflg = false; Whoisplay = true;  }	/*countが100進めば次のターン*/
			break;
		case 3:
			//DrawString(500, 600, "AI2のターン", GetColor(0, 0, 0));
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;
				Shuffle = true;
				Sumflg = true;
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player3sum += Sum;
					Replay = false;
				}
			}
			if (Player3sum == 8 || Player3sum == 30) {
				Replay = true;
			}
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { current = 3; num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true;  }
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = count;  num = 4; p = 0; Sumflg = false; Whoisplay = true;}	/*countが100進めば次のターン*/
			break;
		case 4:
			//DrawString(500, 600, "AI3のターン", GetColor(0, 0, 0));
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;
				Shuffle = true;
				Sumflg = true;
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player4sum += Sum;
					Replay = false;
				}
			}
			if (Player4sum == 8 || Player4sum == 30) {
				Replay = true;
			}
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { current = 4; num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true; }
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = 0;  num = 1; p = 0; Sumflg = false; Whoisplay = true;  }	/*countが100進めば次のターン*/
			break;
		case 5:
			break;
		case 6:
			if (current == 1) { num = 1; }
			else if (current == 2) { num = 2; }
			else if (current == 3) { num = 3; }
			else if (current == 4) { num = 4; }
			break;
	}

	if ((count / 4) % 2 == 0&& Shuffle == true) {
		y = GetRand(5);
		d = GetRand(5);
	}
	Sum = y + d + 2;	/*サイコロの合計値*/
}

void SR_Saikoro::Draw() {
	DrawGraph(1050, 600, SR_Saikoro1[y], true);
	DrawGraph(1140, 600, SR_Saikoro2[d], true);
  
	switch (num) {
	case 1:	/*プレイヤーの時*/
		if (Whoisplay == true) { DrawString(500, 600, "Playerのターン", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "プレイヤーは%d進んだ", Sum); }
		else if(Shuffle == true){ DrawString(500, 600, "サイコロコロコロ", GetColor(0, 0, 0)); }
		
		break;
	case 2:
		if (Whoisplay == true) { DrawString(500, 600, "Player2のターン", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) {DrawFormatString(500,600,GetColor(0, 0, 0),"Player2は%d進んだ", Sum); }
		else if (Shuffle == true) { DrawString(500, 600, "サイコロコロコロ", GetColor(0, 0, 0)); }
		break;
	case 3:
		if (Whoisplay == true) { DrawString(500, 600, "Player3のターン", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player3は%d進んだ", Sum); }
		else if (Shuffle == true) { DrawString(500, 600, "サイコロコロコロ", GetColor(0, 0, 0)); }
		break;
	case 4:
		if (Whoisplay == true) { DrawString(500, 600, "Player4のターン", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(500, 600, GetColor(0, 0, 0), "Player4は%d進んだ", Sum); }
		else if (Shuffle == true) { DrawString(500, 600, "サイコロコロコロ", GetColor(0, 0, 0)); }
		break;
	case 5:
		if (Goalflg == true) {
			DrawString(500, 600, "Goal!!", GetColor(0, 0, 0));
		}
		break;
	}
}

void SR_Saikoro::SR_Enemy1() {	/*AI1*/
	Shuffle = true;
}
void SR_Saikoro::SR_Enemy2() {	/*AI2*/
	Shuffle = true;
}
void SR_Saikoro::SR_Enemy3() {	/*AI3*/
	Shuffle = true;
}

void SR_Saikoro::Plus() {
	Player1sum += 4;
	Player2sum += 4;
	Player3sum += 4;
	Player4sum += 4;
}

void SR_Saikoro::Minus() {
	Player1sum -= 4;
	Player2sum -= 4;
	Player3sum -= 4;
	Player4sum -= 4;
}

void SR_Saikoro::ReDice() {
}

void SR_Saikoro::Restart() {
	if (Player1sum == 24) { Player1sum -= 24; }
	else if (Player2sum == 24) { Player2sum -= 24; }
	else if (Player3sum == 24) { Player3sum -= 24; }
	else if (Player4sum == 24) { Player4sum -= 24; }
}

void SR_Saikoro::Goal() {
	num = 5;
	Goalflg = true;
//	SetNext((new SR_Result));
}
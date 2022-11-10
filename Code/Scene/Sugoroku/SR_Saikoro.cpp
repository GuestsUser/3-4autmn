#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Map.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"
#include "SR_Result.h"
#include <stdio.h>
#include <stdlib.h>

int Player1sum;
int Player2sum;
int Player3sum;
int Player4sum;

SR_Saikoro::SR_Saikoro() {
	LoadDivGraph("Resource/image/SR_Saikoro1.png", 6, 6, 1, 75, 75, SR_Saikoro1, true);	/*サイコロ画像読み込み*/
	LoadDivGraph("Resource/image/SR_Saikoro2.png", 6, 6, 1, 75, 75, SR_Saikoro2, true);	/*サイコロ画像読み込み*/
	y = 0, d = 0, i = 0;	/*各種変数初期化*/
	count = 0;
	SRand(123456); // 乱数の初期値を123456に設定する

	Player1sum = 0;
	Player2sum = 0;
	Player3sum = 0;
	Player4sum = 0;
}

void SR_Saikoro::Update() {
	count++;
	GetMousePoint(&MouseX, &MouseY);/*マウス座標取得（仮）*/
	/*ゴールしたら*/
	if (Player1sum >= 64) {
		Goal();	/*まだ中身はない*/
		Player1sum = 64;
	}

	/*リスタートますに乗ったら*/
	if (Player1sum == 24) {	
		Restart();
	}

	//if (Click == true) {	/*サイコロ画像クリック可否フラグ*/
	if (MouseX >= 1020 && MouseY >= 580 && MouseX <= 1250 && MouseY <= 700) {
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*もし左クリックしたら*/
			Shuffle = true;	/*シャッフルフラグをONに*/
		}
		else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {
			Player1sum += Sum;
			Shuffle = false;
		}
	}
	if ((count / 4) % 2 == 0&& Shuffle == true) {
		y = GetRand(5);
		d = GetRand(5);
	}
	Sum = y + d + 2;	/*サイコロの合計値*/
}

void SR_Saikoro::Draw() {
	DrawString(0, 0, "双六ルール説明画像", GetColor(255, 255, 255));
	DrawFormatString(900, 600, GetColor(255, 255, 255), "%d", Sum);
	DrawGraph(1050, 600, SR_Saikoro1[y], true);
	DrawGraph(1140, 600, SR_Saikoro2[d], true);
	DrawFormatString(700, 600, GetColor(255, 255, 255), "%d", count);
	DrawFormatString(500, 600, GetColor(255, 255, 255), "%d", y);
	DrawFormatString(600, 600, GetColor(255, 255, 255), "%d", d);
	DrawFormatString(400, 600, GetColor(255, 255, 255), "%d", Player1sum);
}
//
//void SR_Enemy1() {
//	Shuffle = true;
//}
//void SR_Enemy2() {
//	Shuffle = true;
//}
//void SR_Enemy3() {
//	Shuffle = true;
//}
//void SR_Enemy4() {
//	Shuffle = true;
//}
void SR_Saikoro::Restart() {
	Player1sum -= 24;
}

void SR_Saikoro::Goal() {
//	SetNext((new SR_Result));
}
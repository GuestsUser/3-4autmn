#include"DxLib.h"
#include"./../Code/GetKey.h"
#include"Karu_Game.h"

#include <random>

int ix = 0, iy = 0;
int reset = 0;

bool Yomiset = false;

/*************************
** \‘¢‘Ì **
*************************/

struct EFUDA Efuda[KARU_MAX_Y][KARU_MAX_X];
struct YOMIFUDA Yomifuda[KARU_MAX_Y][KARU_MAX_X];
struct FUDA Fuda[100];


void Karu_Game::Karu_Game_Initialize() {

	Karu_Bg = LoadGraph("Resource/image/Karu_Image/Karu_Tatami.png");		//”wŒi‰æ‘œ‚ğKaru_Bg‚ÉŠi”[
	Karu_SideBg = LoadGraph("Resource/image/Karu_Image/Karu_Side_Bg.png");	//ƒTƒCƒh”wŒi‰æ‘œ‚ğKaru_SideBg‚ÉŠi”[

	//ŠGD‰æ‘œ‚ğ•ªŠ„‚µ‚ÄKaru_fuda‚ÉŠi”[
	LoadDivGraph("Resource/image/Karu_Image/Karu_Fuda.png", 100, 10, 10, Karu_imgX, Karu_imgY, *Karu_fuda, TRUE);
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
				Efuda[i][j] = { 0,0,0,0,0,true };
				Yomifuda[i][j] = { 0,0,0,true };
		}
	}
	for (int z = 0; z < 100; z++) {
		Fuda[z].get = false;
	}
}
void Karu_Game::Karu_Game_Finalize() {
	DeleteGraph(Karu_Bg);

}
void Karu_Game::Karu_Game_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y); //ƒ}ƒEƒX‚ÌÀ•Wæ“¾
	if(key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ¶ƒNƒŠƒbƒN‚µ‚½‚ç

		Mouse_HitBox();		//‚©‚é‚½‚ÉG‚ê‚Ä‚¢‚é‚©Šm”F

	}
	if (reset < 44) {
		Efuda_Storage();
	}

	if (!Yomiset) {
		Yomifuda_Storage();
	}

	if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) { // ‰EƒNƒŠƒbƒN‚µ‚½‚ç
		//ŠGD‘“ü‚ê‘Ö‚¦
		for (int i = 0; i < KARU_MAX_Y; i++) {
			for (int j = 0; j < KARU_MAX_X; j++) {
				Efuda[i][j] = { 0,0,0,0,0,true };
			}
			for (int z = 0; z < 100; z++) {
				Fuda[z].get = false;
			}
			Yomiset = false;
			reset = 0;
		}
	}

	/*if (reset >= 44) {
		for (int z = 0; z < 100; z++) {
			Fuda[z].get = false;
		}
		reset = 0;
	}*/

}
void Karu_Game::Karu_Game_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, Karu_Bg, TRUE);
	DrawRotaGraph(1100, 360, 1.0, 0, Karu_SideBg, TRUE);
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			if (!Efuda[i][j].kara) {
				DrawRotaGraph((Efuda[i][j].x) + Karu_Space, (Efuda[i][j].y) + Karu_Space, 1.0, 0, Efuda[i][j].img, TRUE);
			}
		}
	}
	DrawRotaGraph(1000, 600, 1.0, 0, Yomifuda[0][0].img, TRUE);

	DrawFormatString(0, 0, 0xFF0000, "X: %d  Y: %d  SUCCESS", ix, iy);
}

void Karu_Game::Mouse_HitBox() {
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			if (Mouse_X > (Efuda[i][j].x - (Karu_imgX / 2)) && Mouse_X < (Efuda[i][j].x + (Karu_imgX / 2)) &&
				Mouse_Y >(Efuda[i][j].y - (Karu_imgY / 2)) && Mouse_Y < (Efuda[i][j].y + (Karu_imgY / 2))) {
				ix = j;
				iy = i;
				Efuda[i][j].kara = true;
			}
		}
	}
}

/*****************
** ŠGD‚ÌŠi”[ **
* ˆø”  :‚È‚µ
* –ß‚è’l:‚È‚µ
******************/
void Karu_Game::Efuda_Storage() {
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			if (Efuda[i][j].kara) {
				int X = 0, Y = 0;
				do {
					Y = GetRand(9);
					X = GetRand(4) * 2;
				} while ((Y == 7 && X == 2) || (Y == 7 && X == 6) ||
					(Y == 9 && X == 2) || (Y == 9 && X == 4) ||
					(Y == 9 && X == 6) || (Y == 9 && X == 8) || Fuda[(Y * 10) + X].get == true);

				Efuda[i][j] = { (j * Karu_imgX) + (Karu_imgX / 2),(i * Karu_imgY) + (Karu_imgY / 2),Karu_fuda[Y][X],X,Y,false };
				Fuda[(Y * 10) + X].get = true;
				reset++;
			}
		}
	}
}

/*****************
** “Ç‚İD‚ÌŠi”[ **
* ˆø”  :‚È‚µ
* –ß‚è’l:‚È‚µ
******************/
void Karu_Game::Yomifuda_Storage() {
	int x = GetRand(KARU_MAX_X);
	int y = GetRand(KARU_MAX_Y);

	if (Yomifuda[0][0].kara) {
		Yomifuda[0][0].img = Karu_fuda[Efuda[y][x].numY][(Efuda[y][x].numX) + 1];
		Yomifuda[0][0].kara = false;
		Yomiset = true;
	}
}
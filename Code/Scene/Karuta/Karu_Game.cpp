#include"DxLib.h"
#include"./../Code/GetKey.h"
#include"Karu_Game.h"

#include <random>

int ix = 0, iy = 0;
int reset = 0;

bool Yomiset = false;

bool Otetuki = false;
int Otetuki_AnimTime = 0;

/*************************
** 構造体 **
*************************/

struct EFUDA Efuda[KARU_MAX_Y][KARU_MAX_X];
struct YOMIFUDA Yomifuda[KARU_MAX_Y][KARU_MAX_X];
struct FUDA Fuda[100];
struct PLAYER player;


void Karu_Game::Karu_Game_Initialize() {

	Karu_Bg = LoadGraph("Resource/image/Karu_Image/Karu_Tatami.png");		//背景画像をKaru_Bgに格納
	Karu_SideBg = LoadGraph("Resource/image/Karu_Image/Karu_Side_Bg.png");	//サイド背景画像をKaru_SideBgに格納

	LoadDivGraph("Resource/image/Karu_Image/Karu_Otetuki.png", 2, 2, 1, 100, 100, Karu_Otetuki_img, TRUE);

	Fuda_voice[0][0] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Atama.wav");
	Fuda_voice[0][2] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Inu.wav");
	Fuda_voice[0][4] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Uma.wav");
	Fuda_voice[0][6] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Ebi.wav");
	Fuda_voice[0][8] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Oni.wav");
	Fuda_voice[1][0] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Kapa.wav");
	Fuda_voice[1][2] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Kyusi.wav");
	Fuda_voice[1][4] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Kusai.wav");
	Fuda_voice[1][6] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Kega.wav");
	Fuda_voice[1][8] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Koi.wav");
	Fuda_voice[2][0] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Saru.wav");
	Fuda_voice[2][2] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Siranu.wav");
	Fuda_voice[2][4] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Sumeba.wav");
	Fuda_voice[2][6] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Senri.wav");
	Fuda_voice[2][8] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Sonae.wav");
	Fuda_voice[3][0] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Tanuki.wav");
	Fuda_voice[3][2] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Tiritumo.wav");
	Fuda_voice[3][4] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Tuki.wav");
	Fuda_voice[3][6] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Teki.wav");
	Fuda_voice[3][8] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Touhu.wav");
	Fuda_voice[4][0] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Naki.wav");
	Fuda_voice[4][2] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Nikai.wav");
	Fuda_voice[4][4] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Nureginu.wav");
	Fuda_voice[4][6] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Neko.wav");
	Fuda_voice[4][8] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Noren.wav");
	Fuda_voice[5][0] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/Hana.wav");
	Fuda_voice[5][2] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/HIni.wav");
	Fuda_voice[5][4] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/Hundari.wav");
	Fuda_voice[5][6] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/Hebi.wav");
	Fuda_voice[5][8] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/Hotoke.wav");
	Fuda_voice[6][0] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Manaita.wav");
	Fuda_voice[6][2] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Mizu.wav");
	Fuda_voice[6][4] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Mukasi.wav");
	Fuda_voice[6][6] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Mekara.wav");
	Fuda_voice[6][8] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Moroha.wav");
	Fuda_voice[7][0] = LoadSoundMem("Resource/se/Karu_SE/YaGroup/Yake.wav");
	Fuda_voice[7][4] = LoadSoundMem("Resource/se/Karu_SE/YaGroup/Yudan.wav");
	Fuda_voice[7][8] = LoadSoundMem("Resource/se/Karu_SE/YaGroup/Yorime.wav");
	Fuda_voice[8][0] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Rati.wav");
	Fuda_voice[8][2] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Ryouyaku.wav");
	Fuda_voice[8][4] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Ruitomo.wav");
	Fuda_voice[8][6] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Reiniyotte.wav");
	Fuda_voice[8][8] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Ronyori.wav");
	Fuda_voice[9][0] = LoadSoundMem("Resource/se/Karu_SE/WaGroup/Wara.wav");


	//絵札画像を分割してKaru_fudaに格納
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

	Karu_Otetuki = 0;

	player.myFuda = 0;
}
void Karu_Game::Karu_Game_Finalize() {
	DeleteGraph(Karu_Bg);

}
void Karu_Game::Karu_Game_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y); //マウスの座標取得
	if (!end) {
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら

			Mouse_HitBox();		//かるたに触れているか確認

		}
		if (reset < 44) {
			Efuda_Storage();
		}

		if (!Yomiset) {
			Yomifuda_Storage();
		}

	}
	if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) { // 右クリックしたら
		//絵札総入れ替え
		for (int i = 0; i < KARU_MAX_Y; i++) {
			for (int j = 0; j < KARU_MAX_X; j++) {
				Efuda[i][j] = { 0,0,0,0,0,true };
			}
			for (int z = 0; z < 100; z++) {
				Fuda[z].get = false;
			}
			Yomifuda[0][0].kara = true;
			Yomiset = false;
			reset = 0;
		}
		end = false;
		Karu_Otetuki = 0;
		player.myFuda = 0;
	}

	/*if (reset >= 44) {
		for (int z = 0; z < 100; z++) {
			Fuda[z].get = false;
		}
		reset = 0;
	}*/
	Otetuki_Anim();
}
void Karu_Game::Karu_Game_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, Karu_Bg, TRUE);
	DrawRotaGraph(1100, 360, 1.0, 0, Karu_SideBg, TRUE);
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			if (!Efuda[i][j].kara) {
				DrawRotaGraph((Efuda[i][j].x) + (Karu_Space * j + Karu_Space), (Efuda[i][j].y) + (Karu_Space * i + Karu_Space), 1.0, 0, Efuda[i][j].img, TRUE);
			}
		}
	}
	DrawRotaGraph(1080, 520, 1.7, 0, Yomifuda[0][0].img, TRUE);
	for (int o = 0; o < 3;o++) {
		if (Karu_Otetuki > o ) {
			DrawRotaGraph(1000 + (100 * o), 290, 1.0, 0, Karu_Otetuki_img[1], TRUE);
		}
		else {
			DrawRotaGraph(1000 + (100 * o), 290, 1.0, 0, Karu_Otetuki_img[0], TRUE);
		}
	}

	if (Otetuki) {
		DrawRotaGraph(Mouse_X, Mouse_Y, 1.0, 0, Karu_Otetuki_img[1], TRUE);
	}

	/*DrawFormatString(800, 0, 0xFF0000, "X: %d  Y: %d", ix, iy);
	DrawFormatString(800, 100, 0xFF0000, "Reset_score: %d", reset);
	DrawFormatString(800, 200, 0xFF0000, "OTETUKI: %d", Karu_Otetuki);
	DrawFormatString(800, 300, 0xFF0000, "PLAYER 1: %d", player.myFuda);
	if (end) {
		DrawFormatString(800, 400, 0xFF0000, "END");
	}*/
}

void Karu_Game::Mouse_HitBox() {
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			if (Mouse_X > (Efuda[i][j].x - (Karu_imgX / 2)) && Mouse_X < (Efuda[i][j].x + (Karu_imgX / 2)) &&
				Mouse_Y >(Efuda[i][j].y - (Karu_imgY / 2)) && Mouse_Y < (Efuda[i][j].y + (Karu_imgY / 2))) {
				ix = j;
				iy = i;
				if (Yomifuda[0][0].img == Karu_fuda[Efuda[i][j].numY][(Efuda[i][j].numX) + 1]) {
					Efuda[i][j].kara = true;
					Yomifuda[0][0].kara = true;
					Yomiset = false;
					player.myFuda++;
				}
				else {
					Otetuki = true;
					if (Karu_Otetuki < KARU_OTETUKI_MAX) {
						Karu_Otetuki++;
					}
					else {
						Karu_Otetuki++;
						Karu_GameOver();
					}
				}
			}
		}
	}
}

/*****************
** 絵札の格納 **
* 引数  :なし
* 戻り値:なし
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
** 読み札の格納 **
* 引数  :なし
* 戻り値:なし
******************/
void Karu_Game::Yomifuda_Storage() {
	int x, y;
	do {
		x = GetRand(KARU_MAX_X - 1);
		y = GetRand(KARU_MAX_Y - 1);
	} while (Efuda[y][x].kara && player.myFuda < 44);

	if (Yomifuda[0][0].kara) {
		Yomifuda[0][0].img = Karu_fuda[Efuda[y][x].numY][(Efuda[y][x].numX) + 1];
		PlaySoundMem(Fuda_voice[Efuda[y][x].numY][Efuda[y][x].numX], DX_PLAYTYPE_NORMAL);
		Yomifuda[0][0].kara = false;
		Yomiset = true;
	}
}

void Karu_Game::Otetuki_Anim() {
	if (Otetuki) {
		if (Otetuki_AnimTime < 60) {
			Otetuki_AnimTime++;
		}
		else {
			Otetuki = false;
			Otetuki_AnimTime = 0;
		}
	}
}

void Karu_Game::Karu_GameOver() {
	end = true;
}
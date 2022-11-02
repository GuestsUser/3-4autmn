#include"DxLib.h"
#include"./../Code/GetKey.h"
#include"Karu_Game.h"

#include <random>


int x = 0, y = 0;

void Karu_Game::Karu_Game_Initialize() {

	Karu_Bg = LoadGraph("Resource/image/Karu_Tatami.png");		//背景画像をKaru_Bgに格納
	Karu_SideBg = LoadGraph("Resource/image/Karu_Side_Bg.png");	//サイド背景画像をKaru_SideBgに格納

	//絵札画像を分割してKaru_fudaに格納
	LoadDivGraph("Resource/image/Karu_Fuda.png", 100, 10, 10, Karu_imgX, Karu_imgY, *Karu_fuda, TRUE);
}
void Karu_Game::Karu_Game_Finalize() {
	DeleteGraph(Karu_Bg);

}
void Karu_Game::Karu_Game_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y); //マウスの座標取得
	if(key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら

		Mouse_HitBox();		//かるたに触れているか確認
	}
}
void Karu_Game::Karu_Game_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, Karu_Bg, TRUE);
	DrawRotaGraph(1100, 360, 1.0, 0, Karu_SideBg, TRUE);
	DrawRotaGraph(640, 360, 1.0, 0, Karu_fuda[y][x], TRUE);
}

void Karu_Game::Mouse_HitBox() {

}
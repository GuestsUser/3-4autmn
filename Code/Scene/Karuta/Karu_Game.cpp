#include"DxLib.h"
#include"./../Code/GetKey.h"
#include"Karu_Game.h"

#include <random>


int x = 0, y = 0;

void Karu_Game::Karu_Game_Initialize() {

	Karu_Bg = LoadGraph("Resource/image/Karu_Tatami.png");		//îwåiâÊëúÇKaru_BgÇ…äiî[
	Karu_SideBg = LoadGraph("Resource/image/Karu_Side_Bg.png");	//ÉTÉCÉhîwåiâÊëúÇKaru_SideBgÇ…äiî[

	//äGéDâÊëúÇï™äÑÇµÇƒKaru_fudaÇ…äiî[
	LoadDivGraph("Resource/image/Karu_Fuda.png", 100, 10, 10, Karu_imgX, Karu_imgY, *Karu_fuda, TRUE);
}
void Karu_Game::Karu_Game_Finalize() {
	DeleteGraph(Karu_Bg);

}
void Karu_Game::Karu_Game_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y); //É}ÉEÉXÇÃç¿ïWéÊìæ
	if(key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ç∂ÉNÉäÉbÉNÇµÇΩÇÁ

		Mouse_HitBox();		//Ç©ÇÈÇΩÇ…êGÇÍÇƒÇ¢ÇÈÇ©ämîF
	}
}
void Karu_Game::Karu_Game_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, Karu_Bg, TRUE);
	DrawRotaGraph(1100, 360, 1.0, 0, Karu_SideBg, TRUE);
	DrawRotaGraph(640, 360, 1.0, 0, Karu_fuda[y][x], TRUE);
}

void Karu_Game::Mouse_HitBox() {

}
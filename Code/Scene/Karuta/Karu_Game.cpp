#include"DxLib.h"
#include"./../Code/GetKey.h"
#include"Karu_Game.h"

void Karu_Game::Karu_Game_Initialize() {
	Karu_Bg = LoadGraph("Resource/image/Karu_Tatami.png");
	LoadDivGraph("Resource/image/Karu_Fuda.png",100,10,10,Karu_imgX,Karu_imgY,*Karu_fuda,TRUE);

}
void Karu_Game::Karu_Game_Finalize() {
	DeleteGraph(Karu_Bg);

}
void Karu_Game::Karu_Game_Update() {

}
void Karu_Game::Karu_Game_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, Karu_Bg, TRUE);
	
	for (float j = Karu_StartPosY; j < (Karu_imgY * Karu_MaxY); j += (Karu_imgY * Karu_Y) + Karu_Space) {
		for (float i = Karu_StartPosX; i < (Karu_imgX * Karu_MaxX); i += (Karu_imgX * Karu_X) + Karu_Space) {

			DrawRotaGraph(i, j, 1.0, 0, Karu_fuda[4][6], TRUE);
			Karu_X++;
		}
		Karu_Y++;
	}
}
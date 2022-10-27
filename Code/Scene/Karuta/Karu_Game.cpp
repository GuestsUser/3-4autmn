#include"DxLib.h"
#include"./../Code/GetKey.h"
#include"Karu_Game.h"

#include <random>


void Karu_Game::Karu_Game_Initialize() {
	Karu_Bg = LoadGraph("Resource/image/Karu_Tatami.png");
	Karu_SideBg = LoadGraph("Resource/image/Karu_Side_Bg.png");
	LoadDivGraph("Resource/image/Karu_Fuda.png",100,10,10,Karu_imgX,Karu_imgY,*Karu_fuda,TRUE);

}
void Karu_Game::Karu_Game_Finalize() {
	DeleteGraph(Karu_Bg);

}
void Karu_Game::Karu_Game_Update() {

}
void Karu_Game::Karu_Game_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, Karu_Bg, TRUE);
	DrawRotaGraph(1100, 360, 1.0, 0, Karu_SideBg, TRUE);

	for (float j = Karu_StartPosY; j < ((Karu_imgY + Karu_Space) * KARU_MAX_Y); j += Karu_imgY + Karu_Space) {
		for (float i = Karu_StartPosX; i < ((Karu_imgX + Karu_Space) * KARU_MAX_X); i += Karu_imgX + Karu_Space) {

			DrawRotaGraph(i, j, 1.0, 0, Karu_fuda[0][6], TRUE);
			
		}
	}
}
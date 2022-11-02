#include"DxLib.h"
#include"./../Code/GetKey.h"
#include"Karu_Game.h"

#include <random>


int x = 0, y = 0;

void Karu_Game::Karu_Game_Initialize() {

	Karu_Bg = LoadGraph("Resource/image/Karu_Tatami.png");		//�w�i�摜��Karu_Bg�Ɋi�[
	Karu_SideBg = LoadGraph("Resource/image/Karu_Side_Bg.png");	//�T�C�h�w�i�摜��Karu_SideBg�Ɋi�[

	//�G�D�摜�𕪊�����Karu_fuda�Ɋi�[
	LoadDivGraph("Resource/image/Karu_Fuda.png", 100, 10, 10, Karu_imgX, Karu_imgY, *Karu_fuda, TRUE);
}
void Karu_Game::Karu_Game_Finalize() {
	DeleteGraph(Karu_Bg);

}
void Karu_Game::Karu_Game_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y); //�}�E�X�̍��W�擾
	if(key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������

		Mouse_HitBox();		//���邽�ɐG��Ă��邩�m�F
	}
}
void Karu_Game::Karu_Game_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, Karu_Bg, TRUE);
	DrawRotaGraph(1100, 360, 1.0, 0, Karu_SideBg, TRUE);
	DrawRotaGraph(640, 360, 1.0, 0, Karu_fuda[y][x], TRUE);
}

void Karu_Game::Mouse_HitBox() {

}
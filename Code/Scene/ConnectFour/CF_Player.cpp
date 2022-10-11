#include"CF_Player.h"
#include"DxLib.h"

//CF_Player cf_player;
void CF_Player::CF_Player_Initialize() {
	CF_Back = LoadGraph("Resource/image/CF_Back.png");
	CF_Panel = LoadGraph("Resource/image/CF_Panel.png");
}
void CF_Player::CF_Player_Finalize() {
	DeleteGraph(CF_Back);
	DeleteGraph(CF_Panel);
}
void CF_Player::CF_Player_Update() {

}
void CF_Player::CF_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, CF_Back, TRUE);
	DrawRotaGraph(640, 420, 0.8, 0, CF_Panel, TRUE);
}
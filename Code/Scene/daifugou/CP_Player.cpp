#include"DxLib.h"
#include"CP_Player.h"
#include"./../Code/GetKey.h"
//‘å•x‹ƒvƒŒƒCƒ„[
void CareerPoker::CP_Player_Initialize(){
	//rule = LoadGraph("Code/Scene/daifugou/images/rule.png");//ƒ‹[ƒ‹‰æ‘œ
	stage = LoadGraph("Code/Scene/daifugou/images/CareerPoker.png");//”wŒi‰æ‘œ
}

void CareerPoker::CP_Player_Finalize() {
	DeleteGraph(stage);
}
void CareerPoker::CP_Player_Update() {

}

void CareerPoker::CP_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0 , 0, stage, TRUE);
}


#include"DxLib.h"
#include"CP_Player.h"
#include"./../Code/GetKey.h"
//��x���v���C���[
void CareerPoker::CP_Player_Initialize(){
	//rule = LoadGraph("Code/Scene/daifugou/images/rule.png");//���[���摜
	stage = LoadGraph("Resource/image/CareerPoker.png");//�w�i�摜
	LoadDivGraph("Resource/image/toranpu_all.png",53,13,5,200,300, *cards,TRUE);
	for (int i = 0; i < 4; i++) {
		printf("�����Z");
	}
}

void CareerPoker::CP_Player_Finalize() {
	DeleteGraph(stage);
}
void CareerPoker::CP_Player_Update() {
	
}

void CareerPoker::CP_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0 , 0, stage, TRUE);
	DrawRotaGraph(100, 200, 0.5, 0, cards[0][0], TRUE);
}


#include"CP_Scene.h"
#include"CP_Player.h"
#include"daifugou.h"
CP_Scene::CP_Scene(){
	/*Player = new CareerPoker();
	Player->CP_Player_Initialize();*/
	Player = new CP();
	Player->Player_Initialize();
	Player->onesec();//��b������
	Player->deckmake();//�f�b�L���Z�b�g
	Player->deckshuffle();//�f�b�L���V���b�t��
}
CP_Scene::~CP_Scene() {
	//delete Player;
	delete Player;
}
void CP_Scene::Update() {
	//Player->CP_Player_Update();
	Player->Player_Update();
	/*Player->elevenback();//11�o�b�N
	Player->datareset();//�f�[�^���Z�b�g
	Player->d3start();//�_�C��3�������Ă���l����X�^�[�g
	Player->dealcards();
	Player->revolution();*/
}

void CP_Scene::Draw() {
	//Player->CP_Player_Draw();
	Player->CP::Player_Draw();
	/*Player->main();*/
}
#include"CP_Scene.h"
#include"CP_Player.h"
#include"daifugou.h"
CP_Scene::CP_Scene(){
	//Player = new CareerPoker();
	//Player->CP_Player_Initialize();
	Player = new CP();
	Player->Player_Initialize();
}
CP_Scene::~CP_Scene() {
	//delete Player;
	delete Player;
}
void CP_Scene::Update() {
	//Player->CP_Player_Update();
	Player->onesec();//一秒数える
	Player->deckmake();//デッキをセット
	Player->deckshuffle();//デッキをシャッフル
	Player->elevenback();//11バック
	Player->datareset();//データをセット
	Player->d3start();//ダイヤ3を持っている人からスタート
	Player->title();//タイトル※こいつは消す
	Player->main();
	Player->dealcards();
	Player->revolution();
	Player->elevenback();
}

void CP_Scene::Draw() {
	Player->CP_Player_Draw();
}
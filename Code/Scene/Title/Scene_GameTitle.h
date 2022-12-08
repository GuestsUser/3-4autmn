#pragma once
#include "./../Scene.h"

class Scene_GameTitle : public Scene { //最初のタイトル画面
private:
	int keyOld; //前回の左クリック入力状態を保存する
	int image; //タイトル画像格納用変数
	int Click;
	int BGM;
public:
	Scene_GameTitle();
	~Scene_GameTitle();
	void Update();
	void Draw();
};
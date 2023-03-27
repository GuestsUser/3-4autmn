#pragma once
#include "./../Scene.h"

class Title : public Scene { //最初のタイトル画面
private:
	int keyOld; //前回の左クリック入力状態を保存する
	int image; //タイトル画像格納用変数
	int Click;
	int BGM;
public:
	Title();
	~Title();
	void Update();
	void Draw();
};
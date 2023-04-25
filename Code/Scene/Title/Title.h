#pragma once
#include "./../Scene.h"

#include "Cmp_3DSoundListener.h"

class Cmp_Sound;

class Title : public Scene { //最初のタイトル画面
private:
	int keyOld; //前回の左クリック入力状態を保存する
	int image; //タイトル画像格納用変数

	Cmp_Sound* bgm; //bgmのサウンドを管理するコンポーネント
	Cmp_Sound* click; //クリックのサウンドを管理するコンポーネント
public:
	Title();
	~Title();
	void Update();
	void Draw();
};
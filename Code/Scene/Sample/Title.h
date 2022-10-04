#pragma once
#include "./../Scene.h"

class Title : public Scene {
private:
	enum class State { Moving, Stop }; //Moving=タイトル画面が上から上ってくる処理を行う Stop=次シーンへ移行する為にボタン入力を受け付ける処理を行う
	State state; //Updateで現在実行すべき処理を分岐する為の変数

	//座標変数
	int posX;
	int posY;
	int titleImage; //タイトル画像格納用変数
	int scrollSpeed; //画面スクロールのスピード

	int* score; //WorldValから手に入れたアドレスを保持する変数
	int* hiscore; //上記同様の保存用変数

	void Move(); //画像スクロール用関数
public:
	Title();
	~Title();
	void Update();
	void Draw();

};

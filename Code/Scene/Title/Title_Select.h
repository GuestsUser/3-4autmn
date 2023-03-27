#pragma once
#include "./../Scene.h"

#include <deque>

class Button;
class Title_Select_Explain;

class Title_Select :public Scene { //セレクト画面
	std::deque<Title_Select_Explain*> explain; //ゲームの説明画面
	std::deque<Button*> button; //説明画面へ飛ばす為のボタン

	Scene* run; //現在実行するシーン、nullptrで自身、explainの何れかならそのシーン、explainに無いシーンが入っていた場合SetNextにrunをセットして指定ゲームへ移行
private:
	int BGM;
public:
	Title_Select();
	~Title_Select();

	void Update();
	void Draw();
};
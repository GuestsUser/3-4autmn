#pragma once
#include "./../Scene.h"

#include <deque>

class Button;
class Scene_Explain;

class Scene_Select :public Scene { //セレクト画面
	std::deque<Scene_Explain*> explain; //ゲームの説明画面
	std::deque<Button*> button; //説明画面へ飛ばす為のボタン

	Scene* run; //現在実行するシーン、nullptrで自身、explainの何れかならそのシーン、explainに無いシーンが入っていた場合SetNextにrunをセットして指定ゲームへ移行

public:
	Scene_Select();
	~Scene_Select();

	void Update();
	void Draw();
};
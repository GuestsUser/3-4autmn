#pragma once
#include "../Code/Scene/Scene.h"

#include <deque>

class Cmp_Image;
class Button;
class Scene;

class Scene_Explain :public Scene {
	std::deque<Cmp_Image*>* image; //説明用画像、呼び出し側でdeque配列を作成し、そのアドレスを受け取る形式
	std::deque<Cmp_Image*> cursor; //スクロール可能である事を示す矢印画像
	std::deque<Button*> button; //ゲーム画面に飛ぶ機能を持つ[0]ボタンとセレクト画面に飛ぶ[1]ボタン
	Scene* run; //次実行するシーン入れ
	int page; //説明画像の現在ページ数
	
public:
	Scene_Explain(std::deque<Cmp_Image*>& setImage, Scene* playGame);
	~Scene_Explain();

	void Update();
	void Draw();
};
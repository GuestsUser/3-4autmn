#pragma once
#include "../Code/Scene/Scene.h"

#include <deque>
#include <functional>

class Cmp_Image;
class Cmp_Sound;
class Button;
class Scene;
class Title_Select_Explain_PageScrollExplain;

class Title_Select_Explain :public Scene {
	std::deque<Cmp_Image*>* image; //説明用画像、呼び出し側でdeque配列を作成し、そのアドレスを受け取る形式
	std::deque<Button*> button; //ゲーム画面に飛ぶ機能を持つ[0]ボタンとセレクト画面に飛ぶ[1]ボタン
	Cmp_Sound* scroll; //マウスホイール操作があった場合鳴らす音
	Scene* run; //次実行するシーン入れ
	Title_Select_Explain_PageScrollExplain* scrollExplain; //ページスクロール可能な場合表示するメッセージ
	int page; //説明画像の現在ページ数
	
public:
	Title_Select_Explain(std::deque<Cmp_Image*>& setImage, std::function<Scene* ()> sceneCreator);
	~Title_Select_Explain();

	void Update();
	void Draw();

	void Reset();
	void FullReset() { Reset(); }
};
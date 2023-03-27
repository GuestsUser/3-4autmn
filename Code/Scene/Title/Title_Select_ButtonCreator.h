#pragma once

#include <deque>

class Button;
class Title_Select_Explain;
class Scene;

class Title_Select_ButtonCreator {

public:
	static void Creat(Scene& parent, std::deque<Title_Select_Explain*>& explain, std::deque<Button*>& button, Scene*& run); //セレクト画面に表示する各種ゲームへ飛ぶボタンの作成を行う

	//実体精製禁止
	Title_Select_ButtonCreator() = delete;
	Title_Select_ButtonCreator(const Title_Select_ButtonCreator&) = delete;
};
#pragma once
#include "Component.h"
#include "Cmp_PK_Pause.h"

class Button;

class Cmp_PK_Pause::GameEnd :public Component { //Pause内のゲーム終了ボタンのclickに付けるタイトル画面へ戻る機能
	Cmp_PK_Pause* parent;
	Button* parentButton;

	int count; //この機能を持つボタンがクリックされてからの時間経過記録
	int runTime; //記録時間がこの時間を超えたらゲームをリセットする機能の実行を行う
public:
	GameEnd(Cmp_PK_Pause& parent, Button& parentButton) :parent(&parent), parentButton(&parentButton), count(0), runTime(30) {}

	void Update();

	void FullReset() { Reset(); }
	void Reset() { count = 0; }
};
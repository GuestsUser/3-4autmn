#pragma once
#include "Component.h"
#include "Cmp_PK_Pause.h"

class Button;

class Cmp_PK_Pause::PauseEnd :public Component { //Pause内のゲーム続行ボタンのclickに付けるポーズ画面を終了しPokerへ戻る機能
	Cmp_PK_Pause* parent;
	Button* parentButton;

public:
	PauseEnd(Cmp_PK_Pause& parent, Button& parentButton) :parent(&parent), parentButton(&parentButton) {}

	void Update();

	static void Close(Cmp_PK_Pause& pause); //ポーズ画面を閉じる機能を実行
};
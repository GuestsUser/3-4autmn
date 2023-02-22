#pragma once
#include "../Scene.h"
#include "Poker.h"

#include "../Code/Component/Component.h"
#include "../Code/Component/Button.h"

class Vector3;

class Poker::GameOver :public Scene {
	Poker* parent; //このクラスの実体を持つPokerへの参照
	Button nextButton; //クリックする事で次シーンへ移行する

	int count;
	int clickStartTime; //countがこの数値に達するとボタンクリックの検知を開始する
	int blink; //この時間間隔で説明を点滅させる

	Vector3 titlePos; //ゲームオーバーである事を示すメッセージの表示位置
	Vector3 explainPos; //ボタン説明の配置位置
public:
	GameOver(Poker& set);
	void Update();
	void Draw();
};
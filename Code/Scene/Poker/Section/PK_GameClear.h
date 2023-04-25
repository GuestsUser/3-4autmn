#pragma once
#include "Scene.h"
#include "Poker.h"

#include "Component.h"
#include "Button.h"
#include "OriginMath.h"

class Cmp_Sound;

class Poker::GameClear :public Scene {
	Poker* parent; //このクラスの実体を持つPokerへの参照
	Button nextButton; //クリックする事で次シーンへ移行する

	int count;
	int clickStartTime; //countがこの数値に達するとボタンクリックの検知を開始する
	int blink; //この時間間隔で説明を点滅させる

	Vector3 titlePos; //ゲームクリアである事を示すメッセージの表示位置
	Vector3 explainPos; //ボタン説明の配置位置

	Cmp_Sound* sound; //ゲームオーバーである事を表すようなサウンド
public:
	GameClear(Poker& set);
	~GameClear() { delete sound; }
	void Update();
	void Draw();

	void FullReset() { Reset(); } //Resetと同様
	void Reset(); //画面クリック検知用ボタンと時間経過記録用カウントのリセット
};

#pragma once
#include "../Scene.h"
#include "Poker.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Button.h"

#include <deque>

class Cmp_Image;
class Cmp_BetActionRecord;
class Vector3;

class Poker::NoContest :public Scene {
	Poker* parent; //このクラスの実体を持つPokerへの参照
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる
	Button nextButton; //クリックする事で次シーンへ移行する

	int count;
	int payOutTime; //このタイミングで支払いを行う
	int clickStartTime; //countがこの数値に達するとボタンクリックの検知を開始する
	int blink; //この時間間隔で説明を点滅させる

	Vector3 titlePos; //ノーコンテストである事を示すメッセージの表示位置
	Vector3 explainPos; //ボタン説明の配置位置
public:
	NoContest(Poker& set);
	void Update();
	void Draw();
};
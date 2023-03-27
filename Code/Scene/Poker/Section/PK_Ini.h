#pragma once
#include "Scene.h"
#include "Poker.h"
#include "Component.h"

#include <deque>

class Cmp_BetActionRecord;

class Poker::Ini :public Scene { //ラウンド開始時の処理を記したUpdateを持つ初期化クラス
	Poker* parent; //このクラスの実体を持つPokerへの参照
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる

public:
	Ini(Poker& set);
	void Update();
};

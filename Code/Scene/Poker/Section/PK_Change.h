#pragma once
#include "Scene.h"
#include "Poker.h"

#include "Component.h"

#include <deque>

class Cmp_BetActionRecord;

class Poker::Change :public Scene { //カードを各キャラへ配るフェイズ
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる

	Poker* parent; //このクラスの実体を持つPokerへの参照
public:
	Change(Poker& set);
	void Update();
};
#pragma once
#include "Scene.h"
#include "Poker.h"

#include "Component.h"
#include "OriginMath.h"

#include <deque>
#include <string>

class Cmp_BetActionRecord;
class Cmp_Sound;

class Poker::ShowDown :public Scene {
	Poker* parent; //このクラスの実体を持つPokerへの参照
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる

	std::deque<std::deque<int>> hand; //各キャラのハンド評価を保持
	std::deque<Vector3> handPos; //各キャラのハンドを表示する為の位置集め配列
	std::deque<std::string> handString; //各キャラのハンドをstring型で保持する配列

	int count;

	Vector3 titlePos; //ショーダウンである事を示すメッセージの表示位置
public:
	ShowDown(Poker& set);
	void Update();
	void Draw();
};
#pragma once
#include "Scene.h"
#include "Poker.h"
#include "Component.h"

#include <deque>

class Cmp_BetActionRecord;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;
class Gage;

class Poker::Pre :public Scene { //カードを各キャラへ配るフェイズ
	Poker* parent; //このクラスの実体を持つPokerへの参照
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる
	Gage* playerGage; //プレイヤー保持のゲージ
	Cmp_Gage_Border* playerGageBorder; //プレイヤーのゲージ下限設定機能のコンポーネント
	Cmp_Gage_UpperBorder* playerGageUpper; //プレイヤーのゲージ上限設定機能のコンポーネント

public:
	Pre(Poker& set);
	void Update();
};
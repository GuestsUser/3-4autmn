#pragma once
#include "Poker.h"
#include "Scene.h"

class Poker::NewGameReset :public Scene { //新しいゲームを開始する為色々リセットするフェーズ
	Poker* parent; //このクラスの実体を持つPokerへの参照

public:
	NewGameReset(Poker& set) :parent(&set) {}
	void Update();

};
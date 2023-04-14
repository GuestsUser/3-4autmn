#pragma once
#include "Component.h"
#include "PK_Player.h"

#include <deque>

class PK_Player::Main :public Component {
	PK_Player* parent; //自身を保持する親
	int count;
public:
	Main(PK_Player& parent) :parent(&parent), count(0) {}

	void Update();

	void FullReset() { Reset(); }
	void Reset() { count = 0; }
};
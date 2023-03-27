#pragma once
#include "Component.h"
#include "PK_Player.h"

#include <deque>

class PK_Player::Main :public Component {
	PK_Player* parent; //©g‚ğ•Û‚·‚ée
	int count;
public:
	Main(PK_Player& parent) :parent(&parent), count(0) {}

	void Update();
};
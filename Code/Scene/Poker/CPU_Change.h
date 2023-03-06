#pragma once
#include "../Code/Component/Component.h"
#include "CPU.h"
#include "CardDealer.h"

#include <deque>

class Button;
class Vector3;

class CPU::Change :public Component {
	CPU* parent; //自身を保持する親
	CardDealer::CardPower border; //役になってない中で一番強いカードがこの強以上ならそれは保持する

	int count;
public:
	Change(CPU& parent) :parent(&parent), count(0), border(CardDealer::CardPower::jack) {}

	void Update();
};
#pragma once
#include "Component.h"
#include "PK_CardDealer.h"
#include "PK_CPU.h"

#include <deque>

class Button;
class Vector3;

class PK_CPU::PK_Change :public Component {
	PK_CPU* parent; //自身を保持する親
	PK_CardDealer::CardPower border; //役になってない中で一番強いカードがこの強以上ならそれは保持する

	int count;
public:
	PK_Change(PK_CPU& parent) :parent(&parent), count(0), border(PK_CardDealer::CardPower::jack) {}

	void Update();
};
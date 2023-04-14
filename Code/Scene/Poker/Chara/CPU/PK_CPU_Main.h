#pragma once
#include "Component.h"
#include "PK_CPU.h"

class PK_CPU::Main : public Component {
	PK_CPU* parent; //自身を保持する親オブジェクト
	int count;
public:
	Main(PK_CPU& parent) :parent(&parent), count(0) {}
	void Update();

	void FullReset() { Reset(); }
	void Reset() { count = 0; }
};
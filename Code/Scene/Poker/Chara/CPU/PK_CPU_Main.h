#pragma once
#include "Component.h"
#include "PK_CPU.h"

class PK_CPU::PK_Main : public Component {
	PK_CPU* parent; //自身を保持する親オブジェクト
	int count;
public:
	PK_Main(PK_CPU& parent) :parent(&parent), count(0) {}
	void Update();
};
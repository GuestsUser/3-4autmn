#pragma once
#include "../Code/Component/Component.h"
#include "CPU.h"

class CPU::Main : public Component {
	CPU* parent; //自身を保持する親オブジェクト
	int count;
public:
	Main(CPU& parent) :parent(&parent), count(0) {}
	void Update();
};
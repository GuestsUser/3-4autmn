#pragma once
#include "../Code/Component/Component.h"
#include "CPU.h"

class CPU::Main : public Component {
	CPU* parent; //���g��ێ�����e�I�u�W�F�N�g
	int count;
public:
	Main(CPU& parent) :parent(&parent), count(0) {}
	void Update();
};
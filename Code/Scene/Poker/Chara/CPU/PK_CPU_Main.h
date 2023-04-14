#pragma once
#include "Component.h"
#include "PK_CPU.h"

class PK_CPU::Main : public Component {
	PK_CPU* parent; //���g��ێ�����e�I�u�W�F�N�g
	int count;
public:
	Main(PK_CPU& parent) :parent(&parent), count(0) {}
	void Update();

	void FullReset() { Reset(); }
	void Reset() { count = 0; }
};
#pragma once
#include "Component.h"
#include "PK_CPU.h"

class PK_CPU::PK_Main : public Component {
	PK_CPU* parent; //���g��ێ�����e�I�u�W�F�N�g
	int count;
public:
	PK_Main(PK_CPU& parent) :parent(&parent), count(0) {}
	void Update();
};
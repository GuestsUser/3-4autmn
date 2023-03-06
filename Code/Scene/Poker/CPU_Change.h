#pragma once
#include "../Code/Component/Component.h"
#include "CPU.h"
#include "CardDealer.h"

#include <deque>

class Button;
class Vector3;

class CPU::Change :public Component {
	CPU* parent; //���g��ێ�����e
	CardDealer::CardPower border; //���ɂȂ��ĂȂ����ň�ԋ����J�[�h�����̋��ȏ�Ȃ炻��͕ێ�����

	int count;
public:
	Change(CPU& parent) :parent(&parent), count(0), border(CardDealer::CardPower::jack) {}

	void Update();
};
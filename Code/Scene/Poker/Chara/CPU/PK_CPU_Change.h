#pragma once
#include "Component.h"
#include "Cmp_Hand.h"
#include "PK_CPU.h"

#include <deque>

class Button;
class Vector3;

class PK_CPU::PK_Change :public Component {
	PK_CPU* parent; //���g��ێ�����e
	Cmp_Hand::CardPower border; //���ɂȂ��ĂȂ����ň�ԋ����J�[�h�����̋��ȏ�Ȃ炻��͕ێ�����

	int count;
public:
	PK_Change(PK_CPU& parent) :parent(&parent), count(0), border(Cmp_Hand::CardPower::jack) {}

	void Update();
};
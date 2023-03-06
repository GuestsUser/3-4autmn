#pragma once
#include "Chara.h"
#include <deque>

class Component;
class Cmp_BetActionRecord;
class Cmp_CPUBetLogic;
class PK_Dealer;
class CardDealer;
class Pot;


class CPU :public Chara {
	static int waitTime;

	std::deque<Component*> sectionModule; //�e�Z�N�V������ێ�
	Component* runSection; //SectionUpdate�Ŏg�p����I�u�W�F�N�g�͂�����Ɉڂ�

	Cmp_BetActionRecord* record;
	Cmp_CPUBetLogic* betData;

	Pot* pot;
	PK_Dealer* dealer;
	CardDealer* cardDealer;
public:
	CPU(int sub, Pot& pot, PK_Dealer& dealer, CardDealer& cardDealer);
	~CPU();

	void SectionUpdate();
	void SetSection(Section set) { runSection = sectionModule[(int)set]; }

private:
	class Main;
	class Change;
	class DataPlace; //�����͂�z�u�p�N���X�AsectionModule�Ɏg�p����R���|�[�l���g�ł͂Ȃ�
};



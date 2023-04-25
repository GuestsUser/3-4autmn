#pragma once
#include "PK_Chara.h"
#include <deque>

class Component;
class Cmp_BetActionRecord;
class Cmp_CPUBetLogic;
class Cmp_PK_Chara_SE;
class PK_Dealer;
class PK_CardDealer;
class PK_Pot;


class PK_CPU :public PK_Chara {
	static int waitTime;

	std::deque<Component*> sectionModule; //�e�Z�N�V������ێ�
	Component* runSection; //SectionUpdate�Ŏg�p����I�u�W�F�N�g�͂�����Ɉڂ�

	Cmp_BetActionRecord* record; //�Q�[�����ł̃A�N�V�����L�^
	Cmp_CPUBetLogic* betData; //cpu�̃x�b�g���f�Ɏg�����Z�߃R���|�[�l���g
	Cmp_PK_Chara_SE* se; ////�L�����N�^�[��se�ێ��R���|�[�l���g

	PK_Pot* pot;
	PK_Dealer* dealer;
	PK_CardDealer* cardDealer;
public:
	PK_CPU(int sub, PK_Pot& pot, PK_Dealer& dealer, PK_CardDealer& cardDealer);
	~PK_CPU();

	void FullReset();
	void Reset();

	void SectionUpdate();
	void SetSection(Section set) { runSection = sectionModule[(int)set]; }

private:
	class Main;
	class Change;
	class DataPlace; //�����͂�z�u�p�N���X�AsectionModule�Ɏg�p����R���|�[�l���g�ł͂Ȃ�
};



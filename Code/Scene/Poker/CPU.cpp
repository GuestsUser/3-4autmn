#include "CPU.h"
#include "CPU_Main.h"
#include "CPU_Change.h"
#include "CPU_DataPlace.h"

#include "Pot.h"
#include "Chara.h"
#include "PK_Dealer.h"
#include "CardDealer.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"

#include <deque>

int CPU::waitTime = 30;

CPU::CPU(int sub, Pot& pot, PK_Dealer& dealer, CardDealer& cardDealer) :pot(&pot), dealer(&dealer), cardDealer(&cardDealer), sectionModule(0) {
	betData = new Cmp_CPUBetLogic(dealer);
	record = new Cmp_BetActionRecord();
	EditAppendCmp()->SetCmp(betData); //cpu�̃x�b�g�ɕK�v�ȃf�[�^��Z�߂�BetLogic�𓱓�
	EditAppendCmp()->SetCmp(record); //�A�N�V�����̏�Ԃ��L�^����ActionRecord�𓱓�

	DataPlace::Run(*this, sub); //�z�u�̎��s�A�l�����\���p�R���|�[�l���g�͂�����ō쐬���Ă���

	sectionModule.push_back(new CPU::Main(*this));
	sectionModule.push_back(new CPU::Change(*this));

	runSection = sectionModule[(int)Section::main]; //main����X�^�[�g
}

CPU::~CPU() {
	for (auto itr : sectionModule) { delete itr; } //�e�Z�N�V�������폜
}

void CPU::SectionUpdate() {
	if (!runSection->GetRunUpdate()) { return; } //�Z�N�V���������s�֎~�Ȃ���s���Ȃ�
	runSection->Update(); //�w��Z�N�V������Update�����s
}



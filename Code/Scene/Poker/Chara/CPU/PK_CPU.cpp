#include "PK_CPU.h"
#include "PK_CPU_Main.h"
#include "PK_CPU_Change.h"
#include "PK_CPU_DataPlace.h"
#include "PK_Chara_Wait.h"

#include "PK_Pot.h"
#include "PK_Chara.h"
#include "PK_Dealer.h"
#include "PK_CardDealer.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"

#include <deque>

int PK_CPU::waitTime = 30;

PK_CPU::PK_CPU(int sub, PK_Pot& pot, PK_Dealer& dealer, PK_CardDealer& cardDealer) :pot(&pot), dealer(&dealer), cardDealer(&cardDealer), sectionModule(0) {
	betData = new Cmp_CPUBetLogic(dealer);
	record = new Cmp_BetActionRecord();
	EditAppendCmp()->SetCmp(betData); //cpu�̃x�b�g�ɕK�v�ȃf�[�^��Z�߂�BetLogic�𓱓�
	EditAppendCmp()->SetCmp(record); //�A�N�V�����̏�Ԃ��L�^����ActionRecord�𓱓�

	DataPlace::Run(*this, sub); //�z�u�̎��s�A�l�����\���p�R���|�[�l���g�͂�����ō쐬���Ă���

	sectionModule.push_back(new PK_CPU::Main(*this)); //section�Z��
	sectionModule.push_back(new PK_CPU::Change(*this));
	sectionModule.push_back(new PK_Chara_Wait());

	SetSection(Section::wait); //��芸�������s�͎~�߂Ă���
}

PK_CPU::~PK_CPU() {
	for (auto itr : sectionModule) { delete itr; } //�e�Z�N�V�������폜
}

void PK_CPU::SectionUpdate() {
	if (!runSection->GetRunUpdate()) { return; } //�Z�N�V���������s�֎~�Ȃ���s���Ȃ�
	runSection->Update(); //�w��Z�N�V������Update�����s
}

void PK_CPU::FullReset() {
	SetSection(Section::wait); //��芸����sectionUpdate�͎~�߂Ă���

	PK_Chara::FullReset(); //Chara��FullReset�����s
	for (auto itr : sectionModule) { itr->FullReset(); } //�e�Z�N�V������FullReset���s
}
void PK_CPU::Reset() {
	SetSection(Section::wait); //��芸����sectionUpdate�͎~�߂Ă���

	PK_Chara::Reset(); //Chara��Reset�����s
	for (auto itr : sectionModule) { itr->Reset(); } //�e�Z�N�V������Reset���s
}


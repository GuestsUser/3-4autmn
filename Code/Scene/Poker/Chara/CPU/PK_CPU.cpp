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
	EditAppendCmp()->SetCmp(betData); //cpuのベットに必要なデータを纏めたBetLogicを導入
	EditAppendCmp()->SetCmp(record); //アクションの状態を記録するActionRecordを導入

	DataPlace::Run(*this, sub); //配置の実行、考え中表示用コンポーネントはこちらで作成している

	sectionModule.push_back(new PK_CPU::Main(*this)); //section纏め
	sectionModule.push_back(new PK_CPU::Change(*this));
	sectionModule.push_back(new PK_Chara_Wait());

	SetSection(Section::wait); //取り敢えず実行は止めておく
}

PK_CPU::~PK_CPU() {
	for (auto itr : sectionModule) { delete itr; } //各セクションを削除
}

void PK_CPU::SectionUpdate() {
	if (!runSection->GetRunUpdate()) { return; } //セクションが実行禁止なら実行しない
	runSection->Update(); //指定セクションのUpdateを実行
}

void PK_CPU::FullReset() {
	SetSection(Section::wait); //取り敢えずsectionUpdateは止めておく

	PK_Chara::FullReset(); //CharaのFullResetを実行
	for (auto itr : sectionModule) { itr->FullReset(); } //各セクションのFullReset実行
}
void PK_CPU::Reset() {
	SetSection(Section::wait); //取り敢えずsectionUpdateは止めておく

	PK_Chara::Reset(); //CharaのResetを実行
	for (auto itr : sectionModule) { itr->Reset(); } //各セクションのReset実行
}


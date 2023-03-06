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
	EditAppendCmp()->SetCmp(betData); //cpuのベットに必要なデータを纏めたBetLogicを導入
	EditAppendCmp()->SetCmp(record); //アクションの状態を記録するActionRecordを導入

	DataPlace::Run(*this, sub); //配置の実行、考え中表示用コンポーネントはこちらで作成している

	sectionModule.push_back(new CPU::Main(*this));
	sectionModule.push_back(new CPU::Change(*this));

	runSection = sectionModule[(int)Section::main]; //mainからスタート
}

CPU::~CPU() {
	for (auto itr : sectionModule) { delete itr; } //各セクションを削除
}

void CPU::SectionUpdate() {
	if (!runSection->GetRunUpdate()) { return; } //セクションが実行禁止なら実行しない
	runSection->Update(); //指定セクションのUpdateを実行
}



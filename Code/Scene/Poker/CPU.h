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

	std::deque<Component*> sectionModule; //各セクションを保持
	Component* runSection; //SectionUpdateで使用するオブジェクトはこちらに移す

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
	class DataPlace; //こちはら配置用クラス、sectionModuleに使用するコンポーネントではない
};



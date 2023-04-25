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

	std::deque<Component*> sectionModule; //各セクションを保持
	Component* runSection; //SectionUpdateで使用するオブジェクトはこちらに移す

	Cmp_BetActionRecord* record; //ゲーム内でのアクション記録
	Cmp_CPUBetLogic* betData; //cpuのベット判断に使う情報纏めコンポーネント
	Cmp_PK_Chara_SE* se; ////キャラクターのse保持コンポーネント

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
	class DataPlace; //こちはら配置用クラス、sectionModuleに使用するコンポーネントではない
};



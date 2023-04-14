#pragma once
#include "Component.h"
#include "ComponentArray.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_Hand.h"
#include <deque>

#include <typeinfo>

class Cmp_Image;
class Cmp_Transform;
class PK_Card;

class PK_Chara :public Component {
public:
	enum class BBView { BB, SB, hide }; //BB、SBである事を示す表示をどう表示するかの為の列挙型、hideは非表示、BB,SBはそう表示する

private:
	static int coinIni; //初期所持金記録用変数
	int coin;
	std::deque<Cmp_Image*> coinBack;
	Cmp_Hand hand;
	BBView bbView;

	ComponentArray cmp; //追加機能集
public:
	enum class Section { main, change, wait }; //sectionModuleから目的のセクションを指定する為の列挙型

	PK_Chara();
	virtual ~PK_Chara();
	virtual void FullReset();
	virtual void Reset();

	void Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos);
	void Update();
	void Draw();

	virtual void SectionUpdate() = 0; //ゲームの各セクションから呼び出すUpdate、セクションに応じて適切な処理を実行してくれる
	virtual void SetSection(Section set) = 0; //使用Section指定用関数

	int GetCoint() const { return coin; }
	void SetCoin(int set) { coin = set; }

	const Cmp_Hand* ReadHand() const { return &hand; } //手札を読み取り専用で返す
	Cmp_Hand* EditHand() { return &hand; } //手札を操作可能な状態で返す

	BBView GetBBView() const { return bbView; } //BB表示の状態を得る
	void SetBBView(BBView set); //BB表示状態を設定する

	const ComponentArray* const ReadAppendCmp() { return &cmp; } //追加機能集へのアクセス、こちらは読み出し専用
	ComponentArray* EditAppendCmp() { return &cmp; } //追加機能集へのアクセスを渡す

};
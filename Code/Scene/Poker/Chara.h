#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Component/ComponentArray.h"
#include <deque>

#include <typeinfo>

class Cmp_Image;
class Cmp_Transform;
class PK_Card;

class Chara :public Component {
public:
	enum class BBView { BB, SB, hide }; //BB、SBである事を示す表示をどう表示するかの為の列挙型、hideは非表示、BB,SBはそう表示する

private:
	static int coinIni; //初期所持金記録用変数
	int coin;
	std::deque<PK_Card*> card;
	std::deque<Cmp_Image*> coinBack;
	BBView bbView;

	ComponentArray cmp; //追加機能集
public:
	Chara();
	virtual ~Chara();
	void FullReset();
	void Reset();

	void Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos);
	void Update();
	void Draw();

	int GetCoint() const { return coin; }
	const std::deque<PK_Card*>* ReadCard() const { return &card; }
	void GetHandNum(std::deque<int>& set) const; //ハンドを数値化した物を取得、set配列内に格納して返す

	void SetCoin(int set) { coin = set; }
	std::deque<PK_Card*>* EditCard() { return &card; }

	BBView GetBBView() const { return bbView; } //BB表示の状態を得る
	void SetBBView(BBView set); //BB表示状態を設定する

	ComponentArray* EditAppendCmp() { return &cmp; } //追加機能集へのアクセスを渡す
	const ComponentArray* const ReadAppendCmp() { return &cmp; } //追加機能集へのアクセス、こちらは読み出し専用
};
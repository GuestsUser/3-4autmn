#pragma once
#include "../Code/Component/Component.h"
#include <deque>

#include <typeinfo>

class Cmp_Image;
class Cmp_Transform;
class PK_Card;

class Chara :public Component {
	static int coinIni; //初期所持金記録用変数
	int coin;
	std::deque<PK_Card*> card;
	std::deque<Cmp_Image*> coinBack;
	std::deque<Component*> cmp;

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

	void SetCmp(Component* set) { cmp.push_back(set); } //追加機能の追加
	void EraseCmp(Component* set); //指定追加機能削除
	void ClearCmp(); //追加機能全削除

	std::deque<Component*>* EditCmpFull() { return &cmp; } //コンポーネント全てを取得、各コンポーネントの中身を気にしない場合こちらを使用

	template<class T> T* EditCmp() { //コンポーネント取得
		const type_info& master = typeid(T); //取得するコンポーネントの型を入れておく
		for (Component* get : cmp) {
			if (typeid(*get) == master) { return dynamic_cast<T*>(get); }
		}
		return nullptr;
	}

	template<class T> void EditCmpMulti(std::deque<T*>& setArray) { //コンポーネント取得、同じクラスのコンポーネントが複数ある場合それら全てを返すタイプ、setArrayに検索結果を入れて返す
		const type_info& master = typeid(T); //取得するコンポーネントの型を入れておく
		for (Component* get : cmp) {
			if (typeid(*get) == master) { setArray.push_back(dynamic_cast<T*>(get)); }
		}
	}

	template<class T> T* ReadCmp() const { //コンポーネント取得、取得したコンポーネントは書き換え不能の読み出し専用形式
		const type_info& master = typeid(T); //取得するコンポーネントの型を入れておく
		for (Component* get : cmp) {
			if (typeid(*get) == master) { return dynamic_cast<T*>(get); }
		}
		return nullptr;
	}
};
#pragma once

#include "Component.h"
#include <deque>

class ComponentArray: public Component { //コンポーネントを追加機能という形で複数持てる機能
	std::deque<Component*> cmp;

public:
	ComponentArray() :cmp(std::deque<Component*>()) {}
	virtual ~ComponentArray() { ClearCmp(); }

	void Reset(); //追加機能のResetを呼び出す
	void FullReset(); //追加機能のFullResetを呼び出す
	void Update(); //追加機能のUpdateを実行、このコンポーネント自身が実行禁止状態なら追加機能のUpdateも実行しない
	void Draw(); //追加機能のDrawを実行、Update同様実行禁止なら追加機能の方も実行しない

	void SetRunUpdateBundle(bool set); //追加機能のisUpdate一括指定
	void SetRunDrawBundle(bool set); //追加機能のisDraw一括指定

	void SetCmp(Component* set) { cmp.push_back(set); } //追加機能の追加
	void EraseCmp(Component* set); //指定追加機能削除
	void ClearCmp(); //追加機能全削除

	std::deque<Component*>* EditCmpFull() { return &cmp; } //コンポーネント全てを取得、各コンポーネントの中身を気にしない場合こちらを使用
	const std::deque<Component*>* ReadCmpFull() const { return &cmp; } //コンポーネント全てを取得、こちらは読み出し専用


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
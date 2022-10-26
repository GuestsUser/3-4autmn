#include "../Code/GetKey.h"
#include "Button.h"
#include "../Code/Component/Component.h"

#include <deque>


void Button::Update() {
	if (!GetRunUpdate()) { return; } //実行の許可が出てない場合終わり
	for (auto itr : always) { itr->Update(); }
	for (auto itr : click) { itr->Update(); }


}

void Button::Draw() {
	if (!GetRunUpdate()) { return; } //実行の許可が出てない場合終わり
	for (auto itr : always) { itr->Draw(); }
	for (auto itr : click) { itr->Draw(); }


}

Button::~Button() {
	ClearAlways();
	ClearClick();
}

void Button::SetAlways(Component* cmp) {
	for (Component* get : always) {
		if (get == cmp) { return; } //指定コンポーネントが追加済みだった場合追加せず終了
	}
	always.push_back(cmp); //ここまで来れればcmpは新しいコンポーネントなので後ろに追加
}

void Button::EraseAlways(Component* cmp) {
	for (Component* get : always) {
		if (get == cmp) { 
			//always.erase(get);
			delete get;
		}
	}
}

void Button::EraseAlways(Component* cmp) {
	for (auto itr = always.begin(); itr != always.end(); ++itr) { //イテレーターで取得したかったのでfor eachではなくforを使う
		if (cmp == *itr) { //イテレーターとコンポーネントが一致した場合
			delete cmp; //削除
			always.erase(itr); //配列から除外
			return; //配列を削ってしまったのでイテレーターが無効になったから終わり
		}
	}

}


void Button::ClearAlways() {
	for (Component* get : always) { delete get; } //格納されてたコンポーネントの削除
	always.clear(); //配列要素の全消去
}

void Button::EraseClick(Component* cmp) {
	for (auto itr = click.begin(); itr != click.end(); ++itr) { //イテレーターで取得したかったのでfor eachではなくforを使う
		if (cmp == *itr) { //イテレーターとコンポーネントが一致した場合
			delete cmp; //削除
			click.erase(itr); //配列から除外
			return; //配列を削ってしまったのでイテレーターが無効になったから終わり
		}
	}

}

void Button::ClearClick() {
	for (Component* get : click) { delete get; } //格納されてたコンポーネントの削除
	click.clear(); //配列の要素を全削除
}




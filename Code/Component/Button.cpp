#include "../Code/GetKey.h"
#include "../Code/OriginMath.h"
#include "Button.h"
#include "Component.h"
#include "Cmp_Transform.h"


#include <deque>


void Button::Update() {
	if (!GetRunUpdate()) { return; } //実行の許可が出てない場合終わり
	for (auto itr : always) { itr->Update(); } //追加機能のUpdate実行
	for (auto itr : click) { itr->Update(); }

	Vector3 current = pos.ReadPos(); //位置へのアクセスショートカット
	Vector3 rad = area.ReadPos(); //範囲へのアクセスショートカット
	int x = -1; //マウスx
	int y = -1; //マウスy
	GetMousePoint(&x, &y); //マウス位置取得
	bool hit = x > current.GetX() + rad.GetX() && x < current.GetX() - rad.GetX() && y > current.GetY() + rad.GetY() && y < current.GetY() - rad.GetY(); //範囲内にカーソルがある場合true

	switch (state) {
	case Button::State::free: //平常時処理
		if (hit && GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //カーソルが範囲内にある状態で押した瞬間を検知
			float shrink = 0.7; //クリックした際の縮小表示の為の拡大倍率

			area.EditScale() = pos.ReadScale(); //現在の拡大状況をareaに保存する
			pos.EditScale() *= shrink; //現在サイズに縮小倍率を掛けて縮小サイズを出す
			state = State::push; //stateを押し状態へ移行する
		}
		
		break;

	case Button::State::push: //押している間の処理
		if (GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PULL) { //離した瞬間を検知
			pos.EditScale() = area.ReadScale(); //拡大率を元の物に戻す
			state = State::free; //stateを平常へ移行する

			if (hit) { //範囲内にカーソルがあった状態で離した場合clickの処理を実行すべく、各種実行可否をtrueにする
				for (auto itr : click) { 
					itr->SetRunUpdate(true); 
					itr->SetRunDraw(true);
					itr->Update(); //この後Drawが実行されるのでUpdateも実行しておく
				}
			}
		}


		break;
	}

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




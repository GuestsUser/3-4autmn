#include "Button.h"

#include "Component.h"
#include "ComponentArray.h"
#include "Cmp_Transform.h"

#include "../Code/GetKey.h"
#include "../Code/OriginMath.h"

#include <deque>

void AppendArrayStateReset(ComponentArray& always, ComponentArray& click) { //alwaysとclickの実行系を初期の物に直す
	always.SetRunUpdate(true); //常に実行できるようtrue
	always.SetRunDraw(true);

	click.SetRunUpdate(false); //クリックした瞬間実行開始するようfalse
	click.SetRunDraw(false);
}

void ButtonStateReset(Button& button) { //buttonのUpdate等実行状態をリセット
	button.SetRunUpdate(true);
	button.SetRunDraw(true);
	button.SetRunClickMonitor(true);
}

Button::Button(int setX, int setY, int setAreaX, int setAreaY, bool monitorSet) :pos(Cmp_Transform()), area(Cmp_Transform()), isMonitorClick(monitorSet), state(State::free), always(ComponentArray()), click(ComponentArray()) {
	pos.EditPos().SetXYZ(setX, setY, 0);
	area.EditPos().SetXYZ(setAreaX, setAreaY, 0);
	AppendArrayStateReset(always, click); //clickは最初から実行されないように設定する
}

void Button::Update() {
	if (!GetRunUpdate()) { return; } //実行の許可が出てない場合終わり
	if (isMonitorClick) { //クリック検知処理、Monitorがfalseなら実行しない
		Vector3 current = pos.ReadPos(); //位置へのアクセスショートカット
		Vector3 rad = area.ReadPos(); //範囲へのアクセスショートカット
		int x = -1; //マウスx
		int y = -1; //マウスy
		GetMousePoint(&x, &y); //マウス位置取得
		bool hit = x < current.GetX() + rad.GetX() && x > current.GetX() - rad.GetX() && y < current.GetY() + rad.GetY() && y > current.GetY() - rad.GetY(); //範囲内にカーソルがある場合true

		switch (state) {
		case Button::State::free: //平常時処理
			if (hit && key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //カーソルが範囲内にある状態で押した瞬間を検知
				float shrink = 0.7; //クリックした際の縮小表示の為の拡大倍率

				area.EditScale() = pos.ReadScale(); //現在の拡大状況をareaに保存する
				pos.EditScale() *= shrink; //現在サイズに縮小倍率を掛けて縮小サイズを出す
				state = State::push; //stateを押し状態へ移行する
			}
			break;

		case Button::State::push: //押している間の処理
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PULL) { //離した瞬間を検知
				pos.EditScale() = area.ReadScale(); //拡大率を元の物に戻す
				state = State::free; //stateを平常へ移行する

				if (hit) { //範囲内にカーソルがあった状態で離した場合clickの処理を実行すべく、各種実行可否をtrueにする
					click.SetRunUpdate(true);
					click.SetRunDraw(true);
				}
			}
			break;
		}
	}

	always.Update(); //追加機能のUpdate実行
	click.Update();
}

void Button::Draw() {
	if (!GetRunDraw()) { return; } //実行の許可が出てない場合終わり
	always.Draw(); //追加機能のDraw実行
	click.Draw();
}

void Button::Reset() {
	AppendArrayStateReset(always, click); //追加機能の実行可否を元に戻す
	ButtonStateReset(*this); //buttonのクリック検知、実行状態を元に戻す
	always.Reset(); //追加機能のResetを呼び出す
	click.Reset();
}

void Button::FullReset() {
	AppendArrayStateReset(always, click); //追加機能の実行可否を元に戻す
	ButtonStateReset(*this); //buttonのクリック検知、実行状態を元に戻す
	always.FullReset(); //追加機能のFullResetを呼び出す
	click.FullReset();
}

#pragma once
#include "Component.h"
#include "ComponentArray.h"
#include "Cmp_Transform.h"

#include <deque>

//alwaysとclickについて
//alwaysとclickのUpdateはButton::Updateで実行されるがその実行順はalways→clickの順になっている
//clickはクリックを検知した瞬間からUpdate、Drawどちらも実行される

class Button : public Component { //Componentを継承しているが追加機能というより単体生存するタイプなので命名にCmpを付けなかった
	enum class State { free, push }; //free=平常時、push=area範囲内で左ボタンを押した瞬間からarea内外問わず離した瞬間まで	
	State state; //クリック状態を記憶しておくための変数

	Cmp_Transform pos; //ボタン座標、中心座標になる
	Cmp_Transform area; //クリック検知範囲、Posに検知半径を入れる、Scaleはクリックした際縮小する機能を実行した際拡大率を元に戻す為posから値を受け取る事に使用する
	bool isMonitorClick; //trueでクリック検知、falseなら検知しない

	ComponentArray always; //常にUpdate、Drawを実行するコンポーネント
	ComponentArray click; //クリックを検知した瞬間Update、Drawを有効化するコンポーネント
public:
	Button(int setX = 0, int setY = 0, int setAreaX = 0, int setAreaY = 0, bool monitorSet = true);

	void Update();
	void Draw();
	void Reset(); //alwaysの実行系をtrueに、clickをfalseに設定し追加機能のResetを呼び出す
	void FullReset(); //Resetの機能と追加機能のReset呼び出しの代わりFullResetを呼び出すやつ

	void SetRunClickMonitor(bool set) { isMonitorClick = set; } //クリックを検知するかを設定、trueで検知する、falseでしない
	bool GetRunClickMonitor()const { return isMonitorClick; } //クリック検知の実行可否の取得

	bool GetRunUpdateAlways() const { return always.GetRunUpdate(); } //always::Updateが実行可能であればtrueを返す
	bool GetRunUpdateClick() const { return click.GetRunUpdate(); } //click::Updateが実行可能であればtrueを返す
	bool GetRunDrawAlways() const { return always.GetRunDraw(); } //always::Drawが実行可能であればtrueを返す
	bool GetRunDrawClick() const { return click.GetRunDraw(); } //click::Drawが実行可能であればtrueを返す
	
	ComponentArray* EditAlways() { return &always; } //alwaysのコンポーネント集を編集可能な状態で返す
	ComponentArray* EditClick() { return &click; } //clickのコンポーネント集を編集可能な状態で返す
	const ComponentArray* ReadAlways() const { return &always; } //alwaysのコンポーネント集を読み取り専用で返す
	const ComponentArray* ReadClick() const { return &click; } //clickのコンポーネント集を読み取り専用で返す


	Cmp_Transform* EditTransform() { return &pos; } //座標系情報を編集可能な状態で取得
	Vector3* EditArea() { return &(area.EditPos()); } //クリック範囲を編集可能な状態で取得
	const Cmp_Transform* ReadTransform() const { return &pos; } //座標系情報を読み取り専用形式で取得
	const Vector3* ReadArea() const { return &(area.ReadPos()); } //クリック範囲を読み取り専用形式で取得
};
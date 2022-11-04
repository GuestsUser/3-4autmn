#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/OriginMath.h"

#include <deque>



class Button : public Component { //Componentを継承しているが追加機能というより単体生存するタイプなので命名にCmpを付けなかった
	enum class State { free, push }; //free=平常時、push=area範囲内で左ボタンを押した瞬間からarea内外問わず離した瞬間まで	
	State state; //クリック状態を記憶しておくための変数

	Cmp_Transform pos; //ボタン座標、中心座標になる
	Cmp_Transform area; //クリック検知範囲、Posに検知半径を入れる、Scaleはクリックした際縮小する機能を実行した際拡大率を元に戻す為posから値を受け取る事に使用する
	bool isMonitorClick; //trueでクリック検知、falseなら検知しない

	std::deque<Component*> always; //常にUpdate、Drawを実行するコンポーネント
	std::deque<Component*> click; //クリックを検知した瞬間Update、Drawを有効化するコンポーネント
	
public:
	Button(int setX = 0, int setY = 0, int setAreaX = 0, int setAreaY = 0, bool monitorSet = true) :pos(Cmp_Transform()), area(Cmp_Transform()), isMonitorClick(monitorSet), state(State::free), always(std::deque<Component*>()), click(std::deque<Component*>()) {
		pos.EditPos().SetXYZ(setX, setY, 0);
		area.EditPos().SetXYZ(setAreaX, setAreaY, 0);
	}
	~Button();

	void Update();
	void Draw();



	void SetRunClickMonitor(bool set) { isMonitorClick = set; } //クリックを検知するかを設定、trueで検知する、falseでしない
	const bool GetRunClickMonitor()const { return isMonitorClick; } //クリック検知の実行可否の取得


	void SetRunUpdateAlways(bool set); //alwaysのisUpdateを一括設定
	void SetRunDrawAlways(bool set); //alwaysのisDrawを一括設定
	void SetRunUpdateClick(bool set); //clickのisUpdateを一括設定
	void SetRunDrawClick(bool set); //clickのisDrawを一括設定

	const bool GetRunUpdateAlways()const; //alwaysのisUpdateを調査し、1つでもtrueがあったらtrueを返す
	const bool GetRunDrawAlways()const; //alwaysのisDrawを調査し、1つでもtrueがあったらtrueを返す
	const bool GetRunUpdateClick()const; //clickのisUpdateを調査し、1つでもtrueがあったらtrueを返す
	const bool GetRunDrawClick()const; //clickのisDrawを調査し、1つでもtrueがあったらtrueを返す
	



	void SetAlways(Component* cmp) { always.push_back(cmp); } //cmpをalwaysへ追加
	void EraseAlways(Component* cmp); //cmp自体を削除し、alwaysからも除外、alwaysに存在しないコンポーネントを指定した場合削除しない
	void ClearAlways(); //alwaysを空にする、入っていたコンポーネント実体は全て削除される

	void SetClick(Component* cmp) { //cmpをclickへ追加
		click.push_back(cmp); //配列に追加
		cmp->SetRunUpdate(false); //指定コンポーネントのUpdate、Drawはクリックを検知した時、trueにされる
		cmp->SetRunDraw(false);
	}
	void EraseClick(Component* cmp); //cmp自体を削除し、clickからも除外
	void ClearClick(); //clickを空にする、入っていたコンポーネント実体は全て削除される




	const Cmp_Transform* ReadTransform() const { return &pos; } //座標系情報を読み取り専用形式で取得
	Cmp_Transform* EditTransform() { return &pos; } //座標系情報を編集可能な状態で取得
	const Vector3* ReadArea() const { return &(area.ReadPos()); } //クリック範囲を読み取り専用形式で取得
	Vector3* EditArea() { return &(area.EditPos()); } //クリック範囲を編集可能な状態で取得
};
#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/OriginMath.h"

#include <deque>



class Button : public Component { //Componentを継承しているが追加機能というより単体生存するタイプなので命名にCmpを付けなかった
	Cmp_Transform pos; //ボタン座標、中心座標になる
	Cmp_Transform area; //クリック検知範囲、Posに検知半径を入れる
	bool isMonitorClick; //trueでクリック検知、falseなら検知しない

	std::deque<Component*> always; //常にUpdate、Drawを実行するコンポーネント
	std::deque<Component*> click; //クリックを検知した瞬間Update、Drawを有効化するコンポーネント
	
public:
	Button(bool monitorSet = true, int setX = 0, int setY = 0, int setAreaX = 0, int setAreaY = 0) :pos(Cmp_Transform()), area(Cmp_Transform()), isMonitorClick(monitorSet), always(std::deque<Component*>()), click(std::deque<Component*>()) {
		pos.EditPos().SetXYZ(setX, setY, 0);
		area.EditPos().SetXYZ(setAreaX, setAreaY, 0);
	}
	~Button();

	void Update();
	void Draw();




	void SetAlways(Component* cmp) { always.push_back(cmp); } //cmpをalwaysへ追加
	void EraseAlways(Component* cmp); //cmp自体を削除し、alwaysからも除外、alwaysに存在しないコンポーネントを指定した場合削除しない
	void ClearAlways(); //alwaysを空にする、入っていたコンポーネント実体は全て削除される

	void SetClick(Component* cmp) { //cmpをclickへ追加
		always.push_back(cmp); //配列に追加
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
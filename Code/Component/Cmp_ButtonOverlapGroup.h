#pragma once
#include "Component.h"
#include "Button.h"
#include <deque>

class Cmp_ButtonOverlapGroup :public Component { //Buttonのalwaysに設定するとそのButtonが検知範囲内で押された際groupに含まれる他のButtonの入力を検知しないようにする
	bool isGroupDelManage; //trueならgroupはこちらで削除管理を行う、trueであっても中身の削除までは行わない
	std::deque<Button*>* group; //ボタングループ、parentが押された時この中にあるButtonオブジェクトは入力検知しないようになる
	Button* parent; //自身を持つボタン、検知範囲内で押された時groupのisMonitorをfalseにして入力検知しないようにする
	Button::State old; //parentの旧ステータス
	std::deque<bool> monitorStateMemo; //parentが離された時、groupのisMonitorを元に戻す為元のisMonitorを記録する変数

public:
	Cmp_ButtonOverlapGroup(Button& setParent, bool setGroupDelManage = true, std::deque<Button*>* setArray = nullptr);
	~Cmp_ButtonOverlapGroup();
	void Update();

	std::deque<Button*>* EditGroup() { return group; } //ボタングループを編集可能な状態で取得
	Button* EditParent() { return parent; } //自身の親を編集可能な状態で取得

};
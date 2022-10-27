#pragma once
#include "Component.h"

#include <deque>

class Button;

class Cmp_ButtonGroup :public Component { //ボタンをクリックするとグループ化された全ボタンの内押されたボタン以外の動作を停止するButton用追加機能
	std::deque<Button*> group; //ボタングループ、基本的にボタンの集まりはSceneに属してるのでこちらでは削除管理を行わない
	Button* parent; //自身を持つボタン、これのclickが実行される時これ以外のgroup内のボタン全てのUpdateをfalseにする

public:
	Cmp_ButtonGroup(Button& setParent, std::deque<Button*>& setArray) :parent(&setParent), group(setArray) {}

	void Update(); //parentのclickが実行された1回だけ実行する様になっている
};
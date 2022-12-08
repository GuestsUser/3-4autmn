#pragma once
#include "Component.h"
#include "../Code/OriginMath.h"

#include "../Code/GetKey.h"

#include <deque>

class Gage;

class Cmp_Gage_MouseControl :public Component {
	Gage* parent; //これを持つ親ゲージ
	Vector3 area; //マウス接触検知範囲、ゲージ実体画像の中心位置からの半径の形式で保持
	float step; //ゲージの刻み方、マウスポインタが画像サイズ/stepの位置を越える度100/step分volを加算する

	int monitorKey; //このボタンを押した時ゲージ操作を行う
	bool control; //trueの間はゲージ操作を行う、検知範囲内でマウス指定ボタンを押した瞬間から押してる間true、離した瞬間falseになる
public:
	Cmp_Gage_MouseControl(Gage& setParent, const Vector3& setArea, float setStep = 100, int setKey = REQUEST_MOUSE_LEFT);

	void Update();
};
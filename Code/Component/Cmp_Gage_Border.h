#pragma once
#include "Component.h"

class Gage;

class Cmp_Gage_Border :public Component { //ゲージの最後にこれを追加するとゲージの最低値を指定可能になり、操作などでこれを下回っても強制的にこの数値となる
	Gage* parent;
	float border; //ゲージ下限

public:
	Cmp_Gage_Border(Gage& setGage) :parent(&setGage), border(0) {}
	void Update();

	void Reset() { border = 0; }
	void FullReset() { Reset(); }

	void SetBorder(float set) { 
		if (set > 1) { set = 1; } //リミットチェック、オーバーしないよう処理
		if (set < 0) { set = 0; }
		border = set;
	}
	float GetBorder() { return border; }
};
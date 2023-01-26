#pragma once
#include "Component.h"

class Gage;

class Cmp_Gage_Border :public Component { //ゲージの最後にこれを追加するとゲージの最低値を指定可能になり、操作などでこれを下回っても強制的にこの数値となる
	Gage* parent;
	int border; //ゲージ下限

public:
	Cmp_Gage_Border(Gage& setGage) :parent(&setGage), border(0) {}
	void Update();

	void SetBorder(int set) { 
		if (set > 100) { set = 100; } //リミットチェック、オーバーしないよう処理
		if (set < 0) { set = 0; }
		border = set;
	}
	int GetBorder() { return border; }
};
#pragma once
#include "Component.h"

class Gage;

class Cmp_Gage_UpperBorder :public Component { //Borderの上限版、これを最後にセットすると上限が決められる、下限を優先するか上限を優先するかはセット順で決められる
	Gage* parent;
	float border; //ゲージ上限

public:
	Cmp_Gage_UpperBorder(Gage& setGage) :parent(&setGage), border(1) {}
	void Update();

	void Reset() { border = 1; }
	void FullReset() { Reset(); }

	void SetBorder(float set) { 
		if (set > 1) { set = 1; } //リミットチェック、オーバーしないよう処理
		if (set < 0) { set = 0; }
		border = set;
	}
	float GetBorder() { return border; }
};
#pragma once
#include "Component.h"

class PK_Chara_Wait :public Component { //何もしない、Pokerにはpre等キャラを動かしたくないセクションがある、キャラのセクションをこいつにする事でsectionUpdateを疑似的に止められる
public:
	PK_Chara_Wait() {}
	void Update() {}
};
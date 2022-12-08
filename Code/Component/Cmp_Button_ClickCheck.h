#pragma once
#include "Component.h"

class Cmp_Button_ClickCheck :public Component { //Buttonのclick内コンポーネントはクリックされた瞬間runUpdateがtrueになるのでこれを付ければ外部からクリックされたか検知できる空コンポーネント

public:
	Cmp_Button_ClickCheck() {}
	void Update() {}
};
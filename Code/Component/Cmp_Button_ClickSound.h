#pragma once
#include "Component.h"

class Cmp_Sound;

class Cmp_Button_ClickSound :public Component { //buttonのclickに格納するとクリックされた瞬間にsoundを鳴らすButton用追加機能
	Cmp_Sound* sound; //鳴らすサウンド

public:
	Cmp_Button_ClickSound(Cmp_Sound& sound) :sound(&sound) {} //newされたサウンドを受け取る、削除管理はこちらで行う
	~Cmp_Button_ClickSound() { delete sound; }

	void Update(); //clickが実行可能になった際一度だけサウンドを鳴らすUpdate
	void FullReset() { Reset(); } //resetと同様
	void Reset() { SetRunUpdate(true); } //再びサウンドを鳴らせる様Update実行をtrueにしておく
};
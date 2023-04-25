#pragma once
#include "Component.h"

class Cmp_Sound;

class Cmp_Button_ClickSound :public Component { //button��click�Ɋi�[����ƃN���b�N���ꂽ�u�Ԃ�sound��炷Button�p�ǉ��@�\
	Cmp_Sound* sound; //�炷�T�E���h

public:
	Cmp_Button_ClickSound(Cmp_Sound& sound) :sound(&sound) {} //new���ꂽ�T�E���h���󂯎��A�폜�Ǘ��͂�����ōs��
	~Cmp_Button_ClickSound() { delete sound; }

	void Update(); //click�����s�\�ɂȂ����ۈ�x�����T�E���h��炷Update
	void FullReset() { Reset(); } //reset�Ɠ��l
	void Reset() { SetRunUpdate(true); } //�ĂуT�E���h��点��lUpdate���s��true�ɂ��Ă���
};
#pragma once
#include "Component.h"

class Gage;

class Cmp_Gage_UpperBorder :public Component { //Border�̏���ŁA������Ō�ɃZ�b�g����Ə�������߂���A������D�悷�邩�����D�悷�邩�̓Z�b�g���Ō��߂���
	Gage* parent;
	float border; //�Q�[�W���

public:
	Cmp_Gage_UpperBorder(Gage& setGage) :parent(&setGage), border(1) {}
	void Update();

	void Reset() { border = 1; }
	void FullReset() { Reset(); }

	void SetBorder(float set) { 
		if (set > 1) { set = 1; } //���~�b�g�`�F�b�N�A�I�[�o�[���Ȃ��悤����
		if (set < 0) { set = 0; }
		border = set;
	}
	float GetBorder() { return border; }
};
#pragma once
#include "Component.h"

class Gage;

class Cmp_Gage_Border :public Component { //�Q�[�W�̍Ō�ɂ����ǉ�����ƃQ�[�W�̍Œ�l���w��\�ɂȂ�A����Ȃǂł����������Ă������I�ɂ��̐��l�ƂȂ�
	Gage* parent;
	int border; //�Q�[�W����

public:
	Cmp_Gage_Border(Gage& setGage) :parent(&setGage), border(0) {}
	void Update();

	void SetBorder(int set) { 
		if (set > 100) { set = 100; } //���~�b�g�`�F�b�N�A�I�[�o�[���Ȃ��悤����
		if (set < 0) { set = 0; }
		border = set;
	}
	int GetBorder() { return border; }
};
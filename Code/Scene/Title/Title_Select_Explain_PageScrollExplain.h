#pragma once
#include "Component.h"
#include "OriginMath.h"

#include <string>



class Title_Select_Explain_PageScrollExplain :public Component { //�y�[�W�X�N���[�����\�ł��鎖��\������ׂ̒ǉ��@�\
	std::string str; //�\�����b�Z�[�W
	Vector3 pos; //�\���ʒu
	Vector3 iniColor; //���b�Z�[�W�̏����F
	Vector3 finalColor; //���b�Z�[�W�̍ŏI�F

	int count; //���Ԍo�ߋL�^
	int limit; //���b�Z�[�W��iniColor��finalColor��iniColor��1���[�v����܂ł̎��ԁA�t���[���P�ʎw��
public:
	Title_Select_Explain_PageScrollExplain();

	void Update(); //count���o�߂�����
	void Draw(); //���b�Z�[�W�`�ʂ��s��

	void FullReset() { Reset(); }
	void Reset(); //���Ԃ̊J�n�ʒu�������_��������
};
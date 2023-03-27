#pragma once
#include "Cmp_Transform.h"
#include <deque>

class Cmp_Image;

class PK_Btn { //�{�^���摜�ƃ{�^���̈ʒu��ۗL�����N���X
	Cmp_Image* img; //�{�^���摜
	std::deque<Cmp_Transform> posList; //�{�^����\������ʒu�W�A���̔z��̕��т̓L�����z��ƑΉ����Ă���
	int usePos; //posList���̂ǂ̈ʒu��\���Ɏg�������肷��Y�����ϐ��A���̐��l���{�^���|�W�V�����Ƃ������ɂȂ�

public:
	PK_Btn();
	~PK_Btn();
	void Reset(); //�V�������E���h�J�n���ɌĂяo���A�|�W�V�����ʒu�̍X�V���s��
	void FullReset(); //�Q�[�����S���������s���������Ăяo���A�{�^�������ʒu�������_�����肵���肷��

	int GetBtnPos() const { return usePos; } //�{�^�����݈ʒu��Y�����Ŏ擾�A�擾�����Y�����̓L�������i�[����z��Ɏg���΂��̃L�������Ăяo����
	void SetBtnPos(int set) { //�{�^���ʒu��V�����ݒ�A�L�������𒴂���l�����Ă��͈͓��ɏC�����Ă����
		usePos = set - 1; //Reset��usePos��+1����̂�set�𐳂����Z�b�g�����-1���Ă���
		Reset(); //���Z�b�g�ɂ��{�^���\���ʒu�̍X�V������
	}

	void Draw();
};
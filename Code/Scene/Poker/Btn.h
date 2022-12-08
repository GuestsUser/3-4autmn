#pragma once
#include "../Code/Component/Cmp_Transform.h"
#include <deque>

class Cmp_Image;

class Btn { //�{�^���摜�ƃ{�^���̈ʒu��ۗL�����N���X
	Cmp_Image* img; //�{�^���摜
	std::deque<Cmp_Transform> posList; //�{�^����\������ʒu�W�A���̔z��̕��т̓L�����z��ƑΉ����Ă���
	int usePos; //posList���̂ǂ̈ʒu��\���Ɏg�������肷��Y�����ϐ��A���̐��l���{�^���|�W�V�����Ƃ������ɂȂ�

public:
	Btn();
	~Btn();
	void Reset(); //�V�������E���h�J�n���ɌĂяo���A�|�W�V�����ʒu�̍X�V���s��
	void FullReset(); //�Q�[�����S���������s���������Ăяo���A�{�^�������ʒu�������_�����肵���肷��

	int GetBtnPos() { return usePos; } //�{�^�����݈ʒu��Y�����Ŏ擾�A�擾�����Y�����̓L�������i�[����z��Ɏg���΂��̃L�������Ăяo����
	void SetBtnPos(int set) { usePos = set % posList.size(); } //�{�^���ʒu��V�����ݒ�A�L�������𒴂���l�����Ă��͈͓��ɏC�����Ă����

	void Draw();
};
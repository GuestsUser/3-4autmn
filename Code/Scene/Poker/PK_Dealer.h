#pragma once
#include "Btn.h"


class PK_Dealer { //�|�[�J�[�Ɋւ���F�X�ȃf�[�^���Ǘ�����f�B�[���[�ȃN���X
	Btn btn; //�{�^���|�W�V����

	int baseBB; //����BB�A���E���h��1�������BB�͂��̐��l���㏸����
	int maxBet; //����BB����ő剽�{�܂Ŋ|�����邩���������l
	int currentMaxBet; //���݂̍ő�x�b�g��BB�̉��{���i�[����

	int BB; //����BB
	int gameCount; //���݂̃��E���h��
	int playSub; //���݃A�N�V�������s���L�����̓Y�������L�^

public:
	PK_Dealer();
	void Draw(); //�{�^���|�W�V������`�ʂ���

	void Reset(); //�V�������E���h�J�n���ɌĂяo��
	void FullReset(); //�Q�[�����ăX�^�[�g����ׂ̊��S������

	int GetBB() const { return BB; } //����BB���擾
	int GetMaxBet() const { return maxBet; } //maxBet���擾
	int GetCurrentMaxBet() const { return currentMaxBet; } //���ݍő�x�b�g���擾
	int GetGameCount() const { return gameCount; } //���݂̃Q�[���񐔂��擾
	int GetActionCharaSub() const { return playSub; } //����A�N�V����������L�����̓Y�������擾

	const Btn* ReadBtn() const { return &btn; } //�{�^���|�W�V������ǂݎ���p�`���Ŏ擾

	void SetCurrentMaxBet(int set) { currentMaxBet = set; } //�ő�x�b�g���X�V����
	void SetActionChara(int set); //���A�N�V�������s���L������ݒ肷��
};
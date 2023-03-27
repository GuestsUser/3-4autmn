#include "DxLib.h"

#include "Component.h"
#include "BetLogicInitializeData.h"
#include "Cmp_CPUBetLogic.h"

#include "PK_CardDealer.h"
#include "PK_Card.h"
#include "PK_Chara.h"
#include "PK_Dealer.h"

#include <deque>

/*
(T�̃n�C�J�[�h)�`(8�̃����y�A)�ȉ� 0
(2�̃����y�A)�`(Q�̃����y�A)���� 1 +(3)�`(8)
(6�̃����y�A)�`(2�̃c�[�y�A)���� 3 +(3)�`(7)
(Q�̃����y�A)�`(6�̃c�[�y�A)���� 5 +(1)�`(3)
(5�̃c�[�y�A)�`(T�̃c�[�y�A)���� 7 +(0)�`(2)
(T�̃c�[�y�A)�`(4�̃X���[�J�[�h)�ȏ� 10 +(0)�`(1)
�X�g���[�g�A�t���b�V���̊����҂� (3)�`(10)
*/


Cmp_CPUBetLogic::Cmp_CPUBetLogic(PK_Dealer& setDealer) :changeTimingLimit(4), changeTiming(1), oldGameCount(0), raiseActive(false), dealer(&setDealer), borderBase(std::deque<int>()), border(std::deque<int>()), payLimit(std::deque<int>()), raiseSplit(std::deque<int>()) {
	//�萔�f�[�^�̏�����

	BorderBaseIni(borderBase);
	RaiseBorderBaseIni(raiseBorderBase);
	PayLimitiIni(payLimit);

	int size = borderBase.size() / 2; //�{�[�_�[�n�̊m�ۗv�f��
	border.resize(size); //�w��v�f���̈�m��
	raiseBorder.resize(size);
}

void Cmp_CPUBetLogic::Reset() {
	raiseSplit.resize(0); //�������C�Y����������
	raiseActive = false;
	int gameCount = dealer->GetGameCount(); //���݃Q�[���񐔂��擾

	if ((gameCount - oldGameCount) % changeTiming == 0) { //�X�V�^�C�~���O�������ꍇ�X�V����
		oldGameCount = gameCount; //����̃Q�[���J�E���g���L�^
		changeTiming = GetRand(changeTimingLimit - 1) + 1; //���̍X�V�^�C�~���O������A0�ɂȂ��Ă��܂�Ȃ��l��+1����

		for (int i = 0; i < border.size(); ++i) {
			int sub = (int)i * 2; //����̍Œ�{�[�_�[�փA�N�Z�X����Y����
			int low = borderBase[sub]; //�Œ�l
			if (i >= 1 && low < border[i - 1]) { low = border[i - 1] + 1; } //�O�̗v�f�̃{�[�_�[������̍Œ�l�������Ă���ꍇ�傫�������̗p�A�O��̒l�ƂԂ���Ȃ��悤��+1���Ă���
			border[i] = GetRand(borderBase[sub + 1] - low) + low; //�{�[�_�[�ݒ�

			raiseBorder[i] = GetRand(raiseBorderBase[sub + 1] - raiseBorderBase[sub]) + raiseBorderBase[sub]; //���C�Y�{�[�_�[�ݒ�
		}
	}
}

void Cmp_CPUBetLogic::RaiseVolDecision(const PK_Chara& chara, bool isCheckReach) {
	std::deque<int> handRank; //��D�𐔒l�����������i�[
	chara.GetHandNum(handRank); //�L���������D�z����擾
	
	int rank = 0; //��̋�����border���̉����ɂ��邩���������������N
	int vol = 0; //���C�Y�\�񐔋L�^

	for (rank = 0; rank < border.size(); ++rank) { //��̋������烌�C�Y�\�񐔂�����o��
		vol = GetRand(payLimit[rank * 2 + 1] - payLimit[rank * 2]) + payLimit[rank * 2]; //����̃��C�Y�\��
		if (handRank[0] < border[rank]) { break; } //��̋���������̃{�[�_�[�ɒB���Ă��Ȃ���ΏI���
	}
	if (rank >= border.size()) { rank = border.size() - 1; } //��̋������{�[�_�[�̏���𒴂��Ă����ꍇ�����ɔ[�߂�

	raiseActive = handRank[0] >= GetRand(borderBase[rank * 2 + 1] - borderBase[rank * 2]) + borderBase[rank * 2] + raiseBorder[rank]; //���������N���̃{�[�_�[�x�[�X�ƃ��C�Y�x�[�X���烉���_�����l�����o����2�����Z�����l�ȏ�̎�̋����Ȃ玩�僌�C�Y���s��

	if (isCheckReach && PK_CardDealer::ReachCheck(chara) != 1) { //���[�`�`�F�b�N
		vol = GetRand(payLimit[payLimit.size() - 1] - payLimit[payLimit.size() - 2]) + payLimit[payLimit.size() - 2]; //���[�`���|�����Ă���΂�����Ƀ��C�Y������킹��
		rank = border.size() + 1; //�g�p�����N�����[�`�p�̕��ɕύX
		raiseActive = round((double)GetRand(10) / 10.0); //���[�`�̏ꍇ���僌�C�Y�̓����_�����肷��
	}
	if (!raiseActive) { //���僌�C�Y���Ȃ��ꍇ
		raiseSplit.push_back(vol); //�����͂����S��split[0]�Ɋi�[
		return; //�I���
	}

	while (vol > 0) { //���C�Y�\��𕪊�����
		raiseSplit.push_back(GetRand(vol - 1) + 1); //����̃��C�Y��
		vol -= raiseSplit[raiseSplit.size() - 1]; //����̉񐔂͎g�p�ς݂Ƃ��ă��C�Y�\�񐔂��猸�Z
	}
}

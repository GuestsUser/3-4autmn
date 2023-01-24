#pragma once
#include "../Code/Component/Component.h"
#include "Cmp_BetActionRecord.h"
#include <deque>

class Chara;
class PK_Dealer;

class Cmp_CPUBetLogic :public Component {
	std::deque<int> borderBase; //���C�Y��̌��f�[�^�A�����_���͈͂̌`���Ŋi�[����Ă���A��X�V�̍ۂ��̐��l�������_���͈͂Ƃ��ă����_�����肳���
	std::deque<int> raiseBorderBase; //���僌�C�Y���s����̋����̊
	std::deque<int> border; //���C�Y��A��̋������i�[����Ă���A��̋����ȉ��̗v�f��payLimit���g�p����
	std::deque<int> raiseBorder; //���僌�C�Y���s����̋����Aborder�ɂ��̐��l�����Z�����l�𒴂��Ă���Ύ��僌�C�Y���s��

	std::deque<int> payLimit; //���C�Y��ɑΉ��������C�Y�\��
	std::deque<int> raiseSplit; //���C�Y���s���ہA���̔z��̗v�f�����������C�Y�𕪊����čs���A�z��̒��g�̒l�����C�Y����
	bool raiseActive; //true�Ŏ��僌�C�Y���s��

	int changeTiming; //��X�V�^�C�~���O�A�Q�[�����s�񐔂����̐��l�̗]��0�ɂȂ������X�V
	int changeTimingLimit; //��L��^�C�~���O�̃����_�����ő�l 
	int oldGameCount; //����X�V�����Q�[���J�E���g���L�^����

	PK_Dealer* dealer; //�f�B�[���[�̎Q�Ƃ�����
public:
	Cmp_CPUBetLogic(PK_Dealer& setDealer);
	void Reset(); //���E���h�J�n���ɌĂяo���ƃ��C�Y�������ƃ��E���h�񐔂ɉ����Ċ�̃��Z�b�g�����Ă����
	void FullReset() { Reset(); } //Reset�Ə������e�͓���
	void Update() {}

	void RaiseVolDecision(const Chara& chara, bool isCheckReach); //�n���h�̕]�����ʂ������ɗ^���鎖�ł���ɉ��������C�Y�\�񐔂����肷��֐��Abool��true������ƃ��[�`�`�F�b�N�������������ʂƂȂ�

	const std::deque<int>* ReadRaiseSplit() const { return &raiseSplit; } //�������C�Y�����L�^�����z���ǂݎ���p�ŕԂ�
	bool GetSelfRaise() { return raiseActive; } //���僌�C�Y���邩�ۂ���Ԃ�
};
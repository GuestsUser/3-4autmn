#pragma once
#include "Component.h"

class Gage;
class Cmp_Sound;

class Cmp_Gage_ControlSound :public Component { //�Q�[�W�ʂ��ω�������sound��炷Gage�����ǉ��@�\
	Gage* parent; //���̃R���|�[�l���g�����e
	const Cmp_Sound* const sound; //�炷�T�E���h
	float oldVol; //�O�t���[���̃Q�[�W��

	bool isSoundStop; //true�̊Ԃ�Update�͎��s���邪�T�E���h�͖炳�Ȃ�
	bool isSelfSoundDel; //true�Ȃ�sound�̍폜�Ǘ��͂�����ōs��

public:
	Cmp_Gage_ControlSound(Gage* parent, const Cmp_Sound* const sound, bool isSelfSoundDel) :parent(parent), sound(sound), oldVol(0), isSoundStop(true), isSelfSoundDel(isSelfSoundDel) {}
	~Cmp_Gage_ControlSound();

	void FullReset() { Reset(); }
	void Reset();

	void Update();
	void SetSoundStop(bool set) { isSoundStop = set; } //�Q�[�W����ɂ�鉹�炵���s�����ǂ����ݒ�
};
#include "Cmp_Gage_ControlSound.h"

#include "Cmp_Sound.h"
#include "Gage.h"


Cmp_Gage_ControlSound::~Cmp_Gage_ControlSound() {
	if (isSelfSoundDel) { delete sound; } //�폜�Ǘ����s���w�߂��o�Ă���΂�����ō폜����
}

void Cmp_Gage_ControlSound::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~��ԂȂ�I���

	float vol = parent->GetVol(); //���݃Q�[�W�擾
	if (vol == oldVol) { return; } //�Q�[�W����Ȃ���ΏI���

	oldVol = vol; //�O��l���X�V
	if (isSoundStop) { return; } //���炵��~���߂��o�Ă���ΏI���

	sound->Play(); //�T�E���h��炷
}

void Cmp_Gage_ControlSound::Reset() { 
	oldVol = parent->GetVol(); //�O��l�����݃Q�[�W�ɋ����I�ɍ��킹��
	isSoundStop = true; //�T�E���h�͖�Ȃ���Ԃɐݒ�
}

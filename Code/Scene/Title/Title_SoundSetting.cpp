#include "DxLib.h"
#include "Title_SoundSetting.h"

#include "Cmp_Sound.h"

void Title_SoundSetting::SetUpTitleSelectBGM(Cmp_Sound& sound) {
	ChangeVolumeSoundMem(255 * 0.5, sound.GetHandle()); //���ʐݒ�
	sound.SetPlayType(DX_PLAYTYPE_LOOP); //�Đ��^�C�v�����[�v�ɕύX
}

void Title_SoundSetting::SetUpTitleClick(Cmp_Sound& sound) {
	ChangeVolumeSoundMem(255 * 0.7, sound.GetHandle()); //���ʐݒ�
}

void Title_SoundSetting::SetUpExplainScroll(Cmp_Sound& sound) {
	ChangeVolumeSoundMem(255 * 0.6, sound.GetHandle()); //���ʐݒ�
}

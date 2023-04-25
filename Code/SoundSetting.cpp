#include "DxLib.h"

#include "SoundSetting.h"
#include "Cmp_Sound.h"
#include "Cmp_Transform.h"

Cmp_Sound* SoundSetting::CreateDefaultButtonClickSound(Cmp_Transform* ts) {
	Cmp_Sound* sound = new Cmp_Sound(LoadSoundMem("Resource/se/buttonPush.wav"), -1, -1, true, ts); //�{�^���N���b�N��������se�쐬
	ChangeVolumeSoundMem(255 * 0.85, sound->GetHandle()); //���ʐݒ�
	return sound; //�쐬����se��Ԃ�
}



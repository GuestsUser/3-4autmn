#pragma once

class Cmp_Sound;
class Cmp_Transform;

class SoundSetting {
public:
	static Cmp_Sound* CreateDefaultButtonClickSound(Cmp_Transform* ts = nullptr); //�{�^���N���b�N���ꂽ���̉����쐬���ĕԂ�

private:
	//���̐����֎~
	SoundSetting() = delete;
	SoundSetting(const SoundSetting&) = delete;

};
#pragma once

class Cmp_Sound;

class Title_SoundSetting {
public:
	static void SetUpTitleSelectBGM(Cmp_Sound& sound); //sound�ɓ����ꂽ�T�E���h�Ƀ^�C�g����bgm�����X�e�[�^�X��ݒ肷��
	static void SetUpTitleClick(Cmp_Sound& sound); //sound�ɓ����ꂽ�T�E���h�Ƀ^�C�g����ʂ̃N���b�N�����X�e�[�^�X��ݒ肷��


private:
	//���̐����֎~
	Title_SoundSetting() = delete;
	Title_SoundSetting(const Title_SoundSetting&) = delete;
};

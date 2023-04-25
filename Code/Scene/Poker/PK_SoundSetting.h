#pragma once
class Cmp_Sound;

class PK_SoundSetting {
public:
	static void SetUpCardPlace(Cmp_Sound& sound); //�J�[�h�z�z���Ƃ��ăX�e�[�^�X��ݒ�
	static void SetUpFold(Cmp_Sound& sound); //fold�������̉��Ƃ��ăX�e�[�^�X��ݒ�
	static void SetUpCall(Cmp_Sound& sound); //call�������̉��Ƃ��ăX�e�[�^�X��ݒ�
	static void SetUpRaise(Cmp_Sound& sound); //raise�������̉��Ƃ��ăX�e�[�^�X��ݒ�
	static void SetupCardChange(Cmp_Sound& sound); //�J�[�h�����������̉��Ƃ��ăX�e�[�^�X��ݒ�
	static void SetupHandOpen(Cmp_Sound& sound); //��D���J�������̉��Ƃ��ăX�e�[�^�X��ݒ�
	static void SetUpCoinMany(Cmp_Sound& sound); //sound�ɓ����ꂽ�T�E���h�ɃR�C������(���)se�����X�e�[�^�X��ݒ肷��
	static void SetUpCoinFew(Cmp_Sound& sound); //sound�ɓ����ꂽ�T�E���h�ɃR�C������(����)se�����X�e�[�^�X��ݒ肷��
private:
	//���̐����֎~
	PK_SoundSetting() = delete;
	PK_SoundSetting(const PK_SoundSetting&) = delete;

};
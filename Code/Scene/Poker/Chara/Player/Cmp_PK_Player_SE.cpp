#include "DxLib.h"
#include "Cmp_PK_Player_SE.h"

#include "Cmp_Sound.h"

Cmp_PK_Player_SE::Cmp_PK_Player_SE(const Cmp_Transform* const soundPos) :soundPos(Cmp_Transform()) {
	if (soundPos != nullptr) { this->soundPos = *soundPos; } //�ʒu�����󂯎���Ă����ꍇ���̏����R�s�[����

	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/coinPlayer.wav"), -1, -1, true, &this->soundPos)); //se�𓱓�����
	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/gageControl.wav"), -1, -1, true, &this->soundPos));

	ChangeVolumeSoundMem(255 * 1, sound[0]->GetHandle()); //���ʐݒ�
	ChangeVolumeSoundMem(255 * 0.9, sound[1]->GetHandle()); //���ʐݒ�
}
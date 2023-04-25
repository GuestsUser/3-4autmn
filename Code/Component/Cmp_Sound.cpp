#include "DxLib.h"

#include "Component.h"
#include "Cmp_Sound.h"
#include "Cmp_Transform.h"

#include "ConstVal.h"

#include <cmath>

Cmp_Sound::Cmp_Sound(const int& handle, int rad, int playType, int topPositionFlag, Cmp_Transform* ts) :handle(handle), rad(rad), ts(ts), playType(playType), topPositionFlag(topPositionFlag), isSelfTs(true) {
	if (ts == nullptr) { this->ts = new Cmp_Transform(); } //ts�ɉ��������ĂȂ���ΐV���ɍ쐬����
	else { isSelfTs = false; } //�O������n���ꂽ�ꍇ�폜�Ǘ��͂�����ōs��Ȃ�
	if (this->rad == -1) { this->rad = std::sqrt(std::pow(WINDOW_X, 2) + std::pow(WINDOW_Y, 2)); } //rad�̏����l�ݒ�A��ʑS�̂𔼌a�ɐݒ�
	if (this->playType == -1) { this->playType = DX_PLAYTYPE_BACK; } //playType�̏����l�ݒ�Aplay���������̏I����҂��Ȃ�
	SetRad(this->rad); //���a���𔽉f����
}

Cmp_Sound::~Cmp_Sound() {
	if (isSelfTs) { delete ts; } //������ŊǗ����鎖�ɂȂ��Ă��ꍇ�폜
	DeleteSoundMem(handle); //�ǂݍ��񂾃T�E���h�̊J��
}

void Cmp_Sound::Play()const {
	Set3DPositionSoundMem(VGet(ts->ReadPos().GetX(), ts->ReadPos().GetY(), ts->ReadPos().GetZ()), handle); //3d��ԏ�ɃT�E���h��ݒ�
	PlaySoundMem(handle, playType, topPositionFlag); //�T�E���h�炵
}

void Cmp_Sound::Stop()const { StopSoundMem(handle); }

void Cmp_Sound::SetRad(float set) { 
	rad = set; //���a�ݒ�
	Set3DRadiusSoundMem(rad, handle); //�ݒ�𔽉f
}
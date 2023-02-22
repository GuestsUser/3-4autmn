#pragma once
#include "Component.h"
#include "Cmp_Transform.h"
#include "../Code/Component/ComponentArray.h"

#include <deque>
#include <typeinfo>

class Cmp_Image;

class Gage :public Component {
	Cmp_Image* base; //�Q�[�W�̃x�[�X�A��̃Q�[�W�摜
	Cmp_Image* full; //�Q�[�W�̎��̕\���p�摜

	float vol; //�Q�[�W�̌��ݗ�
	float iniSize; //�Q�[�W���̉摜�̏���x�g�嗦�A����ɑ΂�vol���|���Č��݃Q�[�W�L�k�����߂鎖�ŃQ�[�W�̍ő�l��L�΂��������̍ہA�\�߉摜���g�債��full�ɓn�����ŃQ�[�W�ő�T�C�Y���摜����蒼�����Đݒ�ł���

	ComponentArray cmp; //�ǉ��@�\
public:
	Gage(Cmp_Image& baseImgae, Cmp_Image& fullImage, int iniVol = 1);
	~Gage();

	void Reset();
	void FullReset();

	void Update();
	void Draw();

	float GetVol() const { return vol; }
	void SetVol(float set) { //�l��ݒ�
		if (set > 1) { set = 1; } //���~�b�g�`�F�b�N�A�}�C�i�X�A�Ⴕ����1�𒴂��Ȃ��悤�ɂ���
		if (set < 0) { set = 0; }
		vol = set;
	}

	const Cmp_Image* ReadBaseGage() const { return base; } //��Q�[�W�̉摜�I�u�W�F�N�g���擾�A�ǂݎ���p
	const Cmp_Image* ReadFullGage() const { return full; } //�Q�[�W���̂̉摜�I�u�W�F�N�g���擾�A�ǂݎ���p

	float GetIniSize() { return iniSize; } //����x�g�嗦���擾

	ComponentArray* EditAppendCmp() { return &cmp; } //�ǉ��@�\�W�ւ̃A�N�Z�X��n��
	const ComponentArray* const ReadAppendCmp() { return &cmp; } //�ǉ��@�\�W�ւ̃A�N�Z�X�A������͓ǂݏo����p
};
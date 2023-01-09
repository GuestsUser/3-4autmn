#pragma once
#include "Component.h"
#include "Cmp_Transform.h"

#include <deque>
#include <typeinfo>

class Cmp_Image;

class Gage :public Component {
	Cmp_Image* base; //�Q�[�W�̃x�[�X�A��̃Q�[�W�摜
	Cmp_Image* full; //�Q�[�W�̎��̕\���p�摜

	int vol; //�Q�[�W�̌��ݗʁA�������ɃQ�[�W��\������A100���ő�A0�ŏ��̕\���A�����_�͏�肭�ێ��ł��Ȃ��\�����������̂ł��̌`���̗p
	float iniSize; //�Q�[�W���̉摜�̏���x�g�嗦�A����ɑ΂�vol���|���Č��݃Q�[�W�L�k�����߂鎖�ŃQ�[�W�̍ő�l��L�΂��������̍ہA�\�߉摜���g�債��full�ɓn�����ŃQ�[�W�ő�T�C�Y���摜����蒼�����Đݒ�ł���

	std::deque<Component*> cmp; //�ǉ��@�\
public:
	Gage(Cmp_Image& baseImgae, Cmp_Image& fullImage, int iniVol = 100);
	~Gage();

	void Reset();
	void FullReset();

	void Update();
	void Draw();

	float GetVol() const { return vol * 0.01; } //�p�[�Z���e�[�W�`���ɒ����ĕԂ�
	void SetVol(float set) { //�l��ݒ�A�p�[�Z���e�[�W�Ŏ󂯎��̂�*100�Ő����ɒ���
		if (set > 1) { set = 1; } //���~�b�g�`�F�b�N�A�}�C�i�X�A�Ⴕ����100�𒴂��Ȃ��悤�ɂ���
		if (set < 0) { set = 0; }
		vol = set * 100;
	}

	const Cmp_Image* ReadBaseGage() const { return base; } //��Q�[�W�̉摜�I�u�W�F�N�g���擾�A�ǂݎ���p
	const Cmp_Image* ReadFullGage() const { return full; } //�Q�[�W���̂̉摜�I�u�W�F�N�g���擾�A�ǂݎ���p

	float GetIniSize() { return iniSize; } //����x�g�嗦���擾

	void SetCmp(Component* set) { cmp.push_back(set); } //�ǉ��@�\�̒ǉ�

	template<class T> T* EditCmp() const { //�R���|�[�l���g�擾
		const type_info& master = typeid(T); //�擾����R���|�[�l���g�̌^�����Ă���
		for (Component* get : cmp) {
			if (typeid(*get) == master) { return dynamic_cast<T*>(get); }
		}
		return nullptr;
	}
};
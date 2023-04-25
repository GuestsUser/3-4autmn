#pragma once
#include "Component.h"

class Cmp_Transform;

class Cmp_Sound :public Component { //�T�E���h��ێ�����R���|�[�l���g�APlay�����s����ƃT�E���h���Đ�����
	Cmp_Transform* ts;
	bool isSelfTs; //Transform�R���|�[�l���g���R���X�g���N�^�ŏȂ����ꍇ�����true�ɂ���Transform�̍폜���͂�����ōs��

	int handle; //�T�E���h�n���h��
	int playType; //PlaySoundMem�ɓn��PlayType�ɑ�������
	int topPositionFlag; //PlaySoundMem�ɓn��TopPositionFlag�ɑ�������

	float rad; //���̕������锼�a
public:
	Cmp_Sound(const int& handle, int rad = -1, int playType = -1, int topPositionFlag = true, Cmp_Transform* ts = nullptr); //rad,playtype�ɐݒ肳��Ă鏉���l-1�͂��̂܂܂Ȃ�R���X�g���N�^�ŕʂ̒l�ɒu��������A�ݒ肵���������l���o���ב����̃w�b�_�[�C���N���[�h��]�V�Ȃ����ꂽ�̂̑[�u
	~Cmp_Sound();

	void Update() {}
	void Play()const; //�T�E���h�Đ�
	void Stop()const; //�T�E���h��~�AStopSoundMem�ł�����Play������̂œ���ׂ̈ɗp��

	const Cmp_Transform* const ReadTranform() const { return ts; } //�ǂݎ���p�`����Transform���擾
	Cmp_Transform* EditTranform() { return ts; } //���������\�Ȍ`����Transform���擾

	void SetPlayType(int set) { playType = set; }
	void SetTopPositionFlag(int set) { topPositionFlag = set; }
	void SetRad(float set);

	int GetHandle()const { return handle; }
};
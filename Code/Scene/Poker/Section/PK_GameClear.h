#pragma once
#include "Scene.h"
#include "Poker.h"

#include "Component.h"
#include "Button.h"
#include "OriginMath.h"

class Cmp_Sound;

class Poker::GameClear :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	Button nextButton; //�N���b�N���鎖�Ŏ��V�[���ֈڍs����

	int count;
	int clickStartTime; //count�����̐��l�ɒB����ƃ{�^���N���b�N�̌��m���J�n����
	int blink; //���̎��ԊԊu�Ő�����_�ł�����

	Vector3 titlePos; //�Q�[���N���A�ł��鎖���������b�Z�[�W�̕\���ʒu
	Vector3 explainPos; //�{�^�������̔z�u�ʒu

	Cmp_Sound* sound; //�Q�[���I�[�o�[�ł��鎖��\���悤�ȃT�E���h
public:
	GameClear(Poker& set);
	~GameClear() { delete sound; }
	void Update();
	void Draw();

	void FullReset() { Reset(); } //Reset�Ɠ��l
	void Reset(); //��ʃN���b�N���m�p�{�^���Ǝ��Ԍo�ߋL�^�p�J�E���g�̃��Z�b�g
};

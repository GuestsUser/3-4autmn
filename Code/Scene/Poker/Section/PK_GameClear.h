#pragma once
#include "Scene.h"
#include "Poker.h"

#include "Component.h"
#include "Button.h"
#include "OriginMath.h"

class Poker::GameClear :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	Button nextButton; //�N���b�N���鎖�Ŏ��V�[���ֈڍs����

	int count;
	int clickStartTime; //count�����̐��l�ɒB����ƃ{�^���N���b�N�̌��m���J�n����
	int blink; //���̎��ԊԊu�Ő�����_�ł�����

	Vector3 titlePos; //�Q�[���N���A�ł��鎖���������b�Z�[�W�̕\���ʒu
	Vector3 explainPos; //�{�^�������̔z�u�ʒu

public:
	GameClear(Poker& set);
	void Update();
	void Draw();

	void FullReset() { Reset(); } //Reset�Ɠ��l
	void Reset(); //��ʃN���b�N���m�p�{�^���Ǝ��Ԍo�ߋL�^�p�J�E���g�̃��Z�b�g
};

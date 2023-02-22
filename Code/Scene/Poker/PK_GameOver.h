#pragma once
#include "../Scene.h"
#include "Poker.h"

#include "../Code/Component/Component.h"
#include "../Code/Component/Button.h"

class Vector3;

class Poker::GameOver :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	Button nextButton; //�N���b�N���鎖�Ŏ��V�[���ֈڍs����

	int count;
	int clickStartTime; //count�����̐��l�ɒB����ƃ{�^���N���b�N�̌��m���J�n����
	int blink; //���̎��ԊԊu�Ő�����_�ł�����

	Vector3 titlePos; //�Q�[���I�[�o�[�ł��鎖���������b�Z�[�W�̕\���ʒu
	Vector3 explainPos; //�{�^�������̔z�u�ʒu
public:
	GameOver(Poker& set);
	void Update();
	void Draw();
};
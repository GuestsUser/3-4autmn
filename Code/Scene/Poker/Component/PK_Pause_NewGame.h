#pragma once
#include "Component.h"
#include "Cmp_PK_Pause.h"

class Button;

class Cmp_PK_Pause::NewGame :public Component { //Pause���̍ŏ�����{�^����click�ɕt����Poker�����S���Z�b�g����@�\
	Cmp_PK_Pause* parent;
	Button* parentButton;

	int count; //���̋@�\�����{�^�����N���b�N����Ă���̎��Ԍo�ߋL�^
	int runTime; //�L�^���Ԃ����̎��Ԃ𒴂�����Q�[�������Z�b�g����@�\�̎��s���s��
public:
	NewGame(Cmp_PK_Pause& parent, Button& parentButton) :parent(&parent), parentButton(&parentButton), count(0), runTime(30) {}

	void Update();

	void FullReset() { Reset(); }
	void Reset() { count = 0; }
};
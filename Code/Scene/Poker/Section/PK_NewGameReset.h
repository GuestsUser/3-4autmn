#pragma once
#include "Poker.h"
#include "Scene.h"

class Poker::NewGameReset :public Scene { //�V�����Q�[�����J�n����אF�X���Z�b�g����t�F�[�Y
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��

public:
	NewGameReset(Poker& set) :parent(&set) {}
	void Update();

};
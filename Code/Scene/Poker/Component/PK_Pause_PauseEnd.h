#pragma once
#include "Component.h"
#include "Cmp_PK_Pause.h"

class Button;

class Cmp_PK_Pause::PauseEnd :public Component { //Pause���̃Q�[�����s�{�^����click�ɕt����|�[�Y��ʂ��I����Poker�֖߂�@�\
	Cmp_PK_Pause* parent;
	Button* parentButton;

public:
	PauseEnd(Cmp_PK_Pause& parent, Button& parentButton) :parent(&parent), parentButton(&parentButton) {}

	void Update();

	static void Close(Cmp_PK_Pause& pause); //�|�[�Y��ʂ����@�\�����s
};
#include "Cmp_SelectSelector.h"
#include "../Code/Scene/Scene.h"
#include "../Code/Component/Button.h"

#include <deque>

void Cmp_SelectSelector::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~��ԂȂ�I��
	if (count == limit) { //���s�^�C�~���O�ɂȂ�������s�V�[����ύX
		if (run != nullptr) { *gameRef = run; } //run�ɉ��������Ă����gameRef�ֈڂ��ւ�
		else { *gameRef = sceneCreator(); } //run����Ȃ�sceneCreator�ŐV�����V�[�����쐬
	}
	++count;
}


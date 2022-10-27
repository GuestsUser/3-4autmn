#pragma once
#include "Component.h"

#include <deque>

class Button;

class Cmp_ButtonGroup :public Component { //�{�^�����N���b�N����ƃO���[�v�����ꂽ�S�{�^���̓������ꂽ�{�^���ȊO�̓�����~����Button�p�ǉ��@�\
	std::deque<Button*> group; //�{�^���O���[�v�A��{�I�Ƀ{�^���̏W�܂��Scene�ɑ����Ă�̂ł�����ł͍폜�Ǘ����s��Ȃ�
	Button* parent; //���g�����{�^���A�����click�����s����鎞����ȊO��group���̃{�^���S�Ă�Update��false�ɂ���

public:
	Cmp_ButtonGroup(Button& setParent, std::deque<Button*>& setArray) :parent(&setParent), group(setArray) {}

	void Update(); //parent��click�����s���ꂽ1�񂾂����s����l�ɂȂ��Ă���
};
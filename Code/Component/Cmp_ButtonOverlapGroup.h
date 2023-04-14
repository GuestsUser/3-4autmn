#pragma once
#include "Component.h"
#include "Button.h"
#include <deque>

class Cmp_ButtonOverlapGroup :public Component { //Button��always�ɐݒ肷��Ƃ���Button�����m�͈͓��ŉ����ꂽ��group�Ɋ܂܂�鑼��Button�̓��͂����m���Ȃ��悤�ɂ���
	bool isGroupDelManage; //true�Ȃ�group�͂�����ō폜�Ǘ����s���Atrue�ł����Ă����g�̍폜�܂ł͍s��Ȃ�
	std::deque<Button*>* group; //�{�^���O���[�v�Aparent�������ꂽ�����̒��ɂ���Button�I�u�W�F�N�g�͓��͌��m���Ȃ��悤�ɂȂ�
	Button* parent; //���g�����{�^���A���m�͈͓��ŉ����ꂽ��group��isMonitor��false�ɂ��ē��͌��m���Ȃ��悤�ɂ���
	Button::State old; //parent�̋��X�e�[�^�X
	std::deque<bool> monitorStateMemo; //parent�������ꂽ���Agroup��isMonitor�����ɖ߂��׌���isMonitor���L�^����ϐ�

public:
	Cmp_ButtonOverlapGroup(Button& setParent, bool setGroupDelManage = true, std::deque<Button*>* setArray = nullptr);
	~Cmp_ButtonOverlapGroup();
	void Update();

	std::deque<Button*>* EditGroup() { return group; } //�{�^���O���[�v��ҏW�\�ȏ�ԂŎ擾
	Button* EditParent() { return parent; } //���g�̐e��ҏW�\�ȏ�ԂŎ擾

};
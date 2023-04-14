#include "Component.h"
#include "Button.h"
#include "Cmp_ButtonOverlapGroup.h"

#include <deque>

Cmp_ButtonOverlapGroup::Cmp_ButtonOverlapGroup(Button& setParent, bool setGroupDelManage, std::deque<Button*>* setArray) :parent(&setParent), group(setArray), isGroupDelManage(setGroupDelManage) {
	old = parent->GetPushState(); //�͈͓��N���b�N��Ԃ̏�����

	if (group == nullptr) { group = new std::deque<Button*>(); } //group���󂾂����ꍇ�V�K�쐬
	for (auto itr : *group) { monitorStateMemo.push_back(itr->GetRunClickMonitor()); } //group��Button�̃N���b�N���m��ԋL�^�ϐ��̏���
}

Cmp_ButtonOverlapGroup::~Cmp_ButtonOverlapGroup() {
	if (isGroupDelManage) { delete group; } //group�̍폜��������Ώ����Ă���
}

void Cmp_ButtonOverlapGroup::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~��ԂȂ�I��
	if (old == parent->GetPushState()) { return; } //�O��ƃN���b�N��Ԃ������̏ꍇ�������Ȃ�

	old = parent->GetPushState(); //old������̕��ɑ�����
	if (group->size() != monitorStateMemo.size()) { monitorStateMemo.resize(group->size()); } //group�̊i�[����monitor�L���ϐ��̃T�C�Y�����킹��

	if (old == Button::State::free) { //����free�ɂ���Ă����ꍇ
		for (int i = 0; i < group->size(); ++i) { (*group)[i]->SetRunClickMonitor(monitorStateMemo[i]); } //group��button�̃N���b�N���m����ۂ����ɖ߂�
	}
	else { //push�ɂ���Ă����ꍇ
		for (int i = 0; i < group->size(); ++i) {
			monitorStateMemo[i] = (*group)[i]->GetRunClickMonitor(); //���݂̃N���b�N���m����ۂ�ۑ�����
			(*group)[i]->SetRunClickMonitor(false); //�N���b�N���m�����Ȃ��悤�ݒ�
		}
	}
}
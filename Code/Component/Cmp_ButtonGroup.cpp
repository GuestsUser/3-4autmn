#include "Component.h"
#include "Button.h"
#include "Cmp_ButtonGroup.h"

#include <deque>

void Cmp_ButtonGroup::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~��ԂȂ�I��
	for (auto itr : group) { itr->SetRunUpdate(false); } //�S�ă{�^����update��؂�
	parent->SetRunUpdate(true); //�e�̃{�^����update��L��������
	parent->SetRunClickMonitor(false); //�e�̃{�^���̃N���b�N�����m���Ȃ��悤�ɂ���

	SetRunUpdate(false); //���g�̎��s��؂�
}
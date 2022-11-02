#include "Cmp_SelectSelector.h"
#include "../Code/Scene/Scene.h"
#include "../Code/Component/Button.h"

#include <deque>

void Cmp_SelectSelector::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~��ԂȂ�I��
	if (count == limit) { *gameRef = run; } //���s�^�C�~���O�ɂȂ�����w��V�[���֎��s�V�[����ύX
	if (count > limit) { //�������Z���N�g��ʂɖ߂��Ă������̏���
		for (auto itr : group) {
			itr->SetRunUpdateClick(false); //�e�{�^���͔�N���b�N��Ԃɖ߂�
			itr->SetRunUpdate(true); //�{�^���̍X�V���ĊJ����
			itr->SetRunClickMonitor(true); //�N���b�N���m��L����
		}
		count = 0; //�ė��p�ł���悤count��0�ɖ߂�
		return;
	}
	++count;
}

#include "Component.h"
#include "Button.h"
#include "Cmp_ButtonGroup.h"

#include <deque>

void Cmp_ButtonGroup::Update() {
	for (auto itr : group) {
		if (itr != parent) { itr->SetRunUpdate(false); } //���g������Button�ȊO��group���S�Ă�Button��Update��؂�
	}
	SetRunUpdate(false); //���g�̎��s��؂�
	SetRunDraw(false); //Draw�͎g���ĂȂ����O�̈�
}
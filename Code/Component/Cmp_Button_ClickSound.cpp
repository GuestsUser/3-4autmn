#include "Cmp_Button_ClickSound.h"
#include "Cmp_Sound.h"

void Cmp_Button_ClickSound::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~��ԂȂ�I���

	sound->Play(); //�T�E���h��炷
	SetRunUpdate(false); //���s��؂�
}
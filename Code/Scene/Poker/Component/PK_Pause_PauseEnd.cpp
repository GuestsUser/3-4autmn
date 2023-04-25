#include "Poker.h"

#include "Cmp_PK_Pause.h"
#include "PK_BGM.h"
#include "PK_Pause_PauseEnd.h"

#include "Button.h"
#include "ComponentArray.h"

void Cmp_PK_Pause::PauseEnd::Update() {
	parent->CloseOrder(); //�|�[�Y��ʏI�����w������
	parent->poker->ControlBGM()->Resume(); //bgm�ĊJ
}

void Cmp_PK_Pause::PauseEnd::Close(Cmp_PK_Pause& pause) {
	pause.parent->SetRunClickMonitor(true); //PK_Pause�����{�^���̃N���b�N���m�ĊJ

	pause.parent->SetRunUpdateClick(false); //PK_Pause�����{�^���̃N���b�N�n������~����
	pause.parent->SetRunDrawClick(false);
}
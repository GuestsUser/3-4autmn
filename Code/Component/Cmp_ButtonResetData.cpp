#include "Cmp_ButtonResetData.h"
#include "Button.h"

void ButtonResetData::Reset() { //parent�ɕێ�����f�[�^��ݒ�
	parent->SetRunUpdate(isUpdate);
	parent->SetRunDraw(isDraw);
	parent->SetRunClickMonitor(clickMonitor);
}

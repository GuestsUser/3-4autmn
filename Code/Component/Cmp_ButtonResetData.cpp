#include "Cmp_ButtonResetData.h"
#include "Button.h"

void ButtonResetData::Reset() { //parentに保持するデータを設定
	parent->SetRunUpdate(isUpdate);
	parent->SetRunDraw(isDraw);
	parent->SetRunClickMonitor(clickMonitor);
}

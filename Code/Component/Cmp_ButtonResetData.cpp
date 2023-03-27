#include "Cmp_ButtonResetData.h"
#include "Button.h"

void ButtonResetData::Reset() { //parent‚É•ÛŽ‚·‚éƒf[ƒ^‚ðÝ’è
	parent->SetRunUpdate(isUpdate);
	parent->SetRunDraw(isDraw);
	parent->SetRunClickMonitor(clickMonitor);
}

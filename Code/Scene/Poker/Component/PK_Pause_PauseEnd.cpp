#include "Cmp_PK_Pause.h"
#include "PK_Pause_PauseEnd.h"

#include "Button.h"
#include "ComponentArray.h"

void Cmp_PK_Pause::PauseEnd::Update() {
	parent->CloseOrder(); //ポーズ画面終了を指示する
}

void Cmp_PK_Pause::PauseEnd::Close(Cmp_PK_Pause& pause) {
	pause.parent->SetRunClickMonitor(true); //PK_Pauseを持つボタンのクリック検知再開

	pause.parent->SetRunUpdateClick(false); //PK_Pauseを持つボタンのクリック系動作を停止する
	pause.parent->SetRunDrawClick(false);
}
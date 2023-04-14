#include "Poker.h"
#include "Cmp_PK_Pause.h"
#include "PK_Pause_GameEnd.h"

#include "Button.h"

void Cmp_PK_Pause::GameEnd::Update() {
	if (count > runTime) { //ボタンが押されてから指定時間が経過したら
		parent->poker->SetNextSection(Poker::Section::titleback); //今回のPoker::Update終了次第ゲームセレクトへ戻るよう指示
		parent->CloseOrder(); //ポーズ画面を終了する指示
	}
	++count;
}

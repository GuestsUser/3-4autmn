#include "Poker.h"
#include "Cmp_PK_Pause.h"
#include "PK_Pause_NewGame.h"

#include "Button.h"

void Cmp_PK_Pause::NewGame::Update() {
	if (count > runTime) { //ボタンが押されてから指定時間が経過したら
		parent->poker->SetNextSection(Poker::Section::newgamereset); //Pokerの実行セクションをリセットシーンに変更
		parent->CloseOrder(); //ポーズ画面を終了する指示
	}
	++count;
}
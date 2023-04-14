#include "DxLib.h"
#include "Cmp_PK_Pause.h"
#include "PK_Pause_DataSetting.h"

#include "PK_Pause_GameEnd.h"
#include "PK_Pause_NewGame.h"
#include "PK_Pause_PauseEnd.h"

#include "Button.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include "OriginMath.h"
#include <deque>

void Cmp_PK_Pause::DataSetting::BackPlace(Cmp_Image& back) { back.EditTranform()->EditPos() = Vector3(640, 360); }
void Cmp_PK_Pause::DataSetting::ButtonNameImageSet(std::deque<Button*>& button) {
	button[0]->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause_tile_name1.png")), 1, button[0]->EditTransform())); //サイズが決まっているのでハードコード
	button[1]->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause_tile_name2.png")), 1, button[1]->EditTransform()));
	button[2]->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause_tile_name3.png")), 1, button[2]->EditTransform()));
}

void Cmp_PK_Pause::DataSetting::ButtonAppendCmpSet(Cmp_PK_Pause& pause, std::deque<Button*>& button) {
	button[0]->EditClick()->SetCmp(new PauseEnd(pause, *button[0]));
	button[1]->EditClick()->SetCmp(new NewGame(pause, *button[1]));
	button[2]->EditClick()->SetCmp(new GameEnd(pause, *button[2]));
}
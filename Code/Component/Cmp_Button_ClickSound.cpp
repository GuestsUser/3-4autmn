#include "Cmp_Button_ClickSound.h"
#include "Cmp_Sound.h"

void Cmp_Button_ClickSound::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止状態なら終わり

	sound->Play(); //サウンドを鳴らす
	SetRunUpdate(false); //実行を切る
}
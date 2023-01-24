#include "Component.h"
#include "Cmp_Gage_UpperBorder.h"

#include "Gage.h"

void Cmp_Gage_UpperBorder::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止で実行しない
	if (parent->GetVol() * 1 > border) { parent->SetVol(border); } //ボーダーをゲージが上回っている場合ボーダーの値にセットする
}
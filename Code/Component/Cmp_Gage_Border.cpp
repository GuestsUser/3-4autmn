#include "Component.h"
#include "Cmp_Gage_Border.h"

#include "Gage.h"

void Cmp_Gage_Border::Update() {
	if (!GetRunDraw()) { return; } //実行禁止で実行しない
	if (parent->GetVol() > border) { parent->SetVol(border); } //ボーダーをゲージが下回っている場合ボーダーの値にセットする
}
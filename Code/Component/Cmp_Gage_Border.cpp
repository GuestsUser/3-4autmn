#include "Component.h"
#include "Cmp_Gage_Border.h"

#include "Gage.h"

void Cmp_Gage_Border::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止で実行しない
	if (parent->GetVol() * 100 < border) { parent->SetVol(border * 0.01); } //ボーダーをゲージが下回っている場合ボーダーの値にセットする
}
#include "Gage.h"

#include "Component.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include "../Code/OriginMath.h"

#include <deque>

Gage::Gage(Cmp_Image& baseImgae, Cmp_Image& fullImage, int iniVol) :base(&baseImgae), full(&fullImage), vol(iniVol) {
	fullImage.SstDrawPivot(OriginMath::HorizonPivot::left, OriginMath::VerticalPivot::center); //伸長方向設定
	iniSize = fullImage.ReadTranform()->ReadScale().GetX(); //初期拡大率取得
}

Gage::~Gage() {
	delete full;
	delete base;
	for (auto itr : cmp) { delete itr; }
}

void Gage::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止が出ていれば実行しない
	for (auto itr : cmp) { itr->Update(); } //追加機能の実行
}

void Gage::Draw() {
	if (!GetRunDraw()) { return; } //実行禁止が出ていれば実行しない

	full->EditTranform()->EditScale().SetX(iniSize * vol * 0.01); //ゲージ実体サイズ設定

	base->Draw(); //ベース描写
	full->Draw(); //実体描写
}
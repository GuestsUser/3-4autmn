#include "DxLib.h"
#include "Title_Select_Explain_PageScrollExplain.h"

#include <cmath>


Title_Select_Explain_PageScrollExplain::Title_Select_Explain_PageScrollExplain() :str("スクロールでページめくり!"), limit(180), pos(120, 670), iniColor(Vector3(255, 25, 65)), finalColor(Vector3(75, 55, 255)) {
	Reset(); //開始countのランダム化
}

void Title_Select_Explain_PageScrollExplain::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止状態なら終わり
	++count; //時間経過
}

void Title_Select_Explain_PageScrollExplain::Draw() {
	if (!GetRunDraw()) { return; } //実行禁止状態なら終わり
	Vector3 color = iniColor + (finalColor - iniColor) * (std::cos(360.0 / limit * (count % limit) * OriginMath::Deg2Rad) + 1) * 0.5; //countから今回のカラーを決定する
	DrawString(pos.GetX(), pos.GetY(), str.c_str(), GetColor(color.GetX(), color.GetY(), color.GetZ())); //ページが複数あった場合ページめくり可能である事を表示する
}

void Title_Select_Explain_PageScrollExplain::Reset() { count = GetRand(limit); }
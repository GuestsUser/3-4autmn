#include "DxLib.h"

#include "GlovalLoading.h"
#include "ConstVal.h"
#include "Worldval.h"

void GlovalLoading() { //色々な全体向け変数の準備
	WorldVal::Set("pokerNormalFont", new int(CreateFontToHandle(nullptr, -1, -1, DX_FONTTYPE_NORMAL))); //ポーカーで使用する通常フォン作成
	WorldVal::Set("pokerNormalFontColor", new unsigned int(GetColor(0, 0, 0))); //ポーカーで使用する通常フォンの色

	WorldVal::Set("pokerEdgeFont", new int(CreateFontToHandle(nullptr, -1, -1, DX_FONTTYPE_EDGE))); //ポーカーで使用するフォン、縁付き
	WorldVal::Set("pokerEdgeFontColor", new unsigned int(GetColor(255, 255, 255))); //ポーカーで使用するエッジ付きフォンの色
	WorldVal::Set("pokerEdgeFontEdgeColor", new unsigned int(GetColor(0, 0, 0))); //ポーカーで使用するエッジ付きフォンのエッジカラー


	WorldVal::Set("score", new int(0)); //WorldVal動作テスト用数値
	WorldVal::Set("highScore", new int(0)); //上記同様のテスト用数値
}
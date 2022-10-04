#include "GlovalLoading.h"
#include "ConstVal.h"
#include "Worldval.h"

void GlovalLoading() { //色々な全体向け変数の準備
	WorldVal::Set("score", new int(0)); //WorldVal動作テスト用数値
	WorldVal::Set("highScore", new int(0)); //上記同様のテスト用数値
}
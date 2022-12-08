#pragma once
#include <deque>

class PokerFontData { //Pokerで使用するフォントデータをGlovalLoadingから取り出して保持するクラス
	static std::deque<int*> fontHandle; //フォントハンドルを詰めた配列
	static std::deque<unsigned int*> fontColor; //フォントカラーを詰めた配列
public:
	enum class type { normal, edge }; //fontHandleにこの値を添え字として使うと目的のハンドルを取る事ができる
	enum class color { normal, edgeNormal, edgeColor }; //上記のfontColor用、edgeNormalはエッジ付きフォントの通常部分カラー、edgeColorがエッジのカラー

	static void SetUp(); //最初にこれを呼び出す事で利用可能となる、各種変数はstaticなので「PokerFontData::関数」の形式で色々取得可能

	static const int* GetHandle(type get)  { return fontHandle[(int)get]; } //目的のハンドルを取る
	static const unsigned int* GetColor(color get)  { return fontColor[(int)get]; } //目的のカラーを取る

	//実体精製禁止
	PokerFontData() = delete;
	PokerFontData(const PokerFontData&) = delete;
};
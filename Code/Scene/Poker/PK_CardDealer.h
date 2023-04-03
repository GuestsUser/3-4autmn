#pragma once
#include <deque>
#include <random>
#include <utility>

class PK_Chara;

class PK_CardDealer {
private:
	std::mt19937 gen; //ランダム値生成機
	std::deque<int> deck; //山札
	int top; //山札の一番上を示す添え字
public:
	PK_CardDealer();
	void Reset(); //ラウンド終了時に呼び出す、山札の初期化等を行ってくれる

	int DeckDraw(); //山札から1枚引いた結果手に入ったカードを返す、実行すると山札も減る
};
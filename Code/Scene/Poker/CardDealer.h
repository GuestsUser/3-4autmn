#pragma once
#include <deque>
#include <random>
#include <utility>

class Chara;

class CardDealer {
public:
	using deque_map = std::deque<std::pair<int, int>>; //dequeを使用したにせマップ、mapもunorded_mapもsortに対応してないので用意
	enum class HandRank { No, OnePair, TwoPair, ThreeCard, Straight, Flash, FullHause, FourCard, StraightFlash, RoyalStraightFlash }; //役の強さ順
	enum class CardPower { one = -1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, max }; //カード数値の強さ順
private:
	std::mt19937 gen; //ランダム値生成機
	std::deque<int> deck; //山札
	int top; //山札の一番上を示す添え字
public:
	CardDealer();
	void Reset(); //ラウンド終了時に呼び出す、山札の初期化等を行ってくれる

	int DeckDraw(); //山札から1枚引いた結果手に入ったカードを返す、実行すると山札も減る
	static std::deque<int> HandCheck(const Chara& chara); //持ち札を渡すと完成役を[0]に、役になってないカードの強さをそれ以降に格納した配列で返してくれる
	static int ReachCheck(const Chara& chara); //フラッシュ若しくはストレートがあと1枚で完成するなら不要なカードを返す、完成しないなら-1で返す、不要なカードがストレートかフラッシュかで違う場合どちらを返すか内部でランダム決定する
};
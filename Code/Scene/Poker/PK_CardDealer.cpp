#include "PK_CardDealer.h"
#include "PK_Card.h"

#include <deque>
#include <numeric>
#include <random>

PK_CardDealer::PK_CardDealer() :deck(std::deque<int>(52)), gen(std::mt19937()), top(0) { gen.seed((std::random_device())()); }

void PK_CardDealer::Reset() {
	top = 0; //山札の上を0に戻す
	std::iota(deck.begin(), deck.end(), 0); //0〜52の値を各要素に格納
	std::shuffle(deck.begin(), deck.end(), gen); //代入されている値をランダム交換
}

int PK_CardDealer::DeckDraw() {
	++top; //山札を引くので1つ増やして次の添え字へ
	return deck[top - 1]; //今回の山札の数値を返す
}





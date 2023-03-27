#pragma once
#include "PK_CardDealer.h"
#include <deque>

void BorderBaseIni(std::deque<int>& base) { //baseに入れられた変数にborderbaseを設定する
	base.push_back((int)PK_CardDealer::HandRank::No * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::seven);
	base.push_back((int)PK_CardDealer::HandRank::OnePair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::six);

	base.push_back((int)PK_CardDealer::HandRank::OnePair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::two);
	base.push_back((int)PK_CardDealer::HandRank::OnePair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::queen);

	base.push_back((int)PK_CardDealer::HandRank::OnePair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::six);
	base.push_back((int)PK_CardDealer::HandRank::TwoPair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::two);

	base.push_back((int)PK_CardDealer::HandRank::OnePair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::queen);
	base.push_back((int)PK_CardDealer::HandRank::TwoPair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::six);

	base.push_back((int)PK_CardDealer::HandRank::TwoPair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::five);
	base.push_back((int)PK_CardDealer::HandRank::TwoPair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::ten);

	base.push_back((int)PK_CardDealer::HandRank::TwoPair * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::ten);
	base.push_back((int)PK_CardDealer::HandRank::ThreeCard * (int)PK_CardDealer::CardPower::max + (int)PK_CardDealer::CardPower::four);
}

void RaiseBorderBaseIni(std::deque<int>& base) { //baseに入れられた変数にraiseborderbaseを設定する
	base.push_back(0);
	base.push_back(0);

	base.push_back(1);
	base.push_back(8);

	base.push_back(1);
	base.push_back(7);

	base.push_back(1);
	base.push_back(3);

	base.push_back(0);
	base.push_back(2);

	base.push_back(0);
	base.push_back(1);
}

void PayLimitiIni(std::deque<int>& base) { //baseに入れられた変数にpaylimitを設定する
	base.push_back(0);
	base.push_back(0);

	base.push_back(1);
	base.push_back(3);

	base.push_back(2);
	base.push_back(6);

	base.push_back(4);
	base.push_back(6);

	base.push_back(6);
	base.push_back(9);

	base.push_back(10);
	base.push_back(10);

	base.push_back(1); //これはストレート、フラッシュリーチ用レイズ上限
	base.push_back(7);
}
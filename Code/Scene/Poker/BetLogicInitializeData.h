#pragma once
#include "Cmp_Hand.h"
#include <deque>

void BorderBaseIni(std::deque<int>& base) { //baseに入れられた変数にborderbaseを設定する
	base.push_back((int)Cmp_Hand::HandRank::No * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::seven);
	base.push_back((int)Cmp_Hand::HandRank::OnePair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::six);

	base.push_back((int)Cmp_Hand::HandRank::OnePair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::two);
	base.push_back((int)Cmp_Hand::HandRank::OnePair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::queen);

	base.push_back((int)Cmp_Hand::HandRank::OnePair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::six);
	base.push_back((int)Cmp_Hand::HandRank::TwoPair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::two);

	base.push_back((int)Cmp_Hand::HandRank::OnePair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::queen);
	base.push_back((int)Cmp_Hand::HandRank::TwoPair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::six);

	base.push_back((int)Cmp_Hand::HandRank::TwoPair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::five);
	base.push_back((int)Cmp_Hand::HandRank::TwoPair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::ten);

	base.push_back((int)Cmp_Hand::HandRank::TwoPair * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::ten);
	base.push_back((int)Cmp_Hand::HandRank::ThreeCard * (int)Cmp_Hand::CardPower::max + (int)Cmp_Hand::CardPower::four);
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
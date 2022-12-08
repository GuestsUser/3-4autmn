#pragma once
#include "CardDealer.h"
#include <deque>

void BorderBaseIni(std::deque<int>& base) { //base�ɓ����ꂽ�ϐ���borderbase��ݒ肷��
	base.push_back((int)CardDealer::HandRank::No * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::seven);
	base.push_back((int)CardDealer::HandRank::OnePair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::six);

	base.push_back((int)CardDealer::HandRank::OnePair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::two);
	base.push_back((int)CardDealer::HandRank::OnePair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::queen);

	base.push_back((int)CardDealer::HandRank::OnePair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::six);
	base.push_back((int)CardDealer::HandRank::TwoPair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::two);

	base.push_back((int)CardDealer::HandRank::OnePair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::queen);
	base.push_back((int)CardDealer::HandRank::TwoPair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::six);

	base.push_back((int)CardDealer::HandRank::TwoPair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::five);
	base.push_back((int)CardDealer::HandRank::TwoPair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::ten);

	base.push_back((int)CardDealer::HandRank::TwoPair * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::ten);
	base.push_back((int)CardDealer::HandRank::ThreeCard * (int)CardDealer::CardPower::max + (int)CardDealer::CardPower::four);
}

void RaiseBorderBaseIni(std::deque<int>& base) { //base�ɓ����ꂽ�ϐ���raiseborderbase��ݒ肷��
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

void PayLimitiIni(std::deque<int>& base) { //base�ɓ����ꂽ�ϐ���paylimit��ݒ肷��
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

	base.push_back(1); //����̓X�g���[�g�A�t���b�V�����[�`�p���C�Y���
	base.push_back(7);
}
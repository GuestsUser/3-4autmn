#include "PokerFontData.h"
#include "../Code/Worldval.h"

#include <deque>

std::deque<int*> PokerFontData::fontHandle = std::deque<int*>();
std::deque<unsigned int*> PokerFontData::fontColor = std::deque<unsigned int*>();

void PokerFontData::SetUp(){
	fontHandle.push_back(WorldVal::Get<int>("pokerNormalFont")); //Poker�p�ʏ�t�H���g�f�[�^�̎擾
	fontColor.push_back(WorldVal::Get<unsigned int>("pokerNormalFontColor"));

	fontHandle.push_back(WorldVal::Get<int>("pokerEdgeFont")); //�G�b�W�t���t�H���g�Ɋւ���f�[�^���擾����
	fontColor.push_back(WorldVal::Get<unsigned int>("pokerEdgeFontColor"));
	fontColor.push_back(WorldVal::Get<unsigned int>("pokerEdgeFontEdgeColor"));
}


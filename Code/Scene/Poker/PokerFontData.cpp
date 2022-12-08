#include "PokerFontData.h"
#include "../Code/Worldval.h"

#include <deque>

std::deque<int*> PokerFontData::fontHandle = std::deque<int*>();
std::deque<unsigned int*> PokerFontData::fontColor = std::deque<unsigned int*>();

void PokerFontData::SetUp(){
	fontHandle.push_back(WorldVal::Get<int>("pokerNormalFont")); //Poker用通常フォントデータの取得
	fontColor.push_back(WorldVal::Get<unsigned int>("pokerNormalFontColor"));

	fontHandle.push_back(WorldVal::Get<int>("pokerEdgeFont")); //エッジ付きフォントに関するデータを取得する
	fontColor.push_back(WorldVal::Get<unsigned int>("pokerEdgeFontColor"));
	fontColor.push_back(WorldVal::Get<unsigned int>("pokerEdgeFontEdgeColor"));
}


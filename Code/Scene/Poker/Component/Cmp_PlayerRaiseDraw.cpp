#include "DxLib.h"

#include "PK_Chara.h"
#include "PK_Dealer.h"
#include "PK_Pot.h"
#include "PokerFontData.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "Cmp_Transform.h"
#include "ComponentArray.h"
#include "Gage.h"

#include <string>
#include <cmath>

Cmp_PlayerRaiseDraw::Cmp_PlayerRaiseDraw(PK_Chara& player, PK_Pot& setPot, PK_Dealer& setDealer) :parent(&player), pot(&setPot), dealer(&setDealer),drawPos(new Cmp_Transform()) {
	drawPos->EditPos().SetXYZ(442, 633, 0); //表示位置の設定
	gage = parent->EditAppendCmp()->EditCmp<Gage>(); //ゲージ取得
}

Cmp_PlayerRaiseDraw::~Cmp_PlayerRaiseDraw() { delete drawPos; } //独自生成した位置設定用変数の削除


void Cmp_PlayerRaiseDraw::Draw() {
	int val = std::round(gage->GetVol() * dealer->GetMaxBet() * dealer->GetBB()) - pot->Inquiry(*parent); //現在ゲージ量から支払状況を引く事で未払分だけを表示する
	DrawStringToHandle(442, 624, std::to_string(val).c_str(), *PokerFontData::GetColor(PokerFontData::color::edgeNormal), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeColor));

}
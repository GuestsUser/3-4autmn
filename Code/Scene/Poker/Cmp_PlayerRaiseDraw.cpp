#include "DxLib.h"

#include "Chara.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "Cmp_BetActionRecord.h"
#include "PK_Dealer.h"
#include "Pot.h"
#include "../Code/Component/Gage.h"

#include "PokerFontData.h"
#include "../Code/Component/Cmp_Transform.h"

#include <string>
#include <cmath>

Cmp_PlayerRaiseDraw::Cmp_PlayerRaiseDraw(Chara& player, Pot& setPot, PK_Dealer& setDealer) :parent(&player), pot(&setPot), dealer(&setDealer),drawPos(new Cmp_Transform()) {
	drawPos->EditPos().SetXYZ(442, 633, 0); //表示位置の設定
	gage = parent->EditCmp<Gage>(); //ゲージ取得
}

Cmp_PlayerRaiseDraw::~Cmp_PlayerRaiseDraw() { delete drawPos; } //独自生成した位置設定用変数の削除


void Cmp_PlayerRaiseDraw::Draw() {
	int val = std::round(gage->GetVol() * dealer->GetMaxBet() * dealer->GetBB()) - pot->Inquiry(*parent); //現在ゲージ量から支払状況を引く事で未払分だけを表示する
	DrawStringToHandle(442, 624, std::to_string(val).c_str(), *PokerFontData::GetColor(PokerFontData::color::edgeNormal), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeColor));

}
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
	drawPos->EditPos().SetXYZ(442, 633, 0); //�\���ʒu�̐ݒ�
	gage = parent->EditCmp<Gage>(); //�Q�[�W�擾
}

Cmp_PlayerRaiseDraw::~Cmp_PlayerRaiseDraw() { delete drawPos; } //�Ǝ����������ʒu�ݒ�p�ϐ��̍폜


void Cmp_PlayerRaiseDraw::Draw() {
	int val = std::round(gage->GetVol() * dealer->GetMaxBet() * dealer->GetBB()) - pot->Inquiry(*parent); //���݃Q�[�W�ʂ���x���󋵂��������Ŗ�����������\������
	DrawStringToHandle(442, 624, std::to_string(val).c_str(), *PokerFontData::GetColor(PokerFontData::color::edgeNormal), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeColor));

}
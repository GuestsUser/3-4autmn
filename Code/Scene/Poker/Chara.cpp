#include "DxLib.h"

#include "Chara.h"
#include "PK_Card.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/Component/Cmp_Image.h"
#include "PokerFontData.h"

#include <string>

int Chara::coinIni = 5000; //�����������l�ݒ�

Chara::Chara() :coin(coinIni), card(std::deque<PK_Card*>()), coinBack(std::deque<Cmp_Image*>()), cmp(std::deque<Component*>()) {
	for (int i = 0; i < 5; ++i) { card.push_back(new PK_Card()); }

	coinBack.push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_score_back.png")), 1));
	int* handle = new int[2];
	LoadDivGraph("Resource/image/poker_pos_view.png", 2, 2, 1, 50, 30, handle);
	coinBack.push_back(new Cmp_Image(*handle, 2));
}

Chara::~Chara() {
	for (auto itr : card) { delete itr; }
	for (auto itr : coinBack) { delete itr; }
	ClearCmp();
}

void Chara::FullReset() {
	for (auto itr : cmp) { itr->FullReset(); } //�ǉ��@�\�̊��S������
	for (auto itr : card) { itr->FullReset(); } //�J�[�h�̊��S������
	coin = coinIni; //�������������l�ɍ��킹��
}
void Chara::Reset() {
	for (auto itr : cmp) { itr->Reset(); } //�ǉ��@�\�̏�����
	for (auto itr : card) { itr->Reset(); } //�J�[�h�̏�����
}

void Chara::Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos) {
	for (int i = 0; i < card.size(); ++i) { card[i]->Place(cardPos[i].ReadPos().GetX(), cardPos[i].ReadPos().GetY()); } //�J�[�h�z�u

	coinBack[0]->EditTranform()->EditPos() = backPos.EditPos(); //�R�C���\���pUI�̔w�i�̈ʒu��ݒ�
	coinBack[1]->EditTranform()->EditPos() = backPos.EditPos(); //bb�Asb��\�������o���̈ʒu�ݒ�A���ɔw�i�Ɠ����ʒu�ɒu���Ă���


	int backX = 0; int backY = 0; //�w�i�T�C�Y
	int bbX = 0; int bbY = 0; //�����o���T�C�Y
	GetGraphSize(*coinBack[0]->ReadImage(), &backX, &backY); //�T�C�Y�擾
	GetGraphSize(coinBack[1]->ReadImage()[1], &bbX, &bbY);
	coinBack[1]->EditTranform()->EditPos().SetXYZ(coinBack[1]->EditTranform()->EditPos().GetX() - backX / 2 + bbX / 2, coinBack[1]->EditTranform()->EditPos().GetY() - backY / 2 - bbY / 2, 0); //����z�u�ɂȂ�悤�ɍĔz�u
}

void Chara::Update() {
	if (!GetRunUpdate()) { return; }
	for (auto itr : cmp) { if (itr->GetRunUpdate()) { itr->Update(); } }
}
void Chara::Draw() {
	if (!GetRunDraw()) { return; }
	for (auto itr : card) { itr->Draw(); } //�J�[�h�`��
	for (auto itr : coinBack) { itr->Draw(); } //�R�C���`�ʗp�w�i�`��
	DrawStringToHandle(coinBack[0]->EditTranform()->ReadPos().GetX(), coinBack[0]->EditTranform()->ReadPos().GetY(), std::to_string(coin).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));

	for (auto itr : cmp) { 
		if (itr->GetRunDraw()) { itr->Draw(); } 
	}
}


void Chara::EraseCmp(Component* set) {
	for (auto itr : cmp) { if (itr == set) { delete set; return; } }
}
void Chara::ClearCmp() {
	for (auto itr : cmp) { delete itr; }
}

void Chara::GetHandNum(std::deque<int>& set) const {
	for (auto itr : card) { set.push_back(itr->GetCard()); } //��D���琔�l�݂̂����o������
}

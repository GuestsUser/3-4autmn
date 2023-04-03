#include "DxLib.h"

#include "PK_Chara.h"
#include "PK_Card.h"
#include "PokerFontData.h"

#include "Component.h"
#include "Cmp_Hand.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include <string>

int PK_Chara::coinIni = 5000; //�����������l�ݒ�

PK_Chara::PK_Chara() :coin(coinIni), hand(Cmp_Hand()), bbView(BBView::hide), coinBack(std::deque<Cmp_Image*>()), cmp(ComponentArray()){
	coinBack.push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_score_back.png")), 1));
	int* handle = new int[2];
	LoadDivGraph("Resource/image/poker_pos_view.png", 2, 2, 1, 50, 30, handle);
	coinBack.push_back(new Cmp_Image(*handle, 2));
}

PK_Chara::~PK_Chara() {
	for (auto itr : coinBack) { delete itr; }
}

void PK_Chara::FullReset() {
	cmp.FullReset(); //�ǉ��@�\�̊��S������
	hand.FullReset(); //��D��FullReset���s

	coin = coinIni; //�������������l�ɍ��킹��
	SetBBView(BBView::hide); //BB�ASB�\�����B��
}
void PK_Chara::Reset() {
	cmp.Reset(); //�ǉ��@�\�̏�����
	hand.Reset(); //��D��Reset���s

	SetBBView(BBView::hide); //BB�ASB�\�����B��
}

void PK_Chara::Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos) {
	std::deque<PK_Card*> card = *hand.EditCard(); //�J�[�h�z��擾
	for (int i = 0; i < card.size(); ++i) { card[i]->Place(cardPos[i].ReadPos().GetX(), cardPos[i].ReadPos().GetY()); } //�J�[�h�z�u

	coinBack[0]->EditTranform()->EditPos() = backPos.EditPos(); //�R�C���\���pUI�̔w�i�̈ʒu��ݒ�
	coinBack[1]->EditTranform()->EditPos() = backPos.EditPos(); //bb�Asb��\�������o���̈ʒu�ݒ�A���ɔw�i�Ɠ����ʒu�ɒu���Ă���


	int backX = 0; int backY = 0; //�w�i�T�C�Y
	int bbX = 0; int bbY = 0; //�����o���T�C�Y
	GetGraphSize(*coinBack[0]->ReadImage(), &backX, &backY); //�T�C�Y�擾
	GetGraphSize(coinBack[1]->ReadImage()[1], &bbX, &bbY);
	coinBack[1]->EditTranform()->EditPos().SetXYZ(coinBack[1]->EditTranform()->EditPos().GetX() - backX / 2 + bbX / 2, coinBack[1]->EditTranform()->EditPos().GetY() - backY / 2 - bbY / 2, 0); //����z�u�ɂȂ�悤�ɍĔz�u
}

void PK_Chara::Update() {
	if (!GetRunUpdate()) { return; }
	hand.Update(); //��D��Update�����s
	cmp.Update(); //�ǉ��@�\���s
}
void PK_Chara::Draw() {
	if (!GetRunDraw()) { return; }
	for (auto itr : coinBack) { itr->Draw(); } //�R�C���`�ʗp�w�i�`��
	DrawStringToHandle(coinBack[0]->EditTranform()->ReadPos().GetX(), coinBack[0]->EditTranform()->ReadPos().GetY(), std::to_string(coin).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));

	hand.Draw(); //��D��Draw�����s
	cmp.Draw(); //�ǉ��@�\���s
}

void PK_Chara::SetBBView(BBView set) {
	bbView = set; //�\����V�������ɓ���ւ�
	coinBack[1]->SetRunDraw(true); //�\����t����
	if (bbView == BBView::hide) { coinBack[1]->SetRunDraw(false); } //�B���w�肾�����ꍇ�`�ʂ�؂�
	else { coinBack[1]->SetAnimeSub((int)bbView); } //�V�����\���ɐ؂�ւ���
}
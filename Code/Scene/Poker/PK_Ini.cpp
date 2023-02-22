#include "PK_Ini.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"

#include "Cmp_BetActionRecord.h"
#include "../Code/Component/ComponentArray.h"


Poker::Ini::Ini(Poker& set) :parent(&set), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}

void Poker::Ini::Update() {
	parent->pot->Reset();
	parent->dealer->Reset();
	parent->cardDealer->Reset();
	for (int i = 0; i < parent->chara.size(); ++i) {
		parent->chara[i]->Reset(); //�L�����R���|�[�l���g�̃��Z�b�g

		if (actionRecord[i]->GetIsLose()) { //����L�������s�k�ς݂̏ꍇ
			std::deque<PK_Card*>* card = parent->chara[i]->EditCard(); //�J�[�h���Ǘ�����z����擾
			for (auto itr : *card) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //�J�[�h��fold�\���ɂ���
		}

	}

	int pos = EnableCharaSearch(actionRecord, parent->dealer->ReadBtn()->GetBtnPos()); //�s�k�ς݃L�������΂��ă|�W�V��������
	parent->dealer->EditBtn()->SetBtnPos(pos); //�����\�ȍŒZ�̃L�����ʒu�ɐݒ肷��
	parent->dealer->SetActionChara(EnableCharaSearch(actionRecord, (pos + 1) % parent->chara.size())); //�ʒu�X�V�ɍ��킹�ď��߂ɃA�N�V�������J�n����L�������X�V����

	parent->run = parent->list[(int)Poker::Section::pre];
}
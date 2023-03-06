#include "Poker.h"
#include "PK_Player.h"
#include "PK_Player_Change.h"

#include "CardDealer.h"
#include "PK_Card.h"
#include "PK_SectionLibrary.h"

#include "../Code/Component/Button.h"
#include "../Code/Component/Cmp_Image.h"

PK_Player::Change::Change(PK_Player& parent):parent(&parent), moveY(-48), count(0) {
	for (auto itr : *parent.EditCard()) {
		cardButton.push_back(itr->EditAppendCmp()->EditCmp<Button>()); //�v���C���[�̃J�[�h������͎�t�p�{�^�����擾
		cardPos.push_back(&itr->EditTransform()->EditPos()); //�e�J�[�h��Transform����ʒu���𔲂��o���Ă���
	}

	originalY = (*parent.EditCard())[0]->ReadTransform()->ReadPos().GetY(); //�J�[�h�̌�y���L�����Ă���
}

void PK_Player::Change::Update() {
	++count;
	if (count == 1) {
		parent->actionButton->SetRunUpdate(true); //�����p�{�^���̗L����
		parent->actionButton->SetRunDraw(true);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(true); } //�N���b�N���m���J�n����
	}
	parent->actionButtonImage->SetAnimeSub((int)Cmp_BetActionRecord::Action::change); //�{�^���摜�������ɕύX


	for (int i = 0; i < cardButton.size(); ++i) { //�e�J�[�h�̃N���b�N�`�F�b�N
		if (cardButton[i]->GetRunUpdateClick()) { //�N���b�N���ꂽ�ꍇ
			int y = cardPos[i]->GetY() - moveY * (1 - 2 * (cardPos[i]->GetY() == originalY)); //�J�[�h�����ʒu�Ɠ����Ȃ�moveY���������A����Ă����moveY���߂�
			cardPos[i]->SetY(y); //�J�[�h�ʒu�ύX
			cardButton[i]->EditTransform()->EditPos().SetY(y); //�{�^���̈ʒu���J�[�h�ʒu�ɍ��킹��

			cardButton[i]->SetRunUpdateClick(false); //�N���b�N���ĂȂ������ɖ߂�
		}
	}


	if (parent->actionButton->GetRunUpdateClick()) { //�A�N�V�����{�^���������ꂽ�ꍇ�̏���
		for (int i = 0; i < cardButton.size(); ++i) { //�e�J�[�h�̌����`�F�b�N
			std::deque<PK_Card*>* card = parent->EditCard(); //�J�[�h�z���ێ�
			if (cardPos[i]->GetY() != originalY) { //�J�[�h�����ʒu�ɂȂ��ꍇ��������Ƃ��Ĉ���
				(*card)[i]->SetCard(parent->cardDealer->DeckDraw()); //�����w��̂���J�[�h������

				cardPos[i]->SetY(originalY); //�ʒu�����ɖ߂�����
				cardButton[i]->EditTransform()->EditPos().SetY(originalY);
			}
		}

		parent->record->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //�A�N�V�����ς݂ɐݒ肷��
		parent->record->SetIsAction(true);

		parent->actionButton->SetRunUpdate(false); //�{�^��������
		parent->actionButton->SetRunDraw(false);
		parent->actionButton->SetRunUpdateClick(false); //�N���b�N��Ԃ̃��Z�b�g
		parent->actionButton->SetRunDrawClick(false);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(false); } //�N���b�N���m�𖳌���

		count = 0; //�J�E���g���Z�b�g
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //���������̂�change���ŏI�A�N�V�����Ɏw��
		return;//�I���


	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //�A�N�V���������s���ĂȂ��̂�noAction��ݒ�
}
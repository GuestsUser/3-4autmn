#include "Poker.h"
#include "PK_Player.h"
#include "PK_Player_Change.h"

#include "PK_CardDealer.h"
#include "PK_Card.h"
#include "PK_SectionLibrary.h"

#include "Button.h"
#include "Cmp_Hand.h"
#include "Cmp_Image.h"

PK_Player::Change::Change(PK_Player& parent) :parent(&parent), moveY(-48), count(0) {
	for (auto itr : *parent.EditHand()->EditCard()) {
		cardButton.push_back(itr->EditAppendCmp()->EditCmp<Button>()); //�v���C���[�̃J�[�h������͎�t�p�{�^�����擾
		cardPos.push_back(&itr->EditTransform()->EditPos()); //�e�J�[�h��Transform����ʒu���𔲂��o���Ă���
	}

	originalY = (*parent.EditHand()->EditCard())[0]->ReadTransform()->ReadPos().GetY(); //�J�[�h�̌�y���L�����Ă���
}

void PK_Player::Change::Update() {
	++count;
	if (count == 1) {
		parent->actionButton->SetRunUpdateDraw(true, true); //�����p�{�^���̗L����
		for (auto itr : cardButton) { itr->SetRunClickMonitor(true); } //�N���b�N���m���J�n����
	}
	parent->actionButtonImage->SetAnimeSub((int)Cmp_BetActionRecord::Action::change); //�{�^���摜�������ɕύX


	for (int i = 0; i < cardButton.size(); ++i) { //�e�J�[�h�̃N���b�N�`�F�b�N
		if (cardButton[i]->GetRunUpdateClick()) { //�N���b�N���ꂽ�ꍇ
			int y = cardPos[i]->GetY() - moveY * (1 - 2 * (cardPos[i]->GetY() == originalY)); //�J�[�h�����ʒu�Ɠ����Ȃ�moveY���������A����Ă����moveY���߂�
			cardPos[i]->SetY(y); //�J�[�h�ʒu�ύX
			cardButton[i]->EditTransform()->EditPos().SetY(y); //�{�^���̈ʒu���J�[�h�ʒu�ɍ��킹��

			cardButton[i]->EditClick()->SetRunUpdate(false); //�N���b�N���ĂȂ������ɖ߂�
		}
	}


	if (parent->actionButton->GetRunUpdateClick()) { //�A�N�V�����{�^���������ꂽ�ꍇ�̏���
		for (int i = 0; i < cardButton.size(); ++i) { //�e�J�[�h�̌����`�F�b�N
			std::deque<PK_Card*>* card = parent->EditHand()->EditCard(); //�J�[�h�z���ێ�
			if (cardPos[i]->GetY() != originalY) { //�J�[�h�����ʒu�ɂȂ��ꍇ��������Ƃ��Ĉ���
				(*card)[i]->SetCard(parent->cardDealer->DeckDraw()); //�����w��̂���J�[�h������

				cardPos[i]->SetY(originalY); //�ʒu�����ɖ߂�����
				cardButton[i]->EditTransform()->EditPos().SetY(originalY);
			}
		}
		parent->EditHand()->HandPowerUpdate(); //���̋�����V������D�ɍ��킹��

		parent->record->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //�A�N�V�����ς݂ɐݒ肷��
		parent->record->SetIsAction(true);

		parent->actionButton->SetRunUpdateDraw(false, false); //�{�^��������
		parent->actionButton->SetRunUpdateDrawClick(false, false); //�N���b�N��Ԃ̃��Z�b�g
		for (auto itr : cardButton) { itr->SetRunClickMonitor(false); } //�N���b�N���m�𖳌���

		count = 0; //�J�E���g���Z�b�g
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //���������̂�change���ŏI�A�N�V�����Ɏw��
		return;//�I���


	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //�A�N�V���������s���ĂȂ��̂�noAction��ݒ�
}

void PK_Player::Change::Reset() { //�J�[�h�ʒu�����삳�ꂽ�܂܂̉\��������̂Ŗ߂��Ă���
	for (int i = 0; i < cardButton.size(); ++i) { 
		cardPos[i]->SetY(originalY); //�ʒu�����ɖ߂�
		cardButton[i]->EditTransform()->EditPos().SetY(originalY); //���m�p�{�^���ʒu���߂�
		cardButton[i]->SetRunClickMonitor(false); //�N���b�N���m�𖳌���
	}
	count = 0; //�J�E���g���Z�b�g
}
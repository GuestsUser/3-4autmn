#include "PK_Chara.h"
#include "PK_CPU.h"
#include "PK_CPU_Change.h"

#include "PK_Card.h"
#include "PK_CardDealer.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_Hand.h"

#include "PK_SectionLibrary.h"

#include <deque>

void PK_CPU::Change::Update() {
	++count;
	if (count > waitTime) {
		count = 0; //�J�E���g���Z�b�g

		parent->record->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //�A�N�V�����ς݂ɐݒ肷��
		parent->record->SetIsAction(true);

		//�����Ԃœ����ĂȂ��\������
		std::deque<int> hand = parent->EditHand()->GetHandPower(); //��D�]���𓾂�
		if (hand[0] <= (int)Cmp_Hand::HandRank::OnePair * (int)Cmp_Hand::CardPower::max) { //�����y�A�ȉ��������ꍇ���[�`�`�F�b�N���s��
			PK_Card* change = parent->EditHand()->ReachCheck(); //�X�g���[�g�A�t���b�V���ɕs�v�ȃJ�[�h���擾
			if (change != nullptr) { //change�ɗL���ȃJ�[�h���������ꍇ�`�F�b�N���s��
				change->SetCard(parent->cardDealer->DeckDraw()); //�s�v�J�[�h������
				change->SetMarking(true); //���������J�[�h���}�[�L���O
				parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //���������̂�change���ŏI�A�N�V�����Ɏw��
				parent->EditHand()->HandPowerUpdate(); //���̋�����V������D�ɍ��킹��

				return; //�I���
			}
		}

		std::deque<PK_Card*> changeList = std::deque<PK_Card*>(); //�������s����D�̎Q�Ƃ����Ă䂭
		int handRank = hand[0] / (int)Cmp_Hand::CardPower::max; //��������HandRank�`���ɒ����������i�[
		int start = 1; //hand�]����������J�[�h���o�����n�߂�ʒu
		switch ((Cmp_Hand::HandRank)handRank) {
		case Cmp_Hand::HandRank::No: start = 0; break;
		case Cmp_Hand::HandRank::OnePair: start = 1; break;
		case Cmp_Hand::HandRank::TwoPair: start = 2; break;
		case Cmp_Hand::HandRank::ThreeCard: start = 1; break;
		case Cmp_Hand::HandRank::FourCard: start = 1; break;
		default: start = hand.size(); break; //��L�n���h�łȂ��ꍇ�����͂��Ȃ�
		}

		if (handRank <= (int)Cmp_Hand::HandRank::OnePair) { //�������������y�A�ȉ��������ꍇ
			if (hand[start] < (int)border) { changeList.push_back(Power2Card(*parent->EditHand()->EditCard(), hand[start])); } //�ŏ��̃J�[�h��border�ȉ��Ȃ炻�̃J�[�h�͌�������
			++start; //start�͌����̗L���Ɋւ�炸�i�߂Ȃ��Ƌ����I�Ɍ�������Ă��܂��̂Ői�߂�
		}

		for (int i = start; i < hand.size(); ++i) { //���ɂȂ��ĂȂ��J�[�h�������Ɏw�肷��
			changeList.push_back(Power2Card(*parent->EditHand()->EditCard(), hand[i])); //hand�ƈ�v����J�[�h�������J�[�h�Ƃ��ă��X�g�ɉ����鏈��
		}
		for (auto itr : changeList) { //���X�g���̃J�[�h���������鏈��
			itr->SetCard(parent->cardDealer->DeckDraw()); //�����w��̂���J�[�h������
			itr->SetMarking(true); //���������J�[�h���}�[�L���O
		}
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //���������̂�change���ŏI�A�N�V�����Ɏw��
		parent->EditHand()->HandPowerUpdate(); //���̋�����V������D�ɍ��킹��

		return; //�I���
	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //�������ĂȂ��̂�noAction���w��

}

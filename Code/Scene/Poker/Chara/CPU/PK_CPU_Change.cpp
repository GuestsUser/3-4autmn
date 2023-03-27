#include "PK_Chara.h"
#include "PK_CPU.h"
#include "PK_CPU_Change.h"

#include "PK_Card.h"
#include "PK_CardDealer.h"
#include "Cmp_BetActionRecord.h"

#include "PK_SectionLibrary.h"

#include <deque>

void PK_CPU::PK_Change::Update() {
	++count;
	if (count > waitTime) {
		count = 0; //�J�E���g���Z�b�g

		parent->record->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //�A�N�V�����ς݂ɐݒ肷��
		parent->record->SetIsAction(true);

		//�����Ԃœ����ĂȂ��\������
		std::deque<int> hand = parent->cardDealer->HandCheck(*parent); //��D�]���𓾂�
		if (hand[0] <= (int)PK_CardDealer::HandRank::OnePair * (int)PK_CardDealer::CardPower::max) { //�����y�A�ȉ��������ꍇ���[�`�`�F�b�N���s��
			int change = parent->cardDealer->ReachCheck(*parent); //�X�g���[�g�A�t���b�V���ɕs�v�ȃJ�[�h
			if (change != -1) { //change�ɗL���ȃJ�[�h���������ꍇ�`�F�b�N���s��
				for (auto itr : *parent->EditCard()) {
					if (itr->GetCard() == change) {
						itr->SetCard(parent->cardDealer->DeckDraw()); //�s�v�J�[�h������
						itr->SetMarking(true); //���������J�[�h���}�[�L���O
						parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //���������̂�change���ŏI�A�N�V�����Ɏw��
						return;//�I���
					}
				}
			}
		}

		std::deque<PK_Card*> changeList = std::deque<PK_Card*>(); //�������s����D�̎Q�Ƃ����Ă䂭
		int handRank = hand[0] / (int)PK_CardDealer::CardPower::max; //�������𐔒l�ɒ����������i�[
		int start = 1; //hand�]����������J�[�h���o�����n�߂�ʒu
		switch ((PK_CardDealer::HandRank)handRank) {
		case PK_CardDealer::HandRank::No: start = 0; break;
		case PK_CardDealer::HandRank::OnePair: start = 1; break;
		case PK_CardDealer::HandRank::TwoPair: start = 2; break;
		case PK_CardDealer::HandRank::ThreeCard: start = 1; break;
		case PK_CardDealer::HandRank::FourCard: start = 1; break;
		default: start = hand.size(); break; //��L�n���h�łȂ��ꍇ�����͂��Ȃ�
		}

		if (handRank <= (int)PK_CardDealer::HandRank::OnePair) { //�������������y�A�ȉ��������ꍇ
			if (hand[start] < (int)border) { changeList.push_back(Power2Card(*parent->EditCard(), hand[start])); } //�ŏ��̃J�[�h��border�ȉ��Ȃ炻�̃J�[�h�͌�������
			++start; //start�͌����̗L���Ɋւ�炸�i�߂Ȃ��Ƌ����I�Ɍ�������Ă��܂��̂Ői�߂�
		}

		for (int i = start; i < hand.size(); ++i) { //���ɂȂ��ĂȂ��J�[�h�������Ɏw�肷��
			changeList.push_back(Power2Card(*parent->EditCard(), hand[i])); //hand�ƈ�v����J�[�h�������J�[�h�Ƃ��ă��X�g�ɉ����鏈��
		}
		for (auto itr : changeList) { //���X�g���̃J�[�h���������鏈��
			itr->SetCard(parent->cardDealer->DeckDraw()); //�����w��̂���J�[�h������
			itr->SetMarking(true); //���������J�[�h���}�[�L���O
		}
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::change); //���������̂�change���ŏI�A�N�V�����Ɏw��
		return;//�I���
	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //�������ĂȂ��̂�noAction���w��

}

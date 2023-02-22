#include "PK_Change.h"
#include "PK_Main.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"

#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "Cmp_CPUBetLogic.h"

Poker::Change::Change(Poker& set) :parent(&set), count(0), cpuWait(30), moveY(-48), border(CardDealer::CardPower::jack), isClick(std::deque<bool>()), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), actionButton(nullptr), cardButton(std::deque<Button*>()), cardPos(std::deque<Vector3*>()) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��

	std::deque<Button*> playerButton = std::deque<Button*>();
	Button* fold = nullptr; //�{�^�������̍ۂ�fold�{�^���i�[�p�A�����fold�͎g��Ȃ��̂Ń��[�J���ϐ�
	parent->chara[(int)Poker::Character::player]->EditCmpMulti<Button>(playerButton); //�{�^�����o��
	PlayerButtonAnalyze(playerButton, &actionButton, &fold); //�{�^���z���action��fold�ɕ����i�[
	actionButtonImage = actionButton->EditAlwaysCmp<Cmp_Image>(); //�A�N�V�����p�{�^���̉摜�����o��

	for (auto itr : *parent->chara[(int)Poker::Character::player]->EditCard()) {
		cardButton.push_back(itr->EditCmp<Button>()); //�v���C���[�̃J�[�h������͎�t�p�{�^�����擾
		cardPos.push_back(&itr->EditTransform()->EditPos()); //�e�J�[�h��Transform����ʒu���𔲂��o���Ă���
	}

	originalY = (*parent->chara[(int)Poker::Character::player]->EditCard())[0]->ReadTransform()->ReadPos().GetY(); //�J�[�h�̌�y���L�����Ă���
}

void Poker::Change::Update() {
	++count;
	int access = parent->dealer->GetActionCharaSub(); //����A�N�V�������s���L�����ւ̓Y�������L�^����A�N�Z�X�V���[�g�J�b�g
	if (typeid(*parent->chara[access]) == typeid(CPU)) { //�A�N�V�����L������cpu�̏ꍇ
		if (count > cpuWait) {
			count = 0; //�J�E���g���Z�b�g

			actionRecord[access]->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //�A�N�V�����ς݂ɐݒ肷��
			actionRecord[access]->SetIsAction(true);

			int endCount = ChangeEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
			parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������

			if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
				SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g

				parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //main�ł�allIn�L�����̃A�N�V�����͕s�\�Ȃ̂ł������菜�����l�ɉ����ĂƂȂ�
				parent->run = parent->list[(int)Poker::Section::main]; //�Z�J���h�x�b�g��
				((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);


				int endCount = 1; //�A�N�V�����s�\�ȃL�����̐����擾
				for (endCount; endCount < actionRecord.size(); ++endCount) {
					if (!BetIgnore(actionRecord[(access + endCount) % actionRecord.size()])) { break; } //�`�F�b�N�L�������I��������1�ɂ�����������Ȃ������ꍇ���f
				}
				if (endCount >= actionRecord.size()) { parent->run = parent->list[(int)Poker::Section::showdown]; } //�ǂ̃L�������x�b�g�s�\�̏ꍇ�V���[�_�E�����s
			}

			//�����Ԃœ����ĂȂ��\������
			std::deque<int> hand = parent->cardDealer->HandCheck(*parent->chara[access]); //��D�]���𓾂�
			if (hand[0] <= (int)CardDealer::HandRank::OnePair * (int)CardDealer::CardPower::max) { //�����y�A�ȉ��������ꍇ���[�`�`�F�b�N���s��
				int change = parent->cardDealer->ReachCheck(*parent->chara[access]); //�X�g���[�g�A�t���b�V���ɕs�v�ȃJ�[�h
				if (change != -1) { //change�ɗL���ȃJ�[�h���������ꍇ�`�F�b�N���s��
					for (auto itr : *parent->chara[access]->EditCard()) {
						if (itr->GetCard() == change) {
							itr->SetCard(parent->cardDealer->DeckDraw()); //�s�v�J�[�h������
							itr->SetMarking(true); //���������J�[�h���}�[�L���O
							return;  //�I���
						}
					}
				}
			}

			std::deque<PK_Card*> changeList = std::deque<PK_Card*>(); //�������s����D�̎Q�Ƃ����Ă䂭
			int handRank = hand[0] / (int)CardDealer::CardPower::max; //�������𐔒l�ɒ����������i�[
			int start = 1; //hand�]����������J�[�h���o�����n�߂�ʒu
			switch ((CardDealer::HandRank)handRank) {
			case CardDealer::HandRank::No: start = 0; break;
			case CardDealer::HandRank::OnePair: start = 1; break;
			case CardDealer::HandRank::TwoPair: start = 2; break;
			case CardDealer::HandRank::ThreeCard: start = 1; break;
			case CardDealer::HandRank::FourCard: start = 1; break;
			default: start = hand.size(); break; //��L�n���h�łȂ��ꍇ�����͂��Ȃ�
			}


			if (handRank <= (int)CardDealer::HandRank::OnePair) { //�������������y�A�ȉ��������ꍇ
				if (hand[start] < (int)border) { changeList.push_back(Power2Card(*parent->chara[access]->EditCard(), hand[start])); } //�ŏ��̃J�[�h��border�ȉ��Ȃ炻�̃J�[�h�͌�������
				++start; //start�͌����̗L���Ɋւ�炸�i�߂Ȃ��Ƌ����I�Ɍ�������Ă��܂��̂Ői�߂�
			}

			for (int i = start; i < hand.size(); ++i) { //���ɂȂ��ĂȂ��J�[�h�������Ɏw�肷��
				changeList.push_back(Power2Card(*parent->chara[access]->EditCard(), hand[i])); //hand�ƈ�v����J�[�h�������J�[�h�Ƃ��ă��X�g�ɉ����鏈��
			}
			for (auto itr : changeList) { //���X�g���̃J�[�h���������鏈��
				itr->SetCard(parent->cardDealer->DeckDraw()); //�����w��̂���J�[�h������
				itr->SetMarking(true); //���������J�[�h���}�[�L���O
			}
		}
		return; //�I���
	}

	//�ȉ��v���C���[�̏ꍇ�̏���
	if (count == 1) {
		actionButton->SetRunUpdate(true); //�����p�{�^���̗L����
		actionButton->SetRunDraw(true);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(true); } //�N���b�N���m���J�n����
	}
	actionButtonImage->SetAnimeSub((int)Cmp_BetActionRecord::Action::change); //�{�^���摜�������ɕύX


	for (int i = 0; i < cardButton.size(); ++i) { //�e�J�[�h�̃N���b�N�`�F�b�N
		if (cardButton[i]->GetRunUpdateClick()) { //�N���b�N���ꂽ�ꍇ
			int y = cardPos[i]->GetY() - moveY * (1 - 2 * (cardPos[i]->GetY() == originalY)); //�J�[�h�����ʒu�Ɠ����Ȃ�moveY���������A����Ă����moveY���߂�
			cardPos[i]->SetY(y); //�J�[�h�ʒu�ύX
			cardButton[i]->EditTransform()->EditPos().SetY(y); //�{�^���̈ʒu���J�[�h�ʒu�ɍ��킹��

			cardButton[i]->SetRunUpdateClick(false); //�N���b�N���ĂȂ������ɖ߂�
		}
	}


	if (actionButton->GetRunUpdateClick()) { //�A�N�V�����{�^���������ꂽ�ꍇ�̏���
		for (int i = 0; i < cardButton.size(); ++i) { //�e�J�[�h�̌����`�F�b�N
			std::deque<PK_Card*>* card = parent->chara[access]->EditCard(); //�J�[�h�z���ێ�
			if (cardPos[i]->GetY() != originalY) { //�J�[�h�����ʒu�ɂȂ��ꍇ��������Ƃ��Ĉ���
				(*card)[i]->SetCard(parent->cardDealer->DeckDraw()); //�����w��̂���J�[�h������

				cardPos[i]->SetY(originalY); //�ʒu�����ɖ߂�����
				cardButton[i]->EditTransform()->EditPos().SetY(originalY);
			}
		}

		actionRecord[access]->SetActionRecord(Cmp_BetActionRecord::Action::change, true); //�A�N�V�����ς݂ɐݒ肷��
		actionRecord[access]->SetIsAction(true);

		int endCount = ChangeEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
		parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������

		if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
			SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
			parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //main�ł�allIn�L�����̃A�N�V�����͕s�\�Ȃ̂ł������菜�����l�ɉ����ĂƂȂ�
			parent->run = parent->list[(int)Poker::Section::main]; //�Z�J���h�x�b�g��
			((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);


			int endCount = 1; //�A�N�V�����s�\�ȃL�����̐����擾
			for (endCount; endCount < actionRecord.size(); ++endCount) {
				if (!BetIgnore(actionRecord[(access + endCount) % actionRecord.size()])) { break; } //�`�F�b�N�L�������I��������1�ɂ�����������Ȃ������ꍇ���f
			}
			if (endCount >= actionRecord.size()) { parent->run = parent->list[(int)Poker::Section::showdown]; } //�ǂ̃L�������x�b�g�s�\�̏ꍇ�V���[�_�E�����s
		}


		actionButton->SetRunUpdate(false); //�{�^��������
		actionButton->SetRunDraw(false);
		actionButton->SetRunUpdateClick(false); //�N���b�N��Ԃ̃��Z�b�g
		actionButton->SetRunDrawClick(false);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(false); } //�N���b�N���m�𖳌���

		count = 0; //�J�E���g���Z�b�g
	}


}

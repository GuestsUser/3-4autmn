#include "PK_SectionLibrary.h"

#include "../Code/ConstVal.h"

#include "Btn.h"
#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"
#include "PokerFontData.h"

#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"

#include <algorithm>
#include <deque>
#include <typeinfo>
#include <string>
#include <cmath>


PK_Card* Power2Card(std::deque<PK_Card*>& hand, int target) { //hand����target�ɓn���ꂽ�J�[�h�̋����ƈ�v����J�[�h�𒊏o����
	for (auto itr : hand) {
		if (itr->GetCard() % (int)CardDealer::CardPower::max == target) { return itr; } //target�ƈ�v����PK_Card�Q�Ƃ�Ԃ�
	}
}

Cmp_BetActionRecord::Action ActionDecision(Cmp_CPUBetLogic* betLogic) { //�����ꂽbetLogic�ɂ����raise���ׂ���call���ׂ����Ԃ�
	return betLogic->GetSelfRaise() ? Cmp_BetActionRecord::Action::raise : Cmp_BetActionRecord::Action::call;
}

bool BetIgnore(Cmp_BetActionRecord* record) { //�L�����̃A�N�V�����L�^��n�����ł��̃L�����̃x�b�g���X�L�b�v���ׂ����ۂ��Ԃ��Atrue�ŃX�L�b�v
	return record->GetActionRecord(Cmp_BetActionRecord::Action::allIn) || record->GetActionRecord(Cmp_BetActionRecord::Action::fold) || record->GetIsLose(); //allIn�AFold�A�s�k�ς݂̏ꍇ�x�b�g���X�L�b�v
}

bool IsFold(Cmp_BetActionRecord& record) { //record�̃L�������A�N�V�������I��点������fold�ŏ��O���ꂽ�����̃t�F�[�Y�����ł��Ȃ��Ȃ��Ă����true��Ԃ�
	return record.GetActionRecord(Cmp_BetActionRecord::Action::fold) || record.GetIsLose() || record.GetIsAction(); //fold���Ă���A�s�k�ς݁A�A�N�V�������s�ς݂�true��Ԃ�
}

int FoldCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //�Q�[�����甲�����L��������Ԃ��Acenter��record�֎g�p����Y����������Ƃ��̃L�����𒆐S�Ƀ`�F�b�N����
	int dropCount = 1; //���̃��E���h���甲�����L�������L�^����

	for (int i = 1; i < (int)Poker::Character::length; ++i) {
		Cmp_BetActionRecord current = *actionRecord[(center + i) % (int)Poker::Character::length]; //����`�F�b�N����L�����A���̃A�N�Z�X�V���[�g�J�b�g
		dropCount += current.GetActionRecord(Cmp_BetActionRecord::Action::fold) || current.GetIsLose(); //��΂������̉��ꂩ�Ɋ|�����Ă����+1����
	}
	return dropCount;
}

int ActionEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //�A�N�V�����I���ς݃L��������Ԃ��Acenter��record�֎g�p����Y����������Ƃ��̃L�����𒆐S�ɏI���ς݃L���������`�F�b�N����
	int endCount = 1; //�A�N�V�������I������L���������L�^����
	for (endCount; endCount < (int)Poker::Character::length; ++endCount) {
		Cmp_BetActionRecord current = *actionRecord[(center + endCount) % (int)Poker::Character::length]; //����`�F�b�N����L�����A���̃A�N�Z�X�V���[�g�J�b�g
		if (current.GetIsAction()) { continue; } //�A�N�V�����I���ς݂Ȃ��蒼��
		if (BetIgnore(&current)) { continue; } //�A�N�V�����s�\�Ȃ��蒼��
		break; //�����܂ŗ����L�����̓A�N�V�����\�Ȃ̂ŏI���
		//if (!(BetIgnore(&current) || current.GetIsAction())) { break; } //�`�F�b�N�L�������I��������1�ɂ�����������Ȃ������ꍇ���f
	}
	return endCount;
}

int ChangeEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //Change��pEndCount�A��L��BetIgnore�Ȃ̂�Change�ɂ͎g���Ȃ�����p��
	int endCount = 1; //�A�N�V�������I������L���������L�^����
	for (endCount; endCount < (int)Poker::Character::length; ++endCount) {
		Cmp_BetActionRecord current = *actionRecord[(center + endCount) % (int)Poker::Character::length]; //����`�F�b�N����L�����A���̃A�N�Z�X�V���[�g�J�b�g
		if (!IsFold(current)) { break; } //�`�F�b�N�L�������I��������1�ɂ�����������Ȃ������ꍇ���f
	}
	return endCount;
}

int EnableCharaSearch(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //��LEndCount�ł͏I���L�����𒲂ׂ����������center����ŒZ�̖��s�k�L�����Y������Ԃ�
	int add = 0;
	for (add; add < actionRecord.size(); ++add) { //center�𒆐S�ɑΏۃL�������s�k���Ă��邩���ׂ�
		Cmp_BetActionRecord current = *actionRecord[(center + add) % actionRecord.size()]; //����`�F�b�N����L�����A���̃A�N�Z�X�V���[�g�J�b�g
		if (current.GetIsAction()) { continue; } //�A�N�V�����I���ς݂Ȃ��蒼��
		if (BetIgnore(&current)) { continue; } //�A�N�V�����s�\�Ȃ��蒼��
		break; //�����܂ŗ����L�����̓A�N�V�����\�Ȃ̂ŏI���
	}
	if (add >= actionRecord.size()) { return -1; } //�S������s�\�ɂȂ��Ă����ꍇ-1��Ԃ�
	return (center + add) % actionRecord.size(); //center�̎��ɂ����s���\�ȃL�����Y������Ԃ�
}


int RaiseCalculation(const std::deque<int>& split, int& runCount, int oldPay, int betRequest, int BB, int coin) {
	//���E���h���ł̑��x���z�ƕ������C�Y�������܂Ŏg������Ԃ��Asplit�ɕ������C�Y�f�[�^�ArunCount��split�ǂݏo���J�n�ʒu��(�ҏW�����A���̓ǂݏo���J�n�ʒu�܂ňړ������)�AoldPay�ɑO��܂ł̎x���z�AbetRequest�Ɍ��ݍő�x�b�g���ABB�Ɍ���BB���Acoin�ɏ�����������
	int adjustSB = oldPay % BB != 0 ? oldPay : 0; //SB���O��x���z�Ɋ܂܂�Ă���(BB�Ŋ���؂�Ȃ�=SB)�ꍇ�������菜�����l���ŏI���C�Y�z�Ƃ���
	for (runCount; runCount < split.size();) { //�x���z�����݃x�b�g������悤�������C�Y�𒲐��g�p���鏈��
		int nowPayMent = split[runCount] * BB; //�����split�x���z
		if (coin - (oldPay + nowPayMent) < 0) { break; } //���C�Y�ŏ�������0�����ɂ��Ă��܂��ꍇ���񕪂͎g�킸�I��

		oldPay += nowPayMent; //���񕪂̎x���z��������
		++runCount; //runCount��i�߂�A���̃^�C�~���O�Ŏ��s���鎖�ɈӖ�������
		if (oldPay > betRequest) { break; } //���݂̕������Ńx�b�g�ő�𒴂�����I��
	}

	return oldPay - betRequest - adjustSB; //���C�Y�ɂ�鑝���z��Ԃ��ASB����菜�����l�Ƃ���
}

void SequenceNextReset(const std::deque<Cmp_BetActionRecord*>& chara) { //���V�[�P���X�ֈڍs����ێ��s����A�N�V�����L�^���Z�b�g�p�֐�
	for (auto itr : chara) {
		itr->SetActionRecord(Cmp_BetActionRecord::Action::check, false); //allIn��Loose�ȊO�̃A�N�V���������Z�b�g
		itr->SetActionRecord(Cmp_BetActionRecord::Action::call, false);
		itr->SetActionRecord(Cmp_BetActionRecord::Action::raise, false);
		itr->SetIsAction(false); //�A�N�V���������s��Ԃɖ߂�
	}
}

void BBSBLevy(int BBpos, std::deque<Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord, Cmp_Gage_Border& gageBorder, Cmp_Gage_UpperBorder& gageUpper, Pot& pot, PK_Dealer& dealer) { //BB�ASB�|�W�V�����L��������BB�ASB�����

	int iniActionChara = dealer.GetActionCharaSub(); //�A�N�V���������s����L�����̏����ݒ�L��
	float playerCoin = chara[(int)Poker::Character::player]->GetCoint(); //�v���C���[�̕ێ��R�C���L��

	if (playerCoin - dealer.GetBB() * dealer.GetMaxBet() <= 0) { gageUpper.SetBorder(playerCoin / (dealer.GetBB() * dealer.GetMaxBet())); } //�ő�x�b�g�\�z���v���C���[�������𒴂��Ă����ꍇ�|��������������ɍ��킹��
	for (int i = 0; i < 2; ++i) { //BB�ASB��2�񒥎����K�v�Ȃ̂�i<2
		int levy = EnableCharaSearch(actionRecord, BBpos + i); //����̃L�����`�F�b�N�ʒu
		int coin = chara[levy]->GetCoint(); //���ݏ�����
		int pay = dealer.GetBB() / (i + 1); //�x���z
		chara[levy]->SetBBView((Chara::BBView)i); //�x���z�ɉ�����BB�x������SB�x�������\����ݒ肷��

		if (coin - pay <= 0) { //�x���z���������������Ă����ꍇ
			pay = coin; //�����Ă镪���x���z�ɐݒ肷��
			actionRecord[levy]->SetActionRecord(Cmp_BetActionRecord::Action::allIn, true); //����allIn
			actionRecord[levy]->SetIsAction(true); //�A�N�V�����ς݂ɂ����

			int newActionChara = EnableCharaSearch(actionRecord, levy); //�ʒu�X�V�ɍ��킹���V�����A�N�V�������s�L����
			if (newActionChara <= -1) { newActionChara = iniActionChara; } //�S���A�N�V�����ς݂ɂȂ��Ă����ꍇ�����̃L�������w�肷��
			dealer.SetActionChara(newActionChara); //�ʒu�X�V�ɍ��킹�ď��߂ɃA�N�V�������J�n����L�������X�V����
		}
		float border = (float)pay / (dealer.GetBB() * dealer.GetMaxBet()); //����x���ɉ������v���C���[�Q�[�W�̉����ݒ�
		if (border > gageBorder.GetBorder()) { //���񉺌������܂ł̉����𒴂��Ă����ꍇ
			pot.SetMainPot(pay, *chara[levy]); //���C���|�b�g��BB�ASB�x����
			gageBorder.SetBorder(border); //�����Đݒ�
		}
		else { pot.SetSidePot(pay, *chara[levy]); } //�����ȉ��̎x�����������ꍇ�T�C�h�|�b�g�Ƃ��čĐU�蕪�����s��

		chara[levy]->SetCoin(coin - pay); //�x���������������獷������
	}

}

void LoseSet(const std::deque<Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord) { //���ݏ������ɍ��킹�Ĕs�k�ݒ���s��
	for (int i = 0; i < chara.size(); ++i) { actionRecord[i]->SetIsLose(chara[i]->GetCoint() <= 0); } //��������0�ȉ��ɂȂ�����s�k�ɐݒ肷��
}

void FullReset(std::deque<Chara*>& chara, Pot& pot, PK_Dealer& dealer, CardDealer& cardDealer) { //�e��fullReset�����s��Pre����V�����Q�[�����n�߂���悤�ɂ���
	pot.Reset();
	dealer.FullReset();
	cardDealer.Reset();
	for (auto chara : chara) { chara->FullReset(); }
}

void PlayerButtonAnalyze(const std::deque<Button*>& button, Button** action, Button** fold) { //button��player�̃{�^����������action�ɃA�N�V�����p�{�^���Afold��fold�p�{�^�������ĕԂ��Ă����
	for (auto itr : button) {
		if ((itr->EditAlwaysCmp<Cmp_Image>())->GetAnimeLength() == 1) { *fold = itr; } //�����摜������1�Ȃ�fold�{�^��
		else { *action = itr; } //�Ⴄ�Ȃ�A�N�V�����{�^��
	}
}

std::string Hand2String(const std::deque<int>& hand) {
	switch ((CardDealer::HandRank)(hand[0] / (int)CardDealer::CardPower::max)) {
	case CardDealer::HandRank::No: return "�n�C�J�[�h"; break;
	case CardDealer::HandRank::OnePair: return "�����y�A"; break;
	case CardDealer::HandRank::TwoPair: return "�c�[�y�A"; break;
	case CardDealer::HandRank::ThreeCard: return "�X���[�J�[�h"; break;
	case CardDealer::HandRank::Straight: return "�X�g���[�g!"; break;
	case CardDealer::HandRank::Flash: return "�t���b�V��!"; break;
	case CardDealer::HandRank::FullHause: return "�t���n�E�X!"; break;
	case CardDealer::HandRank::FourCard: return "�t�H�[�J�[�h!!"; break;
	case CardDealer::HandRank::StraightFlash: return "�X�g���[�g�t���b�V��!!"; break;
	case CardDealer::HandRank::RoyalStraightFlash: return "���C�����X�g���[�g�t���b�V��!!!"; break;
	}

}

void FoldMemberPayOut(std::deque<Chara*>& chara, Pot& pot) { //fold�L������PayOut
	Chara* maxChara = chara[0]; //�ő�x���z�����L����
	int max = pot.Inquiry(*maxChara); //�ő�x���z
	for (int i = 1; i < chara.size(); ++i) {
		int current = pot.Inquiry(*chara[i]); //����L�����̎x���z
		if (max < current) { //����L�������ő�x�b�g�z�������Ă����max�n�̒��g������
			max = current;
			maxChara = chara[i];
		}
	}
	max = pot.PayOut(*maxChara) / chara.size(); //�ő�x���z�����L�����Ń|�b�g������z���o��
	for (int i = 0; i < chara.size(); ++i) { chara[i]->SetCoin(chara[i]->GetCoint() + max); } //�c��𕪔z
}

Poker::Section GameEndCheck(const std::deque<Chara*>& chara, const std::deque<Cmp_BetActionRecord*>& actionRecord) { //���݂̔s�k�󋵂���������ׂ��V�[����Ԃ�
	int loseCount = 0; //�s�k�L�������̃J�E���g
	for (auto itr : actionRecord) { loseCount += itr->GetIsLose(); } //�S�L�������`�F�b�N���s�k�L���������J�E���g���Ă䂭

	Poker::Section val = Poker::Section::ini; //�Ԃ��l�A�Q�[���𑱍s���ׂ��Ȃ�ini��Ԃ�
	if (loseCount >= (int)Poker::Character::length - 1) { val = Poker::Section::gameclear; } //1�L�����ȊO�S�Ă��s�k���Ă����ꍇ�Q�[���N���A��ݒ�
	if (actionRecord[(int)Poker::Character::player]->GetIsLose()) { val = Poker::Section::gameover; } //�v���C���[���s�k���Ă����ꍇ�Q�[���I�[�o�[��ݒ�A�N���A�ƃI�[�o�[�ł̓I�[�o�[���D��

	return val;
}
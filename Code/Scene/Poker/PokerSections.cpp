#include "../Scene.h"
#include "Poker.h"
#include "PokerSections.h"
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
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"

#include <algorithm>
#include <deque>
#include <typeinfo>
#include <string>

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
		if (!(BetIgnore(&current) || current.GetIsAction())) { break; } //�`�F�b�N�L�������I��������1�ɂ�����������Ȃ������ꍇ���f
	}
	return endCount;
}

int RaiseCalculation(const std::deque<int>& split, int& runCount, int oldPay, int betRequest, int BB, int coin) {
	//���E���h���ł̑��x���z�ƕ������C�Y�������܂Ŏg������Ԃ��Asplit�ɕ������C�Y�f�[�^�ArunCount��split�ǂݏo���J�n�ʒu��(�ҏW�����A���̓ǂݏo���J�n�ʒu�܂ňړ������)�AoldPay�ɑO��܂ł̎x���z�AbetRequest�Ɍ��ݍő�x�b�g���ABB�Ɍ���BB���Acoin�ɏ�����������
	for (runCount; runCount < split.size();) { //�x���z�����݃x�b�g������悤�������C�Y�𒲐��g�p���鏈��
		int nowPayMent = split[runCount] * BB; //�����split�x���z
		if (coin - (oldPay + nowPayMent) < 0) { break; } //���C�Y�ŏ�������0�����ɂ��Ă��܂��ꍇ���񕪂͎g�킸�I��

		oldPay += nowPayMent; //���񕪂̎x���z��������
		++runCount; //runCount��i�߂�A���̃^�C�~���O�Ŏ��s���鎖�ɈӖ�������
		if (oldPay > betRequest) { break; } //���݂̕������Ńx�b�g�ő�𒴂�����I��
	}
	return oldPay - betRequest; //���C�Y�ɂ�鑝���z��Ԃ�
}

void SequenceNextReset(const std::deque<Cmp_BetActionRecord*>& chara) { //���V�[�P���X�ֈڍs����ێ��s����A�N�V�����L�^���Z�b�g�p�֐�
	for (auto itr : chara) {
		itr->SetActionRecord(Cmp_BetActionRecord::Action::check, false); //allIn��Loose�ȊO�̃A�N�V���������Z�b�g
		itr->SetActionRecord(Cmp_BetActionRecord::Action::call, false);
		itr->SetActionRecord(Cmp_BetActionRecord::Action::raise, false);
		itr->SetIsAction(false); //�A�N�V���������s��Ԃɖ߂�
	}
}

//������
void BBSBLevy(int BBpos, std::deque<Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord, Pot& pot, PK_Dealer& dealer) { //BB�ASB�|�W�V�����L��������BB�ASB�����

	for (int i = 0; i < 2; ++i) { //BB�ASB��2�񒥎����K�v�Ȃ̂�i<2
		int levy = (BBpos + i) % chara.size(); //����̃L�����`�F�b�N�ʒu

		for (int j = 0; j < chara.size(); ++j) { //����L�����𒆐S�ɑΏۃL�������s�k���Ă��邩���ׂ�
			if (!IsFold(*actionRecord[levy + j])) { break; } //�Ώۂ����s�k�̏ꍇ�s�k�`�F�b�N�I��
			levy = (levy + 1) % chara.size(); //1�L������i�߂�
		}
		int coin = chara[levy]->GetCoint(); //���ݏ�����
		int pay = dealer.GetBB() / (i + 1); //�x���z
		chara[levy]->SetBBView((Chara::BBView)i); //�x���z�ɉ�����BB�x������SB�x�������\����ݒ肷��

		if (coin - pay <= 0) { //�x���z���������������Ă����ꍇ
			actionRecord[i]->SetActionRecord(Cmp_BetActionRecord::Action::allIn, true); //����allIn
			actionRecord[i]->SetIsAction(true); //�A�N�V�����ς݂ɂ����
			pot.SetSidePot(coin, *chara[levy]); //�����Ă镪�����x�����Ă��炤
			chara[levy]->SetCoin(0); //��ɂ���

			//parent->dealer->SetActionChara((pos + 1) % parent->chara.size()); //�ʒu�X�V�ɍ��킹�ď��߂ɃA�N�V�������J�n����L�������X�V����



			continue; //���̃L�����ɑ΂��鑀��I���
		}

		pot.SetMainPot(pay, *chara[levy]); //BB�ASB�̎x����
		chara[levy]->SetCoin(coin - pay); //�x���������������獷������

	}
}

void LoseSet(const std::deque<Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord) { //���ݏ������ɍ��킹�Ĕs�k�ݒ���s��
	for (int i = 0; i < chara.size(); ++i) { actionRecord[i]->SetIsLose(chara[i]->GetCoint() <= 0); } //��������0�ȉ��ɂȂ�����s�k�ɐݒ肷��
}

Poker::Section GameEndCheck(const std::deque<Chara*>& chara, const std::deque<Cmp_BetActionRecord*>& actionRecord) { //���݂̔s�k�󋵂���������ׂ��V�[����Ԃ�
	int loseCount = 0; //�s�k�L�������̃J�E���g
	for (auto itr : actionRecord) { loseCount += itr->GetIsLose(); } //�S�L�������`�F�b�N���s�k�L���������J�E���g���Ă䂭
	
	Poker::Section val = Poker::Section::ini; //�Ԃ��l�A�Q�[���𑱍s���ׂ��Ȃ�ini��Ԃ�
	if (loseCount >= (int)Poker::Character::length - 1) { val = Poker::Section::gameclear; } //1�L�����ȊO�S�Ă��s�k���Ă����ꍇ�Q�[���N���A��ݒ�
	if (actionRecord[(int)Poker::Character::player]->GetIsLose()) { val = Poker::Section::gameover; } //�v���C���[���s�k���Ă����ꍇ�Q�[���I�[�o�[��ݒ�A�N���A�ƃI�[�o�[�ł̓I�[�o�[���D��

	return val;
}

void FullReset(std::deque<Chara*>& chara, Pot& pot, PK_Dealer& dealer, CardDealer& cardDealer) { //�e��fullReset�����s��Pre����V�����Q�[�����n�߂���悤�ɂ���
	pot.Reset();
	dealer.FullReset();
	cardDealer.Reset();
	for (auto chara : chara) { chara->FullReset(); }
}





Poker::Ini::Ini(Poker& set) :parent(&set), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}

void Poker::Ini::Update() {
	parent->pot->Reset();
	parent->dealer->Reset();
	parent->cardDealer->Reset();
	for (auto chara : parent->chara) { chara->Reset(); }

	//���f�o�b�O
	//int pos = parent->dealer->ReadBtn()->GetBtnPos(); //�s�k�ς݃L�������΂��ă|�W�V�������肩��
	//for (int i = 0; i < parent->chara.size(); ++i) { //�S�L��������
	//	if (!IsFold(*actionRecord[pos])) { break; } //���݃L�����������\�Ȃ烋�[�v����
	//	pos = (pos + 1) % parent->chara.size(); //1�L������i�߂�
	//}
	//parent->dealer->EditBtn()->SetBtnPos(pos); //�����\�ȍŒZ�̃L�����ʒu�ɐݒ肷��
	//parent->dealer->SetActionChara((pos + 1) % parent->chara.size()); //�ʒu�X�V�ɍ��킹�ď��߂ɃA�N�V�������J�n����L�������X�V����

	parent->run = parent->list[(int)Poker::Section::pre];
}

Poker::Pre::Pre(Poker& set) :parent(&set), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}

void Poker::Pre::Update() {
	//���f�o�b�O
	//BBSBLevy(parent->dealer->ReadBtn()->GetBtnPos(), parent->chara, actionRecord, *parent->pot, *parent->dealer); //BB�ASB�̒���


	for (auto itr : parent->chara) {

		//�f�o�b�O�p
		//for (auto card : *itr->EditCard()) { card->SetDrawMode(PK_Card::DrawMode::front); } //�J�[�h���������Ă��� 

		for (auto card : *itr->EditCard()) { card->SetCard(parent->cardDealer->DeckDraw()); } //�R�D��������Ă����J�[�h����D�ɐݒ�
		if (typeid(*itr) == typeid(CPU)) { //���̃L������cpu�������ꍇ
			(itr->EditCmp<Cmp_CPUBetLogic>())->RaiseVolDecision(*itr, true); //���ݎ�D���烌�C�Y���ƕ����A���僌�C�Y���邩�ǂ��������肷��
		}
		else { //�v���C���[�������ꍇ
			for (auto card : *itr->EditCard()) { card->SetDrawMode(PK_Card::DrawMode::front); } //�J�[�h���������Ă��� 
		}
	}
	//�f�o�b�O�p
	//parent->run = parent->list[(int)Poker::Section::change];

	parent->run = parent->list[(int)Poker::Section::main];
	((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(0); //�_�E���L���X�g�������g���n�b�L�����Ă邩�狖���āc�c
}

void PlayerButtonAnalyze(const std::deque<Button*>& button, Button** action, Button** fold) { //button��player�̃{�^����������action�ɃA�N�V�����p�{�^���Afold��fold�p�{�^�������ĕԂ��Ă����
	for (auto itr : button) {
		if ((itr->EditAlwaysCmp<Cmp_Image>())->GetAnimeLength() == 1) { *fold = itr; } //�����摜������1�Ȃ�fold�{�^��
		else { *action = itr; } //�Ⴄ�Ȃ�A�N�V�����{�^��
	}
}

Poker::Main::Main(Poker& set) :parent(&set), phase(0), count(0), cpuWait(30), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), betLogic(std::deque<Cmp_CPUBetLogic*>(3)), playerButton(std::deque<Button*>()), actionButton(nullptr), foldButton(nullptr), playerGage(nullptr), playerGageBorder(nullptr), gageControl(nullptr), actionButtonImage(nullptr) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
	for (int i = 0; i < betLogic.size(); ++i) { betLogic[i] = parent->chara[i]->EditCmp<Cmp_CPUBetLogic>(); } //�x�b�g���W�b�N���o���Achara�z��̕��я���player�Ō�ɂȂ��Ă�̂ł���œ����A�s���Ȃ�if����player�`�F�b�N���Ă�����
	parent->chara[(int)Poker::Character::player]->EditCmpMulti<Button>(playerButton); //�{�^�����o��
	PlayerButtonAnalyze(playerButton, &actionButton, &foldButton); //�{�^���z���action��fold�ɕ����i�[
	actionButtonImage = actionButton->EditAlwaysCmp<Cmp_Image>(); //�A�N�V�����p�{�^���̉摜�����o��


	playerGage = parent->chara[(int)Poker::Character::player]->EditCmp<Gage>(); //�Q�[�W���o��
	playerGageBorder = playerGage->EditCmp<Cmp_Gage_Border>(); //�Q�[�W����e��@�\�����o��
	gageControl = playerGage->EditCmp<Cmp_Gage_MouseControl>();
}

void Poker::Main::Update() {
	++count;
	int access = parent->dealer->GetActionCharaSub(); //����A�N�V�������s���L�����ւ̓Y�������L�^����A�N�Z�X�V���[�g�J�b�g
	if (typeid(*parent->chara[access]) == typeid(CPU)) { //�A�N�V�����L������cpu�̏ꍇ

		if (count > cpuWait) { //�w��ҋ@���Ԃ𒴂����ꍇ���s�A�N�V���������肷��
			count = 0; //�J�E���g���Z�b�g

			Cmp_BetActionRecord* record= actionRecord[access]; //���̃L�����̃x�b�g�L�^���擾
			Cmp_CPUBetLogic* betData = betLogic[access]; //cpu�̃x�b�g���f�@�\�̎擾
			int raise = 0; //���̃L�����̃��C�Y�\��
			for (auto itr : *betData->ReadRaiseSplit()) { raise += itr; } //�������ꂽ���C�Y�\�񐔂���ɓZ�߂�
			raise *= parent->dealer->GetBB(); //����BB�����C�Y�\�񐔂Ɋ|���ă��C�Y�\�z�ɕύX����

			int betRequest = parent->pot->GetCurrentMaxBet(); //���ݍő�x�b�g���z
			int oldPay = parent->pot->Inquiry(*parent->chara[access]); //���̃L�����̑O��܂ł̎x���z
			int pay = betRequest - oldPay; //�x�����z


			Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::fold; //���s���ׂ��A�N�V�������i�[
			if (raise > betRequest) { action = ActionDecision(betData); } //���ݍő�x�b�g�����C�Y�\�z�𒴂��Ă��Ȃ���΃��C�Y�A�R�[������
			if (record->GetRaiseRunCount() > 0 && raise * 5 > parent->pot->GetCurrentMaxBet()) { action = ActionDecision(betData); } //1�x���C�Y�������Ƃ�����ꍇ���C�Y�\�z��5�{�܂ł̓��C�Y���󂯂�
			if (parent->chara[access]->GetCoint() - betRequest <= 0) { action = Cmp_BetActionRecord::Action::allIn; } //�R�[������ł��Ȃ��������Ȃ�I�[���C���ɂȂ�

			if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y�̗�O��e������
				//if (raise <= parent->pot->GetCurrentMaxBet()) { action = Cmp_BetActionRecord::Action::call; } //���C�Y�����̏ꍇ�ł��v���z�����C�Y�\�񐔂𒴂��Ă����ꍇ�R�[���ɂȂ�
				if (record->GetRaiseRunCount() >= betData->ReadRaiseSplit()->size()) { action = Cmp_BetActionRecord::Action::call; } //���C�Y�\�z�S�Ă��g���؂��Ă����ꍇ�R�[���ɂȂ�
			}
			
			if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y�z�o������
				int runCount = record->GetRaiseRunCount(); //�����split�ǂݏo���J�n�ʒu������
				int raiseAdd=RaiseCalculation(*betData->ReadRaiseSplit(), runCount, oldPay, betRequest, parent->dealer->GetBB(), parent->chara[access]->GetCoint()); //���C�Y�ɂ�鑝���𓾂�

				record->SetRaiseRunCount(runCount); //�g�p�ςݕ��������L�^����
				if (raiseAdd <= 0) { action = Cmp_BetActionRecord::Action::call; } //���C�Y���Ă��͂��Ȃ������菊�����̖��Ŏw�蕪���C�Y�ł��Ȃ������ꍇcall�ɂ���
				else { pay += raiseAdd; } //���ʂɃ��C�Y�ł���Α�����������
			}
			if (action == Cmp_BetActionRecord::Action::call && pay == 0) { action = Cmp_BetActionRecord::Action::check; } //�w��A�N�V������call�ŋ��z�x�������s�v�̏ꍇ�`�F�b�N�ɂȂ�


			record->SetActionRecord(action, true); //�Y���A�N�V�����𓮍�ς݂ɂ���
			record->SetIsAction(true); //�A�N�V�����ς݂ɐݒ�

			if (action == Cmp_BetActionRecord::Action::call || action == Cmp_BetActionRecord::Action::raise) { parent->pot->SetMainPot(pay, *parent->chara[access]); } //call�Araise�̏ꍇ���C���|�b�g��
			if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent->chara[access]); } //allIn�̏ꍇ�T�C�h�|�b�g��
			if (action != Cmp_BetActionRecord::Action::fold) { parent->chara[access]->SetCoin(parent->chara[access]->GetCoint() - pay); } //fold�ȊO�̏ꍇ����������x���z�����Z����(check�̏ꍇpay��0�Ȃ̂Œe���K�v�Ȃ�)

			if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y���Ă����ꍇ�S���̃A�N�V�����󋵂̌��������s��
				for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allIn�����Ă��Ȃ��ꍇ���A�N�V������ԂɍX�V����
				playerGageBorder->SetBorder(((pay + oldPay) / parent->dealer->GetBB()) * parent->dealer->GetMaxBet()); //�Q�[�W�̍Œ�l���X�V
				record->SetIsAction(true); //���C�Y�����L�����̃A�N�V�����͏I���ς݂ɐݒ肷��
			}

			
			
			int endCount = ActionEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
			if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
				SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
				if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //�t�@�[�X�g�x�b�g�������ꍇ�����s����V�[�P���X�̓J�[�h����
				else { parent->run = parent->list[(int)Poker::Section::showdown]; } //�Z�J���h�x�b�g�Ȃ�V���[�_�E���ֈڍs����
			}
			if (action == Cmp_BetActionRecord::Action::fold) { //�t�H�[���h�����ꍇ���E���h���f�`�F�b�N���s��
				for (auto itr : *parent->chara[access]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //��D��fold�\���֕ύX
				
				if (FoldCount(actionRecord, access) >= (int)Poker::Character::length - 1) { //1�L�����ȊO�S�ăL�������������ꍇ�m�[�R���e�X�g��
					SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
					parent->run = parent->list[(int)Poker::Section::nocontest];
				}
			}
			parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������
		}
		return;
	}
	
	//�v���C���[�̏ꍇ
	if (count == 1) { //�v���C���[�ɑ��삪�ڂ����u�ԂȂ�Ίe��{�^����L��������
		for (auto itr : playerButton) { //�{�^���̃N���b�N���m�J�n�ƕ\�������o�� 
			itr->SetRunUpdate(true);
			itr->SetRunDraw(true);
		}
		gageControl->SetRunUpdate(true); //�Q�[�W�̑���󂯕t�����J�n����
	}
	Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::check; //����̃A�N�V�������L�^����A��芸����check������
	Cmp_BetActionRecord* record = actionRecord[access]; //���̃L�����̃x�b�g�L�^���擾
	int pay = playerGage->GetVol() * parent->dealer->GetMaxBet() * parent->dealer->GetBB(); //���݃Q�[�W�ɍ��킹���x���z
	int oldPay = parent->pot->Inquiry(*parent->chara[access]); //�O��܂ł̎x���z

	if (pay == parent->pot->GetCurrentMaxBet() && pay - oldPay != 0) { action = Cmp_BetActionRecord::Action::call; } //�x���z�����ݍő�x�b�g�Ɠ��l�������ꍇ�A�N�V������call�A�A���ŏI�x���z��0�ɂȂ�ꍇcheck
	if (pay > parent->pot->GetCurrentMaxBet()) { action = Cmp_BetActionRecord::Action::raise; } //�x���z�����ݍő�x�b�g�𒴂��Ă����ꍇ�A�N�V������raise
	pay -= oldPay; //�x���󋵂����������z�ɕύX
	
	if (parent->chara[access]->GetCoint() - pay < 0) { action = Cmp_BetActionRecord::Action::allIn; } //�x���z���������𒴂��Ă����ꍇAllIn

	actionButtonImage->SetAnimeSub((int)action); //�{�^���摜�����݂̃A�N�V�����̕��ɕύX
	for (auto itr : playerButton) { //�{�^�����`�F�b�N�������ꂽ�{�^�����������ꍇ�{�^���������ʋ@�\�����s����
		if (itr->GetRunDrawClick()) {
			record->SetIsAction(true); //�A�N�V�����ς݂ɐݒ�
			break; //�ǂꂩ1�ł������ꂽ����Ď��s����K�v�͂Ȃ��̂Ń��[�v����
		}
	}
	if (!record->GetIsAction()) { return; } //�A�N�V�����ς݂ɂ���ĂȂ��ꍇ�{�^����������ĂȂ��̂ňȍ~�̏����͔�΂�
	int endCount = ActionEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��

	if (actionButton->GetRunUpdateClick()) { //�A�N�V�����{�^���������ꂽ�ꍇ�̏���
		if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent->chara[access]); } //allIn�̏ꍇ�T�C�h�|�b�g��
		else if (action != Cmp_BetActionRecord::Action::check) { parent->pot->SetMainPot(pay, *parent->chara[access]); } //call,raise�������ꍇ���C���|�b�g��
		parent->chara[access]->SetCoin(parent->chara[access]->GetCoint() - pay); //����������x���z�����Z����

		if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y���Ă����ꍇ�S���̃A�N�V�����󋵂̌��������s��
			playerGageBorder->SetBorder((pay + oldPay) / parent->dealer->GetBB() * parent->dealer->GetMaxBet()); //�Q�[�W�̍Œ�l���X�V
			for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allIn�����Ă��Ȃ��ꍇ���A�N�V������ԂɍX�V����
		}
		record->SetActionRecord(action, true); //�Y���A�N�V�����𓮍�ς݂ɂ���
		record->SetIsAction(true); //���C�Y�����v���C���[�̃A�N�V�����͏I���ς݂ɐݒ肷��
		endCount = ActionEndCount(actionRecord, access); //endcount�̍X�V

		if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
			SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
			if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //�t�@�[�X�g�x�b�g�������ꍇ�����s����V�[�P���X�̓J�[�h����
			else { parent->run = parent->list[(int)Poker::Section::showdown]; } //�Z�J���h�x�b�g�Ȃ�V���[�_�E���ֈڍs����
		}
	}

	if (foldButton->GetRunUpdateClick()) { //fold�{�^���������ꂽ�ꍇ�̏���
		for (auto itr : *parent->chara[access]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //��D��fold�\���֕ύX
		record->SetActionRecord(Cmp_BetActionRecord::Action::fold, true); //fold�𓮍�ς݂ɂ���

		if (FoldCount(actionRecord, access) >= (int)Poker::Character::length - 1) { //1�L�����ȊO�S�ăL�������������ꍇ�m�[�R���e�X�g��
			SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
			parent->run = parent->list[(int)Poker::Section::nocontest];
		}
	}

	for (auto itr : playerButton) { //�{�^���̃N���b�N���m�I���ƕ\���B���A�N���b�N���̍폜���s��
		itr->SetRunUpdate(false); //�N���b�N���m�I��
		itr->SetRunDraw(false); //��\����
		itr->SetRunUpdateClick(false); //�N���b�N��Ԃ̃��Z�b�g
		itr->SetRunDrawClick(false);
	}

	parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������
	gageControl->SetRunUpdate(false); //�Q�[�W�̑���󂯕t�����I������
	count = 0; //�J�E���g���Z�b�g
}

Poker::Change::Change(Poker& set) :parent(&set), count(0), cpuWait(30), moveY(-48), border(CardDealer::CardPower::ten), isClick(std::deque<bool>()), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), actionButton(nullptr), cardButton(std::deque<Button*>()), cardPos(std::deque<Vector3*>()){
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

			int endCount = ActionEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
			if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
				SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
				parent->run = parent->list[(int)Poker::Section::main]; //�Z�J���h�x�b�g��
				((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);
			}
			parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������

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
			int start = 1; //hand�]����������J�[�h���o�����n�߂�ʒu
			switch ((CardDealer::HandRank)(hand[0] / (int)CardDealer::CardPower::max)) {
			case CardDealer::HandRank::No: start = 1; break;
			case CardDealer::HandRank::OnePair: start = 2; break;
			case CardDealer::HandRank::TwoPair: start = 3; break;
			case CardDealer::HandRank::ThreeCard: start = 2; break;
			case CardDealer::HandRank::FourCard: start = 2; break;
			default: start = hand.size(); break; //��L�n���h�łȂ��ꍇ�����͂��Ȃ�
			}

			//�������W�b�N�Ƀ~�X��������
			//922qq�̗l�ȏ󋵂�9���������Ȃ�����
			for (int i = start; i < hand.size(); ++i) {
				if (i == start && hand[start] >= (int)border) { continue; } //�J�n�ʒu(���ȊO�ň�ԋ����J�[�h)���w��ȏ�̋����������Ă��ꍇ���̃J�[�h�͎���Ă���
				for (auto itr : *parent->chara[access]->EditCard()) {
					if (itr->GetCard() % (int)CardDealer::CardPower::max == hand[i]) { changeList.push_back(itr); break; } //hand�ƈ�v����J�[�h�������J�[�h�Ƃ��ă��X�g�ɉ����鏈��
				}
			}
			for (auto itr : changeList) { 
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

		int endCount = ActionEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
		if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
			SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
			parent->run = parent->list[(int)Poker::Section::main]; //�Z�J���h�x�b�g��
			((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);
		}
		parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������

		actionButton->SetRunUpdate(false); //�{�^��������
		actionButton->SetRunDraw(false);
		actionButton->SetRunUpdateClick(false); //�N���b�N��Ԃ̃��Z�b�g
		actionButton->SetRunDrawClick(false);
		for (auto itr : cardButton) { itr->SetRunClickMonitor(false); } //�N���b�N���m�𖳌���

		count = 0; //�J�E���g���Z�b�g
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


Poker::ShowDown::ShowDown(Poker& set) :parent(&set), count(0), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), hand(std::deque<std::deque<int>>(4, std::deque<int>(5))), handPos(std::deque<Vector3>(4)), handString(std::deque<std::string>(4)) {
	titlePos.SetXYZ(513, 189, 0); //�V���[�_�E���ł��鎖���������b�Z�[�W�̈ʒu�ݒ�

	//��D����\������ׂ̈ʒu�ݒ�
	handPos[0].SetXYZ(108, 382, 0);
	handPos[1].SetXYZ(776, 31, 0);
	handPos[2].SetXYZ(1039, 377, 0);
	handPos[3].SetXYZ(497, 400, 0);

	

	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}






void Poker::ShowDown::Update() {
	
	if (count == 60) {
		for (int i = 0; i < actionRecord.size(); ++i) { //�e�L�������`�F�b�N�������D�����J���鏈��
			if (IsFold(*actionRecord[i])) { continue; } //�Q�[�����珜�O����Ă����ꍇ�ȉ������͎��s���Ȃ�
			for (auto itr : *parent->chara[i]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::front); } //�����܂ł��ꂽ�L�����̓J�[�h��\���\����
		}
	}

	if (count == 120) {
		for (int i = 0; i < parent->chara.size(); ++i) { //�n���h�]�����s��
			hand[i] = CardDealer::HandCheck(*parent->chara[i]); //�e�L�����̎�D�]��������
			handString[i] = Hand2String(hand[i]); //�e�L�����̊������𕶎��񉻂��������i�[
		}
	}

	if (count == 180) {
		std::deque<Chara*> enableChara= std::deque<Chara*>(); //�������s���L�����Z��
		std::deque<Chara*> foldChara = std::deque<Chara*>(); //�t�H�[���h�����L�����Z��(�s�k�ς݂͏���)

		std::deque<std::deque<int>> enableHand = std::deque<std::deque<int>>(); //�������s���L�����̃n���h�]���Z��

		for (int i = 0; i < parent->chara.size(); ++i) { //�L����������������L�����Afold�L�����A���O�L�����Ɏd������
			if (actionRecord[i]->GetIsLose()) { continue; } //�s�k�ς݂̏ꍇ�����������L�����ֈڍs
			if (actionRecord[i]->GetActionRecord(Cmp_BetActionRecord::Action::fold)) { foldChara.push_back(parent->chara[i]); continue; } //fold���Ă�ꍇfoldCara�֊i�[�����L�����ֈڍs
			enableChara.push_back(parent->chara[i]); //���݃L������enableChara�֊i�[
			enableHand.push_back(hand[i]); //���݃L�����̃n���h�]���i�[
		}


		while (enableChara.size() > 0) { //enableChara�S�ĂɎx�����I����܂Ŏ��s
			std::deque<int> max = std::deque<int>(1, 0); //����x�����s���L�����̓Y�����W�A��芸�����v�f��1�Ŋi�[�l��0

			for (int i = 1; i < enableChara.size(); ++i) { //��ԋ����������L���������肷��
				if (enableHand[max[0]][0] < enableHand[i][0]) { max = std::deque<int>(1, i); continue; } //����̖��̕��������ꍇ�x�����s���L����������̕��ɕύX
				if (enableHand[max[0]][0] == enableHand[i][0]) { max.push_back(i); } //�����������Ȃ獡��L�������x�����ΏۂƂ��Ĕz��ɒǉ�����
			}

			//�f�o�b�O�p
			//std::deque<int> max = std::deque<int>(); //����x�����s���L�����̓Y�����W�A��芸�����v�f��1�Ŋi�[�l��0
			//for (int i = 0; i < enableChara.size(); ++i) { max.push_back(i); }

			std::deque<int> copy = max; //max��ҏW����ׂ̃R�s�[
			if (copy.size() == 1) { //�v�f��1�����Ȃ��ꍇ
				enableChara[copy[0]]->SetCoin(enableChara[copy[0]]->GetCoint() + parent->pot->PayOut(*enableChara[copy[0]])); //�����z�����
				copy.erase(copy.begin()); //�v�f����
			}
			else { std::sort(copy.begin(), copy.end(), [=](int a, int b) { return parent->pot->Inquiry(*enableChara[copy[a]]) < parent->pot->Inquiry(*enableChara[copy[b]]); }); } //�x���z�̏����\�[�g

			while (copy.size() > 0) { //copy����ɂȂ�܂ő�����
				std::deque<Chara*> same = std::deque<Chara*>(1, enableChara[copy[0]]); //�x���z����̃L�����܂Ƃ�
				int pay = parent->pot->Inquiry(*same[0]); //����̎x���z
				for (int i = 1; i < copy.size(); ++i) { //����x���z�Ɠ���̃L�����T��
					if (pay == parent->pot->Inquiry(*enableChara[copy[i]])) { same.push_back(enableChara[copy[i]]); } //����Ȃ�z��֊i�[
				}

				pay = parent->pot->PayOut(*same[0]) / same.size(); //�x���������s�A����x���z�L�����̐��������z���𓙕�
				for (int i = 0; i < same.size(); ++i) { //����x���z�̊e�L�����֎x����
					same[i]->SetCoin(same[i]->GetCoint() + pay); //����x���z�̃L�����֔z��
					for (int j = 0; j < copy.size(); ++j) { //�x�������L������copy���珜�O����ׂ̃��[�v
						if (enableChara[copy[j]] == same[i]) { copy.erase(copy.cbegin() + j); break; } //����x�������L������copy���珜�O
					}
				}

			}

			if (parent->pot->TotalAmount() <= 0) { ++count; return; } //�x�����̌��ʃ|�b�g�����z��0�ɂȂ����ꍇ���̎��_�ŏI���

			std::deque<Chara*> maxChara = std::deque<Chara*>(); //max�����enableChara������o��������ێ�����z��
			for (int i = 0; i < max.size(); ++i) { maxChara.push_back(enableChara[max[i]]); } //maxChara�֑Ή�Chara�Q�Ƃ��i�[


			for (int i = 0; i < maxChara.size(); ++i) { //����x���z�̊e�L�����֎x����
				for (int j = 0; j < enableChara.size(); ++j) { //�x�������L������copy���珜�O����ׂ̃��[�v
					if (enableChara[j] == maxChara[i]) { //enableChara���̂ǂ̗v�f���g���������肷��
						enableChara.erase(enableChara.begin() + j); //�Ή��v�f��enable���珜�O
						enableHand.erase(enableHand.begin() + j); //hand�̕��������Ă���
						break; 
					}
				}
			}
			FoldMemberPayOut(foldChara, *parent->pot); //�]����pot��fold�L�����֕��z
		}
		
	}

	if (count == 240) {
		parent->run = parent->list[(int)Poker::Section::ini]; //�ŏ��̏�Ԃɖ߂�
		count = -1; //�J�E���g���Z�b�g
	}

	++count;
}

void Poker::ShowDown::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "�V���[�_�E��!!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));

	if (count >= 120) {
		for (int i = 0; i < actionRecord.size(); ++i) { //�����ɒ��񂾃L�����̃n���h��\������
			if (IsFold(*actionRecord[i])) { continue; } //�Q�[�����珜�O����Ă����ꍇ�ȉ������͎��s���Ȃ�
			DrawStringToHandle(handPos[i].GetX(), handPos[i].GetY(), handString[i].c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal)); //�n���h�\��
		}
	}


}


Poker::NoContest::NoContest(Poker& set) :parent(&set), count(0), payOutTime(60), clickStartTime(120), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	titlePos.SetXYZ(513, 189, 0); //�m�[�R���e�X�g�ł��鎖���������b�Z�[�W�̈ʒu�ݒ�
	explainPos.SetXYZ(484, 312, 0); //�{�^�������z�u�ʒu

	nextButton.SetClick(new Cmp_Button_ClickCheck()); //�N���b�N�`�F�b�N�p�R���|�[�l���g�ǉ�

	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}

void Poker::NoContest::Update() {
	nextButton.Update(); //�{�^��Update���s

	if (count == payOutTime) {
		Chara* enableChara = nullptr; //�~��Ȃ������L����������
		std::deque<Chara*> foldChara = std::deque<Chara*>(); //�t�H�[���h�����L�����Z��(�s�k�ς݂͏���)

		for (int i = 0; i < parent->chara.size(); ++i) { //�L����������������L�����Afold�L�����A���O�L�����Ɏd������
			if (actionRecord[i]->GetIsLose()) { continue; } //�s�k�ς݂̏ꍇ�����������L�����ֈڍs
			if (actionRecord[i]->GetActionRecord(Cmp_BetActionRecord::Action::fold)) { foldChara.push_back(parent->chara[i]); continue; } //fold���Ă�ꍇfoldCara�֊i�[�����L�����ֈڍs
			enableChara = parent->chara[i]; //���݃L������enableChara�֊i�[
			break; //�L���L������1�l�����Ȃ̂ł����܂ł��ꂽ��I���
		}
		enableChara->SetCoin(enableChara->GetCoint() + parent->pot->PayOut(*enableChara)); //���z�����
		if (parent->pot->TotalAmount() <= 0) { ++count; return; } //���z���Ȃ��Ȃ�ΏI���
		FoldMemberPayOut(foldChara, *parent->pot); //�]���Ă����fold�L�����֕��z

	}

	if (count == clickStartTime) { //�N���b�N���m�J�n�^�C�~���O�ɂȂ�����

		//���f�o�b�O
		//LoseSet(parent->chara, actionRecord); //�s�k�󋵂̐ݒ�
		//Poker::Section next = GameEndCheck(parent->chara, actionRecord); //�s�k�󋵂��玟�������ׂ��V�[�����擾

		//if (next != Poker::Section::ini) { //ini(���s���ׂ�)�ȊO���������ꍇ
		//	parent->run = parent->list[(int)next]; //���̃V�[���Ɉڍs
		//	count = -1; //�J�E���g���Z�b�g
		//	return; //�I���
		//}

		nextButton.SetRunClickMonitor(true); //�N���b�N���m�J�n
	}

	if (nextButton.GetRunUpdateClick()) { //�N���b�N���ꂽ�ꍇ
		parent->run = parent->list[(int)Poker::Section::ini]; //�ŏ��̏�Ԃɖ߂�

		nextButton.SetRunUpdate(false); //�N���b�N��Ԃ�߂�
		nextButton.SetRunDraw(false); //�O�̈�Draw���߂�
		nextButton.SetRunClickMonitor(false); //�N���b�N���m�̖�����
		count = -1; //�J�E���g���Z�b�g
	}

	++count;
}

void Poker::NoContest::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "�m�[�R���e�X�g!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "��ʂ��N���b�N�Ŏ��Q�[����", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}


Poker::GameOver::GameOver(Poker& set) :parent(&set), count(0), clickStartTime(60), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false) {
	titlePos.SetXYZ(513, 189, 0); //�m�[�R���e�X�g�ł��鎖���������b�Z�[�W�̈ʒu�ݒ�
	explainPos.SetXYZ(432, 312, 0); //�{�^�������z�u�ʒu

	nextButton.SetClick(new Cmp_Button_ClickCheck()); //�N���b�N�`�F�b�N�p�R���|�[�l���g�ǉ�
}

void Poker::GameOver::Update() {
	nextButton.Update(); //�{�^��Update���s
	if (count == clickStartTime) { nextButton.SetRunClickMonitor(true); } //�J�n�^�C�~���O�ɂȂ�����N���b�N���m�J�n

	if (nextButton.GetRunUpdateClick()) { //�N���b�N���ꂽ�ꍇ
		FullReset(parent->chara, *parent->pot, *parent->dealer, *parent->cardDealer); //�V�����Q�[���̏���������
		parent->run = parent->list[(int)Poker::Section::pre]; //�ŏ��̏�Ԃɖ߂�

		nextButton.SetRunUpdate(false); //�N���b�N��Ԃ�߂�
		nextButton.SetRunDraw(false); //�O�̈�Draw���߂�
		nextButton.SetRunClickMonitor(false); //�N���b�N���m�̖�����
		count = -1; //�J�E���g���Z�b�g
	}

	++count;
}

void Poker::GameOver::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "�Q�[���I�[�o�[!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "��ʂ��N���b�N�ŐV�����n�߂�", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}
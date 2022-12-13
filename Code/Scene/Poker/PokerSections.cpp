#include "../Scene.h"
#include "Poker.h"
#include "PokerSections.h"

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
#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"

#include <deque>
#include <typeinfo>

void Poker::Ini::Update() {
	parent->pot->Reset();
	parent->dealer->Reset();
	parent->cardDealer->Reset();
	for (auto chara : parent->chara) { chara->Reset(); }

	parent->run = parent->list[(int)Poker::Section::pre];
}

void Poker::Pre::Update() {
	for (auto itr : parent->chara) {
		for (auto card : *itr->EditCard()) { card->SetCard(parent->cardDealer->DeckDraw()); } //�R�D��������Ă����J�[�h����D�ɐݒ�
		if (typeid(*itr) == typeid(CPU)) { //���̃L������cpu�������ꍇ
			(itr->EditCmp<Cmp_CPUBetLogic>())->RaiseVolDecision(*itr, true); //���ݎ�D���烌�C�Y���ƕ����A���僌�C�Y���邩�ǂ��������肷��
		}
		else { //�v���C���[�������ꍇ
			for (auto card : *itr->EditCard()) { card->SetVisible(true); } //�J�[�h���������Ă��� 
		}
	}
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
	playerGagePayDraw = parent->chara[(int)Poker::Character::player]->EditCmp<Cmp_PlayerRaiseDraw>(); //


	playerGage = parent->chara[(int)Poker::Character::player]->EditCmp<Gage>(); //�Q�[�W���o��
	playerGageBorder = playerGage->EditCmp<Cmp_Gage_Border>(); //�Q�[�W����e��@�\�����o��
	gageControl = playerGage->EditCmp<Cmp_Gage_MouseControl>();
}

Cmp_BetActionRecord::Action ActionDecision(Cmp_CPUBetLogic* betLogic) { //�����ꂽbetLogic�ɂ����raise���ׂ���call���ׂ����Ԃ�
	return betLogic->GetSelfRaise() ? Cmp_BetActionRecord::Action::raise : Cmp_BetActionRecord::Action::call;
}

bool BetIgnore(Cmp_BetActionRecord* record) { //�L�����̃A�N�V�����L�^��n�����ł��̃L�����̃x�b�g���X�L�b�v���ׂ����ۂ��Ԃ��Atrue�ŃX�L�b�v
	return record->GetActionRecord(Cmp_BetActionRecord::Action::allIn) || record->GetActionRecord(Cmp_BetActionRecord::Action::fold) || record->GetIsLoose(); //allIn�AFold�A�s�k�ς݂̏ꍇ�x�b�g���X�L�b�v
}

int FoldCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //�Q�[�����甲�����L��������Ԃ��Acenter��record�֎g�p����Y����������Ƃ��̃L�����𒆐S�Ƀ`�F�b�N����
	int dropCount = 1; //���̃��E���h���甲�����L�������L�^����
	for (dropCount; dropCount < (int)Poker::Character::length; ++dropCount) {
		Cmp_BetActionRecord current = *actionRecord[(center + dropCount) % (int)Poker::Character::length]; //����`�F�b�N����L�����A���̃A�N�Z�X�V���[�g�J�b�g
		if (!(current.GetActionRecord(Cmp_BetActionRecord::Action::fold) || current.GetIsLoose() || current.GetIsAction())) { break; } //�`�F�b�N�L�������I��������1�ɂ�����������Ȃ������ꍇ���f
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

void RaiseCalculation(const std::deque<int>& split, int& runCount, int& pay, int betRequest, int BB, int coin) {
	//���E���h���ł̑��x���z�ƕ������C�Y�������܂Ŏg������Ԃ��Asplit�ɕ������C�Y�f�[�^�ArunCount��split�ǂݏo���J�n�ʒu��(�ҏW�����A���̓ǂݏo���J�n�ʒu�܂ňړ������)�Apay�Ɏx�����z�AbetRequest�Ɍ��ݍő�x�b�g���ABB�Ɍ���BB���Acoin�ɏ�����������
	for (runCount; runCount < split.size();) { //�x���z�����݃x�b�g������悤�������C�Y�𒲐��g�p���鏈��
		int nowPayMent = split[runCount] * BB; //�����split�x���z
		if (coin - (pay + nowPayMent) < 0) { break; } //���C�Y�ŏ�������0�����ɂ��Ă��܂��ꍇ���񕪂͎g�킸�I��

		pay += nowPayMent; //���񕪂̎x���z��������
		++runCount; //runCount��i�߂�A���̃^�C�~���O�Ŏ��s���鎖�ɈӖ�������
		if (pay > betRequest) { break; } //���݂̕������Ńx�b�g�ő�𒴂�����I��
	}
}

void SequenceNextReset(const std::deque<Cmp_BetActionRecord*>& chara) { //���V�[�P���X�ֈڍs����ێ��s����A�N�V�����L�^���Z�b�g�p�֐�
	for (auto itr : chara) {
		itr->SetActionRecord(Cmp_BetActionRecord::Action::check, false); //allIn��Loose�ȊO�̃A�N�V���������Z�b�g
		itr->SetActionRecord(Cmp_BetActionRecord::Action::call, false);
		itr->SetActionRecord(Cmp_BetActionRecord::Action::raise, false);
		itr->SetIsAction(false); //�A�N�V���������s��Ԃɖ߂�
	}
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


			int betRequest = parent->dealer->GetCurrentMaxBet() * parent->dealer->GetBB(); //���ݍő�x�b�g���z
			int oldPay = parent->pot->Inquiry(*parent->chara[access]); //���̃L�����̑O��܂ł̎x���z
			int pay = betRequest - oldPay; //�x�����z


			Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::fold; //���s���ׂ��A�N�V�������i�[
			if (raise > parent->dealer->GetCurrentMaxBet()) { action = ActionDecision(betData); } //���ݍő�x�b�g�����C�Y�\�z�𒴂��Ă��Ȃ���΃��C�Y�A�R�[������
			if (record->GetRaiseRunCount() > 0 && raise * 5 > parent->dealer->GetCurrentMaxBet()) { action = ActionDecision(betData); } //1�x���C�Y�������Ƃ�����ꍇ���C�Y�\�z��5�{�܂ł̓��C�Y���󂯂�
			if (parent->chara[access]->GetCoint() - betRequest < 0) { action = Cmp_BetActionRecord::Action::allIn; } //�R�[������ł��Ȃ��������Ȃ�I�[���C���ɂȂ�

			if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y�̗�O��e������
				if (raise <= parent->dealer->GetCurrentMaxBet()) { action == Cmp_BetActionRecord::Action::call; } //���C�Y�����̏ꍇ�ł��v���z�����C�Y�\�񐔂𒴂��Ă����ꍇ�R�[���ɂȂ�
				if (record->GetRaiseRunCount() >= betData->ReadRaiseSplit()->size()) { action == Cmp_BetActionRecord::Action::call; } //���C�Y�\�z�S�Ă��g���؂��Ă����ꍇ�R�[���ɂȂ�
			}
			
			if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y�z�o������
				int runCount = record->GetRaiseRunCount(); //�����split�ǂݏo���J�n�ʒu������
				RaiseCalculation(*betData->ReadRaiseSplit(), runCount, pay, betRequest, parent->dealer->GetBB(), parent->chara[access]->GetCoint());

				record->SetRaiseRunCount(runCount); //�g�p�ςݕ��������L�^����
				if (pay <= betRequest) { //�������̓s���Ō��݃x�b�g�𒴂����x�b�g���ł��Ȃ��ꍇcall�ɂ���
					action == Cmp_BetActionRecord::Action::call; //call�ɂ���
					pay = betRequest - oldPay; //�x�������R�[���z�ɍ��킹��
				} else { pay -= oldPay; } //���ʂɃ��C�Y�ł���ΑO�񕪂���菜���ă��C�Y�z�Ƃ���
			}
			if (action == Cmp_BetActionRecord::Action::call && pay == 0) { action = Cmp_BetActionRecord::Action::check; } //�w��A�N�V������call�ŋ��z�x�������s�v�̏ꍇ�`�F�b�N�ɂȂ�


			record->SetActionRecord(action, true); //�Y���A�N�V�����𓮍�ς݂ɂ���
			record->SetIsAction(true); //�A�N�V�����ς݂ɐݒ�
			if (action == Cmp_BetActionRecord::Action::call || action == Cmp_BetActionRecord::Action::raise) { parent->pot->SetMainPot(pay, *parent->chara[access]); } //call�Araise�̏ꍇ���C���|�b�g��
			if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent->chara[access]); } //allIn�̏ꍇ�T�C�h�|�b�g��
			parent->chara[access]->SetCoin(parent->chara[access]->GetCoint() - pay); //����������x���z�����Z����

			if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y���Ă����ꍇ�S���̃A�N�V�����󋵂̌��������s��
				for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allIn�����Ă��Ȃ��ꍇ���A�N�V������ԂɍX�V����
				playerGageBorder->SetBorder(((pay + oldPay) / parent->dealer->GetBB()) / parent->dealer->GetMaxBet()); //�Q�[�W�̍Œ�l���X�V
			}

			
			
			int endCount = ActionEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
			if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
				SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
				if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //�t�@�[�X�g�x�b�g�������ꍇ�����s����V�[�P���X�̓J�[�h����
				else { parent->run = parent->list[(int)Poker::Section::showdown]; } //�Z�J���h�x�b�g�Ȃ�V���[�_�E���ֈڍs����
			}
			if (action == Cmp_BetActionRecord::Action::fold) { //�t�H�[���h�����ꍇ���E���h���f�`�F�b�N���s��
				if (FoldCount(actionRecord, access) >= (int)Poker::Character::length - 1) { //1�L�����ȊO�S�ăL�������������ꍇ�m�[�R���e�X�g��
					SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
					parent->run = parent->list[(int)Poker::Section::nocontest];
				}
			}
			parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������
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
	int pay = playerGage->GetVol() * parent->dealer->GetBB() - parent->pot->Inquiry(*parent->chara[access]); //���݃Q�[�W�Ǝx���󋵂Ɋ�Â����x���z

	if (pay == parent->dealer->GetBB()) { action = Cmp_BetActionRecord::Action::call; } //�x���z��BB�Ɠ��l�������ꍇ�A�N�V������call
	if (pay > parent->dealer->GetBB()) { action = Cmp_BetActionRecord::Action::raise; } //�x���z��BB�𒴂��Ă����ꍇ�A�N�V������raise
	if (parent->chara[access]->GetCoint() - pay < 0) { action = Cmp_BetActionRecord::Action::allIn; } //�x���z���������𒴂��Ă����ꍇAllIn


	for (auto itr : playerButton) { //�{�^�����`�F�b�N�������ꂽ�{�^�����������ꍇ�{�^���������ʋ@�\�����s����
		if (itr->GetRunDrawClick()) {
			record->SetActionRecord(action, true); //�Y���A�N�V�����𓮍�ς݂ɂ���
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

		if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
			SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
			if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //�t�@�[�X�g�x�b�g�������ꍇ�����s����V�[�P���X�̓J�[�h����
			else { parent->run = parent->list[(int)Poker::Section::showdown]; } //�Z�J���h�x�b�g�Ȃ�V���[�_�E���ֈڍs����
		}
	}

	if (foldButton->GetRunUpdateClick()) { //fold�{�^���������ꂽ�ꍇ�̏���
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
	gageControl->SetRunUpdate(false); //�Q�[�W�̑���󂯕t�����I������
	parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������
	count = 0; //�J�E���g���Z�b�g
}

Poker::Change::Change(Poker& set) :parent(&set), count(0), cpuWait(30), moveY(-48), border(CardDealer::CardPower::ten), isClick(std::deque<bool>()), actionRecord(std::deque<Cmp_BetActionRecord*>()), actionButton(nullptr), cardButton(std::deque<Button*>()) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
	
	std::deque<Button*> playerButton = std::deque<Button*>();
	Button* fold = nullptr; //�{�^�������̍ۂ�fold�{�^���i�[�p�A�����fold�͎g��Ȃ��̂Ń��[�J���ϐ�
	parent->chara[(int)Poker::Character::player]->EditCmpMulti<Button>(playerButton); //�{�^�����o��
	PlayerButtonAnalyze(playerButton, &actionButton, &fold); //�{�^���z���action��fold�ɕ����i�[

	for (auto itr : *parent->chara[(int)Poker::Character::player]->EditCard()) { cardButton.push_back(itr->EditCmp<Button>()); } //�v���C���[�̃J�[�h������͎�t�p�{�^�����擾
	
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
	if (count == 0) {
		for (auto itr : cardButton) { itr->SetRunClickMonitor(true); } //�N���b�N���m���J�n����
	}


}
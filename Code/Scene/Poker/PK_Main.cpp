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

#include "../Code/Component/ComponentArray.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"



Poker::Main::Main(Poker& set) :parent(&set), phase(0), count(0), cpuWait(30), actionRecord(std::deque<Cmp_BetActionRecord*>(4)), betLogic(std::deque<Cmp_CPUBetLogic*>(3)), playerButton(std::deque<Button*>()), actionButton(nullptr), foldButton(nullptr), playerGage(nullptr), playerGageBorder(nullptr), gageControl(nullptr), actionButtonImage(nullptr) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
	for (int i = 0; i < betLogic.size(); ++i) { betLogic[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_CPUBetLogic>(); } //�x�b�g���W�b�N���o���Achara�z��̕��я���player�Ō�ɂȂ��Ă�̂ł���œ����A�s���Ȃ�if����player�`�F�b�N���Ă�����
	parent->chara[(int)Poker::Character::player]->EditAppendCmp()->EditCmpMulti<Button>(playerButton); //�{�^�����o��
	PlayerButtonAnalyze(playerButton, &actionButton, &foldButton); //�{�^���z���action��fold�ɕ����i�[
	actionButtonImage = actionButton->EditAlwaysCmp<Cmp_Image>(); //�A�N�V�����p�{�^���̉摜�����o��


	playerGage = parent->chara[(int)Poker::Character::player]->EditAppendCmp()->EditCmp<Gage>(); //�Q�[�W���o��
	playerGageBorder = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_Border>(); //�Q�[�W����e��@�\�����o��
	playerGageUpper = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_UpperBorder>(); //�v���C���[�Q�[�W�������ݒ�@�\�̎��o��
	gageControl = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_MouseControl>();
}

void Poker::Main::Update() {
	++count;
	int access = parent->dealer->GetActionCharaSub(); //����A�N�V�������s���L�����ւ̓Y�������L�^����A�N�Z�X�V���[�g�J�b�g
	if (typeid(*parent->chara[access]) == typeid(CPU)) { //�A�N�V�����L������cpu�̏ꍇ

		if (count > cpuWait) { //�w��ҋ@���Ԃ𒴂����ꍇ���s�A�N�V���������肷��
			count = 0; //�J�E���g���Z�b�g

			Cmp_BetActionRecord* record = actionRecord[access]; //���̃L�����̃x�b�g�L�^���擾
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
			if (action == Cmp_BetActionRecord::Action::raise && record->GetRaiseRunCount() >= betData->ReadRaiseSplit()->size()) { action = Cmp_BetActionRecord::Action::call; } //���C�Y�\�z�S�Ă��g���؂��Ă����ꍇ�R�[���ɂȂ�


			if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y�z�o������
				int runCount = record->GetRaiseRunCount(); //�����split�ǂݏo���J�n�ʒu������
				int raiseAdd = RaiseCalculation(*betData->ReadRaiseSplit(), runCount, oldPay, betRequest, parent->dealer->GetBB(), parent->chara[access]->GetCoint()); //���C�Y�ɂ�鑝���𓾂�

				record->SetRaiseRunCount(runCount); //�g�p�ςݕ��������L�^����
				if (raiseAdd <= 0) { action = Cmp_BetActionRecord::Action::call; } //���C�Y���Ă��͂��Ȃ������菊�����̖��Ŏw�蕪���C�Y�ł��Ȃ������ꍇcall�ɂ���
				else { pay += raiseAdd; } //���ʂɃ��C�Y�ł���Α�����������
			}
			if (action == Cmp_BetActionRecord::Action::call && pay == 0) { action = Cmp_BetActionRecord::Action::check; } //�w��A�N�V������call�ŋ��z�x�������s�v�̏ꍇ�`�F�b�N�ɂȂ�
			if (parent->chara[access]->GetCoint() - pay <= 0) { //�x���z���������ȏ�ɂȂ�ꍇ
				action = Cmp_BetActionRecord::Action::allIn; //allIn�ɂȂ�
				pay = parent->chara[access]->GetCoint(); //�x���z���������ɍ��킹��
			}


			record->SetActionRecord(action, true); //�Y���A�N�V�����𓮍�ς݂ɂ���
			record->SetIsAction(true); //�A�N�V�����ς݂ɐݒ�

			if (action == Cmp_BetActionRecord::Action::call || action == Cmp_BetActionRecord::Action::raise) { parent->pot->SetMainPot(pay, *parent->chara[access]); } //call�Araise�̏ꍇ���C���|�b�g��
			if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent->chara[access]); } //allIn�̏ꍇ�T�C�h�|�b�g��
			if (action != Cmp_BetActionRecord::Action::fold) { parent->chara[access]->SetCoin(parent->chara[access]->GetCoint() - pay); } //fold�ȊO�̏ꍇ����������x���z�����Z����(check�̏ꍇpay��0�Ȃ̂Œe���K�v�Ȃ�)

			if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y���Ă����ꍇ�S���̃A�N�V�����󋵂̌��������s��
				for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allIn�����Ă��Ȃ��ꍇ���A�N�V������ԂɍX�V����
				playerGageBorder->SetBorder((float)(pay + oldPay) / (parent->dealer->GetBB() * parent->dealer->GetMaxBet())); //�Q�[�W�̍Œ�l���X�V
				record->SetIsAction(true); //���C�Y�����L�����̃A�N�V�����͏I���ς݂ɐݒ肷��
			}
			int endCount = ActionEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
			parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������

			if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
				SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
				parent->dealer->SetActionChara((ChangeEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //change��allIn�����L�������A�N�V�����ΏۂȂ̂Ŏ���L�����̐ݒ�Ɋ܂߂�

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
	int pay = std::round(playerGage->GetVol() * parent->dealer->GetMaxBet() * parent->dealer->GetBB()); //���݃Q�[�W�ɍ��킹���x���z
	int oldPay = parent->pot->Inquiry(*parent->chara[access]); //�O��܂ł̎x���z

	if (pay == parent->pot->GetCurrentMaxBet() && pay - oldPay != 0) { action = Cmp_BetActionRecord::Action::call; } //�x���z�����ݍő�x�b�g�Ɠ��l�������ꍇ�A�N�V������call�A�A���ŏI�x���z��0�ɂȂ�ꍇcheck
	if (pay > parent->pot->GetCurrentMaxBet()) { action = Cmp_BetActionRecord::Action::raise; } //�x���z�����ݍő�x�b�g�𒴂��Ă����ꍇ�A�N�V������raise
	pay -= oldPay; //�x���󋵂����������z�ɕύX

	if (parent->chara[access]->GetCoint() - pay <= 0) { action = Cmp_BetActionRecord::Action::allIn; } //�x���z���������𒴂��Ă����ꍇAllIn

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
			playerGageBorder->SetBorder((float)(pay + oldPay) / (parent->dealer->GetBB() * parent->dealer->GetMaxBet())); //�Q�[�W�̍Œ�l���X�V
			for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allIn�����Ă��Ȃ��ꍇ���A�N�V������ԂɍX�V����
		}
		record->SetActionRecord(action, true); //�Y���A�N�V�����𓮍�ς݂ɂ���
		record->SetIsAction(true); //���C�Y�����v���C���[�̃A�N�V�����͏I���ς݂ɐݒ肷��
		endCount = ActionEndCount(actionRecord, access); //endcount�̍X�V
	}
	parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������


	if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
		SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
		parent->dealer->SetActionChara((ChangeEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //change��allIn�����L�������A�N�V�����ΏۂȂ̂Ŏ���L�����̐ݒ�Ɋ܂߂�

		if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //�t�@�[�X�g�x�b�g�������ꍇ�����s����V�[�P���X�̓J�[�h����
		else { parent->run = parent->list[(int)Poker::Section::showdown]; } //�Z�J���h�x�b�g�Ȃ�V���[�_�E���ֈڍs����
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

	gageControl->SetRunUpdate(false); //�Q�[�W�̑���󂯕t�����I������
	count = 0; //�J�E���g���Z�b�g
}

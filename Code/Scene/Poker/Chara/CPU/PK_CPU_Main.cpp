#include "PK_Chara.h"
#include "PK_CPU.h"
#include "PK_CPU_Main.h"

#include "PK_Pot.h"
#include "PK_Dealer.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_Transform.h"
#include "Cmp_PK_Chara_SE.h"
#include "Cmp_Sound.h"

#include "PK_SectionLibrary.h"

#include <deque>

void PK_CPU::Main::Update() {
	++count;
	if (count > waitTime) { //�w��ҋ@���Ԃ𒴂����ꍇ���s�A�N�V���������肷��
		count = 0; //�J�E���g���Z�b�g

		int raise = 0; //���̃L�����̃��C�Y�\��
		for (auto itr : *parent->betData->ReadRaiseSplit()) { raise += itr; } //�������ꂽ���C�Y�\�񐔂���ɓZ�߂�
		raise *= parent->dealer->GetBB(); //����BB�����C�Y�\�񐔂Ɋ|���ă��C�Y�\�z�ɕύX����

		int betRequest = parent->pot->GetCurrentMaxBet(); //���ݍő�x�b�g���z
		int oldPay = parent->pot->Inquiry(*parent); //���̃L�����̑O��܂ł̎x���z
		int pay = betRequest - oldPay; //�x�����z


		Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::fold; //���s���ׂ��A�N�V�������i�[
		if (raise > betRequest) { action = ActionDecision(parent->betData); } //���ݍő�x�b�g�����C�Y�\�z�𒴂��Ă��Ȃ���΃��C�Y�A�R�[������
		if (parent->record->GetRaiseRunCount() > 0 && raise * 5 > parent->pot->GetCurrentMaxBet()) { action = ActionDecision(parent->betData); } //1�x���C�Y�������Ƃ�����ꍇ���C�Y�\�z��5�{�܂ł̓��C�Y���󂯂�
		if (action == Cmp_BetActionRecord::Action::raise && parent->record->GetRaiseRunCount() >= parent->betData->ReadRaiseSplit()->size()) { action = Cmp_BetActionRecord::Action::call; } //���C�Y�\�z�S�Ă��g���؂��Ă����ꍇ�R�[���ɂȂ�


		if (action == Cmp_BetActionRecord::Action::raise) { //���C�Y�z�o������
			int runCount = parent->record->GetRaiseRunCount(); //�����split�ǂݏo���J�n�ʒu������
			int raiseAdd = RaiseCalculation(*parent->betData->ReadRaiseSplit(), runCount, oldPay, betRequest, parent->dealer->GetBB(), parent->GetCoint()); //���C�Y�ɂ�鑝���𓾂�

			parent->record->SetRaiseRunCount(runCount); //�g�p�ςݕ��������L�^����
			if (raiseAdd <= 0) { action = Cmp_BetActionRecord::Action::call; } //���C�Y���Ă��͂��Ȃ������菊�����̖��Ŏw�蕪���C�Y�ł��Ȃ������ꍇcall�ɂ���
			else { pay += raiseAdd; } //���ʂɃ��C�Y�ł���Α�����������
		}
		if (action == Cmp_BetActionRecord::Action::call && pay == 0) { action = Cmp_BetActionRecord::Action::check; } //�w��A�N�V������call�ŋ��z�x�������s�v�̏ꍇ�`�F�b�N�ɂȂ�
		if (parent->GetCoint() - pay <= 0) { //�x���z���������ȏ�ɂȂ�ꍇ
			action = Cmp_BetActionRecord::Action::allIn; //allIn�ɂȂ�
			pay = parent->GetCoint(); //�x���z���������ɍ��킹��
		}

		parent->record->SetActionRecord(action, true); //�Y���A�N�V�����𓮍�ς݂ɂ���
		parent->record->SetFinalAction(action); //�Y���A�N�V�������ŏI�A�N�V�����ɂ���
		parent->record->SetIsAction(true); //�A�N�V�����ς݂ɐݒ�

		Cmp_PK_Chara_SE::Request request = Cmp_PK_Chara_SE::Request::call; //�炷se�̎w�����i�[
		if (action == Cmp_BetActionRecord::Action::raise || action == Cmp_BetActionRecord::Action::allIn) { request = Cmp_PK_Chara_SE::Request::raise; } //raise����allIn���Ă����raise�����w��
		if (action == Cmp_BetActionRecord::Action::fold) { request = Cmp_PK_Chara_SE::Request::fold; } //fold�����w��
		if (action != Cmp_BetActionRecord::Action::check) { parent->se->ReadSE(request)->Play(); } //check�ȊO�Ȃ�w�肳�ꂽ����炷
		

		if (action == Cmp_BetActionRecord::Action::call || action == Cmp_BetActionRecord::Action::raise) { parent->pot->SetMainPot(pay, *parent); } //call�Araise�̏ꍇ���C���|�b�g��
		if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent); } //allIn�̏ꍇ�T�C�h�|�b�g��
		if (action != Cmp_BetActionRecord::Action::fold) { parent->SetCoin(parent->GetCoint() - pay); } //fold�ȊO�̏ꍇ����������x���z�����Z����(check�̏ꍇpay��0�Ȃ̂Œe���K�v�Ȃ�)

		return; //�I���
	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //�A�N�V���������s���ĂȂ��̂�noAction��ݒ�

}

#include "PK_Player.h"
#include "PK_Player_Main.h"

#include "PK_CardDealer.h"
#include "PK_Chara.h"
#include "PK_Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"

#include "Button.h"
#include "Gage.h"
#include "Cmp_Gage_ControlSound.h"
#include "Cmp_Button_ClickCheck.h"
#include "Cmp_Gage_MouseControl.h"
#include "Cmp_Image.h"
#include "Cmp_PK_Chara_SE.h"
#include "Cmp_Sound.h"

#include <deque>

void PK_Player::Main::Update() {
	++count;
	if (count == 1) { //�v���C���[�ɑ��삪�ڂ����u�ԂȂ�Ίe��{�^����L��������
		parent->actionButton->SetRunUpdateDraw(true, true); //�{�^���̃N���b�N���m�J�n�ƕ\�������o�� 
		parent->foldButton->SetRunUpdateDraw(true, true);
		parent->actionButton->EditClick()->SetRunUpdateBundle(true); //�N���b�N�ǉ��@�\��Update���s��������

		parent->gageControl->SetRunUpdate(true); //�Q�[�W�̑���󂯕t�����J�n����
		parent->gageSound->SetSoundStop(false); //�Q�[�W���쉹��L��������
	}


	Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::check; //����̃A�N�V�������L�^����A��芸����check������
	int pay = std::round(parent->gage->GetVol() * parent->dealer->GetMaxBet() * parent->dealer->GetBB()); //���݃Q�[�W�ɍ��킹���x���z
	int oldPay = parent->pot->Inquiry(*parent); //�O��܂ł̎x���z

	if (pay == parent->pot->GetCurrentMaxBet() && pay - oldPay != 0) { action = Cmp_BetActionRecord::Action::call; } //�x���z�����ݍő�x�b�g�Ɠ��l�������ꍇ�A�N�V������call�A�A���ŏI�x���z��0�ɂȂ�ꍇcheck
	if (pay > parent->pot->GetCurrentMaxBet()) { action = Cmp_BetActionRecord::Action::raise; } //�x���z�����ݍő�x�b�g�𒴂��Ă����ꍇ�A�N�V������raise
	pay -= oldPay; //�x���󋵂����������z�ɕύX

	if (parent->GetCoint() - pay <= 0) { action = Cmp_BetActionRecord::Action::allIn; } //�x���z���������𒴂��Ă����ꍇAllIn

	parent->actionButtonImage->SetAnimeSub((int)action); //�{�^���摜�����݂̃A�N�V�����̕��ɕύX

	if (parent->actionButton->GetRunUpdateClick()) { //�A�N�V�����{�^���������ꂽ�ꍇ�̏���
		if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent); } //allIn�̏ꍇ�T�C�h�|�b�g��
		else if (action != Cmp_BetActionRecord::Action::check) { parent->pot->SetMainPot(pay, *parent); } //call,raise�������ꍇ���C���|�b�g��
		parent->SetCoin(parent->GetCoint() - pay); //����������x���z�����Z����

		parent->record->SetActionRecord(action, true); //�Y���A�N�V�����𓮍�ς݂ɂ���
		parent->record->SetIsAction(true); //���C�Y�����v���C���[�̃A�N�V�����͏I���ς݂ɐݒ肷��

		if (action != Cmp_BetActionRecord::Action::check) { parent->se->ReadSE(Cmp_PK_Chara_SE::Request::call)->Play(); } //check�ȊO�Ȃ�x�b�g����炷
		if (action == Cmp_BetActionRecord::Action::raise || action == Cmp_BetActionRecord::Action::allIn) { parent->se->ReadSE(Cmp_PK_Chara_SE::Request::raise)->Play(); } //raise����allIn���Ă���ΑΉ���������炷
	}
	if (parent->foldButton->GetRunUpdateClick()) { //fold�{�^���������ꂽ�ꍇ�̏���
		action = Cmp_BetActionRecord::Action::fold; //���s�A�N�V������fold�ɃZ�b�g
		for (auto itr : *parent->EditHand()->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //��D��fold�\���֕ύX
		parent->record->SetActionRecord(action, true); //fold�𓮍�ς݂ɂ���
		parent->record->SetIsAction(true); //�A�N�V�����ς݂ɐݒ�

		parent->se->ReadSE(Cmp_PK_Chara_SE::Request::fold)->Play(); //fold����炷
	}
	if (!parent->record->GetIsAction()) { //�A�N�V���������s�Ȃ�
		parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //noAction��ݒ�
		return; //�I���
	}


	//�{�^���̃N���b�N���m�I���ƕ\���B���A�N���b�N���̍폜���s��
	parent->actionButton->SetRunUpdateDraw(false, false);
	parent->actionButton->SetRunUpdateDrawClick(false, false);
	parent->foldButton->SetRunUpdateDraw(false, false);
	parent->foldButton->SetRunUpdateDrawClick(false, false);

	parent->gageControl->SetRunUpdate(false); //�Q�[�W�̑���󂯕t�����I������
	parent->gageSound->SetSoundStop(true); //�Q�[�W���쉹�𖳌�������
	count = 0; //���ԃJ�E���g���Z�b�g

	parent->record->SetFinalAction(action); //����A�N�V�������ŏI�A�N�V�����ɂ���
}
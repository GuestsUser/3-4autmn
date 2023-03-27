#include "PK_Change.h"
#include "PK_Main.h"

#include "Scene.h"
#include "Poker.h"
#include "ConstVal.h"

#include "PK_CPU.h"
#include "PK_Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "PK_SectionLibrary.h"

#include "Button.h"
#include "ComponentArray.h"
#include "Cmp_Image.h"
#include "Cmp_CPUBetLogic.h"

Poker::Change::Change(Poker& set) :parent(&set),actionRecord(std::deque<Cmp_BetActionRecord*>((int)Poker::Character::length)) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}

void Poker::Change::Update() {
	int access = parent->dealer->GetActionCharaSub(); //����A�N�V�������s���L�����ւ̓Y�������L�^����A�N�Z�X�V���[�g�J�b�g
	
	parent->chara[access]->SectionUpdate(); //����L�����̃Z�N�V�����pUpdate�����s
	if(actionRecord[access]->GetFinalAction() == Cmp_BetActionRecord::Action::noAction) { return; } //����L�������A�N�V�������ĂȂ��ꍇ�ȉ������͎��s�����I���


	int endCount = ChangeEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
	parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������

	if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
		SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
		parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //main�ł�allIn�L�����̃A�N�V�����͕s�\�Ȃ̂ł������菜�����l�ɉ����ĂƂȂ�
		
		for (auto itr : parent->chara) { itr->SetSection(PK_Chara::Section::main); } //�e�L�����̎��s�Z�N�V������ύX�Ashowdown�͐�p�̃Z�N�V�����������Ȃ��ׂ���ŗǂ�
		parent->run = parent->list[(int)Poker::Section::main]; //�Z�J���h�x�b�g��
		((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);


		int endCount = 1; //�A�N�V�����s�\�ȃL�����̐����擾
		for (endCount; endCount < actionRecord.size(); ++endCount) {
			if (!BetIgnore(actionRecord[(access + endCount) % actionRecord.size()])) { break; } //�`�F�b�N�L�������I��������1�ɂ�����������Ȃ������ꍇ���f
		}
		if (endCount >= actionRecord.size()) { parent->run = parent->list[(int)Poker::Section::showdown]; } //�ǂ̃L�������x�b�g�s�\�̏ꍇ�V���[�_�E�����s
	}
}

#include "PK_NewGameReset.h"
#include "Poker.h"

#include "PK_BGM.h"
#include "PK_CardDealer.h"
#include "PK_Chara.h"
#include "PK_Dealer.h"
#include "PK_Pot.h"

void Poker::NewGameReset::Update() {
	parent->bgm->Reset(); //bgm�V�X�e���̃��Z�b�g
	parent->pot->Reset(); //�|�b�g�̃��Z�b�g
	parent->dealer->FullReset(); //BB���̊Ǘ���Ԃ̊��S���Z�b�g
	parent->cardDealer->Reset(); //�R�D�����Z�b�g

	for (auto chara : parent->chara) { chara->FullReset(); } //�L������Ԃ����S���Z�b�g
	for (auto section : parent->list) { section->FullReset(); } //�Z�N�V�����̊��S���Z�b�g

	parent->SetNextSection(Poker::Section::pre); //�V�����Q�[����pre�X�^�[�g
}
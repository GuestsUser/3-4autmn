#include "DxLib.h"

#include "Btn.h"
#include "PK_Dealer.h"
#include "Poker.h"
#include "PokerFontData.h"

#include <string>

PK_Dealer::PK_Dealer() :btn(Btn()), baseBB(100), addBB(50), maxBet(10) { FullReset(); } //maxBet�̓Q�[�����ω����Ȃ��̂�FullReset�ɂ͊܂߂��������10�ƒ�`���Ă���

void PK_Dealer::Draw() {
	btn.Draw(); //�{�^���摜�̕`��
	DrawStringToHandle(554, 247, ("BB:" + std::to_string(BB)).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
}

void PK_Dealer::Reset() {
	++gameCount; //���E���h���𑝉�����

	BB = baseBB + addBB * ((int)(gameCount / (int)Poker::Character::length)); //1��������BB��addBB������������

	btn.Reset(); //�{�^���|�W�V���������Z�b�g����
	SetActionChara(btn.GetBtnPos() + 1); //�ŏ��ɃA�N�V�������s���L�������{�^���|�W�V�����̎��̃L�����ɐݒ肷��
}

void PK_Dealer::FullReset() {
	BB = baseBB; //BB�������l�ɐݒ�
	gameCount = 0; //���E���h����0�ɐݒ�
	btn.FullReset(); //�{�^���|�W�V������FullReset
	SetActionChara(btn.GetBtnPos() + 1); //�ŏ��ɃA�N�V�������s���L�������{�^���|�W�V�����̎��̃L�����ɐݒ肷��
}

void PK_Dealer::SetActionChara(int set) { playSub = set % (int)Poker::Character::length; }
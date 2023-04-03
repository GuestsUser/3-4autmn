#pragma once
#include "Poker.h"
#include "Cmp_BetActionRecord.h"

#include <deque>
#include <string>

class PK_Card;
class PK_Dealer;
class PK_Chara;
class PK_Pot;
class PK_CardDealer;

class Button;
class Cmp_CPUBetLogic;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;


PK_Card* Power2Card(std::deque<PK_Card*>& hand, int target); //hand����target�ɓn���ꂽ�J�[�h�̋����ƈ�v����J�[�h�𒊏o����

Cmp_BetActionRecord::Action ActionDecision(Cmp_CPUBetLogic* betLogic); //�����ꂽbetLogic�ɂ����raise���ׂ���call���ׂ����Ԃ�
bool BetIgnore(Cmp_BetActionRecord* record); //�L�����̃A�N�V�����L�^��n�����ł��̃L�����̃x�b�g���X�L�b�v���ׂ����ۂ��Ԃ��Atrue�ŃX�L�b�v
bool IsFold(Cmp_BetActionRecord& record); //record�̃L�������A�N�V�������I��点������fold�ŏ��O���ꂽ�����̃t�F�[�Y�����ł��Ȃ��Ȃ��Ă����true��Ԃ�
int FoldCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center); //�Q�[�����甲�����L��������Ԃ��Acenter��record�֎g�p����Y����������Ƃ��̃L�����𒆐S�Ƀ`�F�b�N����
int ActionEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center); //�A�N�V�����I���ς݃L��������Ԃ��Acenter��record�֎g�p����Y����������Ƃ��̃L�����𒆐S�ɏI���ς݃L���������`�F�b�N����
int ChangeEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center); //Change��pEndCount�A��L��BetIgnore�Ȃ̂�Change�ɂ͎g���Ȃ�����p��
int EnableCharaSearch(std::deque<Cmp_BetActionRecord*>& actionRecord, int center); //��LEndCount�ł͏I���L�����𒲂ׂ����������center����ŒZ�̖��s�k�L�����Y������Ԃ�

int RaiseCalculation(const std::deque<int>& split, int& runCount, int oldPay, int betRequest, int BB, int coin); //���E���h���ł̑��x���z�ƕ������C�Y�������܂Ŏg������Ԃ��Asplit�ɕ������C�Y�f�[�^�ArunCount��split�ǂݏo���J�n�ʒu��(�ҏW�����A���̓ǂݏo���J�n�ʒu�܂ňړ������)�AoldPay�ɑO��܂ł̎x���z�AbetRequest�Ɍ��ݍő�x�b�g���ABB�Ɍ���BB���Acoin�ɏ�����������
void SequenceNextReset(const std::deque<Cmp_BetActionRecord*>& chara); //���V�[�P���X�ֈڍs����ێ��s����A�N�V�����L�^���Z�b�g�p�֐�
void BBSBLevy(int BBpos, std::deque<PK_Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord, Cmp_Gage_Border& gageBorder, Cmp_Gage_UpperBorder& gageUpper, PK_Pot& pot, PK_Dealer& dealer); //BB�ASB�|�W�V�����L��������BB�ASB�����
void LoseSet(const std::deque<PK_Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord); //���ݏ������ɍ��킹�Ĕs�k�ݒ���s��
void PartsFullReset(std::deque<PK_Chara*>& chara, PK_Pot& pot, PK_Dealer& dealer, PK_CardDealer& cardDealer); //�e��fullReset�����s��Pre����V�����Q�[�����n�߂���悤�ɂ���

void PlayerButtonAnalyze(const std::deque<Button*>& button, Button** action, Button** fold); //button��player�̃{�^����������action�ɃA�N�V�����p�{�^���Afold��fold�p�{�^�������ĕԂ��Ă����

void FoldMemberPayOut(std::deque<PK_Chara*>& chara, PK_Pot& pot); //fold�L������PayOut

Poker::Section GameEndCheck(const std::deque<PK_Chara*>& chara, const std::deque<Cmp_BetActionRecord*>& actionRecord); //���݂̔s�k�󋵂���������ׂ��V�[����Ԃ�
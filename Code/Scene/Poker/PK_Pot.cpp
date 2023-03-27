#include "DxLib.h"

#include "PK_Chara.h"
#include "PK_Pot.h"
#include "PokerFontData.h"

#include "Component.h"
#include "Cmp_Image.h"
#include "Cmp_Transform.h"

#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>

PK_Pot::PK_Pot() :pot(std::map<int, int>()), charaPayment(std::unordered_map<const PK_Chara*, int>()), textPos(Cmp_Transform()) {
	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pot.png")), 1); //�|�b�g���z�\���w�i�摜����
	back->EditTranform()->EditPos().SetXYZ(604, 295, 0); //�ʒu�ݒ�
	textPos.EditPos().SetXYZ(567, 324, 0); //�e�L�X�g�ʒu�ݒ�
}

PK_Pot::~PK_Pot() { delete back; } //�摜�͏I���Ɠ����ɍ폜

void PK_Pot::Draw() {
	back->Draw(); //�|�b�g���z�̔w�i�\��

	int potSum = 0; //�|�b�g�����z���v
	for (auto itr : pot) { potSum += itr.second; } //�|�b�g�̗v�f�S�Ă��`�F�b�N�����v���z���o��
	DrawStringToHandle(textPos.ReadPos().GetX(), textPos.ReadPos().GetY(), std::to_string(potSum).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
}

void PK_Pot::Reset() {
	charaPayment = std::unordered_map<const PK_Chara*, int>(); //�e�L�����̎x�������̃��Z�b�g�A������ɂ���
	pot = std::map<int, int>(); //�T�C�h�|�b�g�A���C���|�b�g�����Z�b�g
}

int PK_Pot::PayOut(const PK_Chara& user) {
	int payOut = 0; //�x�����v�z

	for (auto itr = pot.find(charaPayment[&user]); true; --itr) { //map�͏����Ȃ̂Ŏ��g�ȉ��̃|�b�g�𓾂�בO�ɐi�߂�
		payOut += itr->second; //����̃|�b�g���x���z�ɉ�����
		itr->second = 0; //����̃|�b�g�����Z�b�g
		if (itr == pot.begin()) { break; } //�O������end()�̂悤�ȕ����Ȃ��̂ŏI���������������Ɏ����Ă���
	}

	return payOut; //�x���z��Ԃ�
}

int PK_Pot::Inquiry(const PK_Chara& user) {
	if (charaPayment.count(&user) == 0) { return 0; } //�x�������Ȃ��ꍇ0��Ԃ��ďI���
	return charaPayment[&user]; //�x���z��Ԃ�
}

int PK_Pot::TotalAmount() {
	int sum = 0;
	for (auto itr = pot.begin(); itr != pot.end(); ++itr) { sum += itr->second; } //�e�|�b�g�����z��sum�֍��v���Ă䂭
	return sum;
}

void PK_Pot::SetSidePot(int pay, const PK_Chara& user) {
	charaPayment[&user] = charaPayment[&user] + pay; //��芸�����T�C�h�|�b�g�p�x���z���L�^���Ă���

	std::deque<std::pair<int, const PK_Chara*>> copy = std::deque<std::pair<int, const PK_Chara*>>(); //�x���󋵂��R�s�[����
	for (auto itr : charaPayment) { copy.push_back(std::make_pair(itr.second, itr.first)); } //map��unordered_map���]�v�ȋ@�\�̂����Ń\�[�g�ł��Ȃ�����pair���g��
	std::sort(copy.begin(), copy.end(), [](std::pair<int, const PK_Chara*> a, std::pair<int, const PK_Chara*> b) { return a.first < b.first; }); //�x���z�������Ƀ\�[�g

	Reset(); //���f�[�^�̏���

	for (auto itr : copy) { SetMainPot(itr.first, *itr.second); } //���荞�񂾃T�C�h�|�b�g�������炠�镨�Ƃ��Ĉ����׏����ɍĐU�蕪�����s��
}

void PK_Pot::SetMainPot(int pay, const PK_Chara& user) {
	auto itr = pot.begin(); //for�J�n�ʒu
	int paid = 0; //����pay����pot�֎x���������̋��z
	int old = 0; //�O��܂ł̎x���z

	if (charaPayment.count(&user)) { //��x�x��������������ꍇ
		itr = pot.find(charaPayment[&user]); //�O��x���ʒu�ɐݒ�
		old = itr->first; //�O��x�����L��
		itr++; //�J�n�ʒu��O��x���ʒu�̎��ɕύX����
	}

	for (itr; itr != pot.end(); ++itr) { //�J�n�ʒu���猻�ݍő�|�b�g�܂ŃC�e���[�^�[���񂵐U�蕪�����s��
		int currentPay = itr->first - paid - old; //����̃|�b�g�ւ̎x���v���z
		if (pay < paid + currentPay) { break; } //����x�����������x���z�𒴂�����I��
		itr->second += currentPay; //�|�b�g�ɗv���z���x����
		paid += currentPay; //����v���z���x���ς݂Ƃ���
	}

	pot[pay + old] += pay - paid; //�e�|�b�g�֎x�������z����菜���č���z�̃|�b�g�֎x����
	charaPayment[&user] += pay; //����̎x���z���L�^

}
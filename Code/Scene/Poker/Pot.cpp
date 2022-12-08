#include "DxLib.h"

#include "Pot.h"
#include "DxLib.h"
#include "PokerFontData.h"

#include "Chara.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"

#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>

Pot::Pot() :pot(std::map<int, int>()), charaPayment(std::unordered_map<const Chara*, int>()), textPos(Cmp_Transform()) {
	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pot.png")), 1); //�|�b�g���z�\���w�i�摜����
	back->EditTranform()->EditPos().SetXYZ(604, 295, 0); //�ʒu�ݒ�
	textPos.EditPos().SetXYZ(567, 324, 0); //�e�L�X�g�ʒu�ݒ�
}

Pot::~Pot() { delete back; } //�摜�͏I���Ɠ����ɍ폜

void Pot::Draw() {
	back->Draw(); //�|�b�g���z�̔w�i�\��

	int potSum = 0; //�|�b�g�����z���v
	for (auto itr : pot) { potSum += itr.second; } //�|�b�g�̗v�f�S�Ă��`�F�b�N�����v���z���o��
	DrawStringToHandle(textPos.ReadPos().GetX(), textPos.ReadPos().GetY(), std::to_string(potSum).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
}

void Pot::Reset() {
	charaPayment.clear(); //�e�L�����̎x�������̃��Z�b�g
	pot.clear(); //�T�C�h�|�b�g�A���C���|�b�g�����Z�b�g
}

int Pot::PayOut(const Chara& user) {
	int payOut = 0; //�x�����v�z

	for (auto itr = pot.find(charaPayment[&user]); true; --itr) { //map�͏����Ȃ̂Ŏ��g�ȉ��̃|�b�g�𓾂�בO�ɐi�߂�
		payOut += itr->second; //����̃|�b�g���x���z�ɉ�����
		itr->second = 0; //����̃|�b�g�����Z�b�g
		if (itr == pot.begin()) { break; } //�O������end()�̂悤�ȕ����Ȃ��̂ŏI���������������Ɏ����Ă���
	}

	return payOut; //�x���z��Ԃ�
}

int Pot::Inquiry(const Chara& user) {
	int payOut = 0; //�x�����v�z

	auto itr = pot.find(charaPayment[&user]);

	for (itr; true; --itr) { //map�͏����Ȃ̂Ŏ��g�ȉ��̃|�b�g�𓾂�בO�ɐi�߂�
		if (itr == pot.begin()) { break; } //�O������end()�̂悤�ȕ����Ȃ��̂ŏI���������������Ɏ����Ă���
		payOut += itr->second; //����̃|�b�g���x���z�ɉ�����
	}

	return payOut; //�x���z��Ԃ�
}

void Pot::SetSidePot(int pay, const Chara& user) {
	charaPayment[&user] = pay; //��芸�����T�C�h�|�b�g�p�x���z���L�^���Ă���

	std::deque<std::pair<int, const Chara*>> copy = std::deque<std::pair<int, const Chara*>>(); //�x���󋵂��R�s�[����
	for (auto itr : charaPayment) { copy.push_back(std::make_pair(itr.second, itr.first)); } //map��unordered_map���]�v�ȋ@�\�̂����Ń\�[�g�ł��Ȃ�����pair���g��
	std::sort(copy.begin(), copy.end(), [](std::pair<int, const Chara*> a, std::pair<int, const Chara*> b) { return a.first < b.first; }); //�x���z�������Ƀ\�[�g

	charaPayment.clear(); //���f�[�^�̏���
	pot.clear();

	for (auto itr : copy) { SetMainPot(itr.first, *itr.second); } //���荞�񂾃T�C�h�|�b�g�������炠�镨�Ƃ��Ĉ����׏����ɍĐU�蕪�����s��
}

void Pot::SetMainPot(int pay, const Chara& user) {
	auto itr = pot.begin(); //for�J�n�ʒu
	int paid = 0; //�x���ς݊z

	if (charaPayment.count(&user)) { //��x�x��������������ꍇ
		itr = ++pot.find(charaPayment[&user]); //�O��x���ʒu�̎��ɊJ�n�ʒu�����킹��
		paid = (--itr)->first; //�O��x�������͖Ə�����
	}

	for (itr; itr != pot.end(); ++itr) { //�J�n�ʒu���猻�ݍő�|�b�g�܂ŃC�e���[�^�[���񂵐U�蕪�����s��
		int currentPay = itr->first - paid; //����̃|�b�g�ւ̎x���v���z
		if (pay < paid + currentPay) { break; } //�x���v���z���x���z�𒴂�����I���
		itr->second += currentPay; //�|�b�g�ɗv���z���x����
		paid += currentPay; //����v���z���x���ς݂Ƃ���
	}

	pot[pay] += pay - paid; //�e�|�b�g�֎x�������z����菜���č���z�̃|�b�g�֎x����
	charaPayment[&user] = pay; //����̎x���z���L�^

}
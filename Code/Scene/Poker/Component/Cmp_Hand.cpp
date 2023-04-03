#include <DxLib.h>
#include "Cmp_Hand.h"

#include "PK_CardDealer.h"
#include "PK_Card.h"

#include <algorithm>
#include <deque>
#include <string>


Cmp_Hand::Cmp_Hand() :handPower(std::deque<int>()), handName(std::string()) {
	for (int i = 0; i < 5; ++i) { card.push_back(new PK_Card()); } //��D�\����V�K�쐬
}
Cmp_Hand::~Cmp_Hand() {
	for (auto itr : card) { delete itr; } //��D�̍폜
	card.clear(); //�z��̃N���A
}

void Cmp_Hand::Update() { for (auto itr : card) { itr->Update(); } } //card��Update�����s
void Cmp_Hand::Draw() { for (auto itr : card) { itr->Draw(); } } //card��Draw�����s
void Cmp_Hand::FullReset() { for (auto itr : card) { itr->FullReset(); } } //��������J�[�h��FullReset���Ăяo��
void Cmp_Hand::Reset() { for (auto itr : card) { itr->Reset(); } } //��������J�[�h��Reset���Ăяo��



std::string Hand2String(const std::deque<int>& hand) {
	switch ((Cmp_Hand::HandRank)(hand[0] / (int)Cmp_Hand::CardPower::max)) {
	case Cmp_Hand::HandRank::No: return "�n�C�J�[�h"; break;
	case Cmp_Hand::HandRank::OnePair: return "�����y�A"; break;
	case Cmp_Hand::HandRank::TwoPair: return "�c�[�y�A"; break;
	case Cmp_Hand::HandRank::ThreeCard: return "�X���[�J�[�h"; break;
	case Cmp_Hand::HandRank::Straight: return "�X�g���[�g!"; break;
	case Cmp_Hand::HandRank::Flash: return "�t���b�V��!"; break;
	case Cmp_Hand::HandRank::FullHause: return "�t���n�E�X!"; break;
	case Cmp_Hand::HandRank::FourCard: return "�t�H�[�J�[�h!!"; break;
	case Cmp_Hand::HandRank::StraightFlash: return "�X�g���[�g�t���b�V��!!"; break;
	case Cmp_Hand::HandRank::RoyalStraightFlash: return "���C�����X�g���[�g�t���b�V��!!!"; break;
	}
}

std::deque<int> CardNumExtract(std::deque<PK_Card*>& card) { //�󂯎����card�z�񂩂�\���摜�ɗ��p����Y�������������o���Ĕz��ɋl�߂ĕԂ�
	std::deque<int> set;
	for (auto itr : card) { set.push_back(itr->GetCard()); }
	return set;
}

PK_Card* Num2Card(int card, std::deque<PK_Card*>& originl) { //original�ɓ����ꂽCard�z�񂩂�card�Ɠ���̕\���摜�Y�����̃J�[�h�Q�Ƃ�Ԃ��֐�
	for (auto itr : originl) {
		if (itr->GetCard() == card) { return itr; } //�Ή��J�[�h���������ꍇ�����Ԃ��ďI���A�Ή��������������ꍇ�ŏ��ɏo�������D�悳���
	}
	return nullptr; //������Ȃ������ꍇnullptr��Ԃ�
}

PK_Card* CardPower2Card(int card, std::deque<PK_Card*>& originl) { //cardPower�̌`����original����Ή���T���A�Ή��������������ꍇ�X�[�g���ア�����D�悳���
	for (auto itr : originl) {
		for (int i = 0; i < 4; ++i) { //card�ɂ͂ǂ̃X�[�g���̏�񂪓����ĂȂ��̂�4�̃X�[�g�S�Ă���D�Ɣ�r���đΉ���T��
			if (itr->GetCard() == card + ((int)Cmp_Hand::CardPower::max) * i) { return itr; } //�Ή��J�[�h���������ꍇ�����Ԃ��ďI��
		}
	}
	return nullptr; //������Ȃ������ꍇnullptr��Ԃ�
}

void HandComboCheck(std::deque<int> hand, Cmp_Hand::deque_map& get) { //hand�Ɍ��ݎ�D��n���Ƃ��̎�D�œ��������̃J�[�h�̌���get�ɓ���Ă����
	for (int i = 0; i < hand.size(); ++i) {
		if (hand[i] == -1) { continue; } //�`�F�b�N�ς݂�-1�D�̏ꍇ��΂�
		get.push_back(std::pair<int, int>(hand[i] % 13, 1)); //��`�F�b�N�̃J�[�h�Ȃ�ǉ����Ă���

		int sub = get.size() - 1; //����̓Y����
		for (int j = i + 1; j < hand.size(); ++j) {
			if (get[sub].first != hand[j] % (int)Cmp_Hand::CardPower::max) { continue; } //�D���Ⴄ�ꍇ��蒼��
			++get[sub].second; //���̎D�̖����J�E���g�𑝂₷
			hand[j] = -1; //�����D���`�F�b�N���Ȃ��悤���ׂ��D��-1�����
		}
	}
	std::sort(get.begin(), get.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.second == b.second ? a.first > b.first:a.second > b.second; }); //get�\�[�g�A����J�[�h���������A����J�[�h���������Ȃ�Y�������傫����
}

int HandStraightCheck(const Cmp_Hand::deque_map& combo) { //�X�g���[�g(���l��1���݂ŕ���ł�)���`�F�b�N�A����ł�ꍇ�ł��傫���J�[�h�p���[�̕ԋp�A���s�̏ꍇ-1
	int old = combo.begin()->first; //�O��̐��l
	bool ato5 = false; //ace�`five�̃X�g���[�g�̏ꍇtrue�ɂ���
	for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) {
		if (old - itr->first == 1) { old = itr->first; continue; } //�A�ԂɂȂ��Ă���Ȃ玟�ɍs��
		if (old == (int)Cmp_Hand::CardPower::ace && itr->first == (int)Cmp_Hand::CardPower::five) { ato5 = true; old = itr->first; continue; } //�O��A�ō���5�Ȃ�A��1�Ƃ��Ĉ����ב�����
		return -1; //�����܂ŗ����ꍇ�X�g���[�g�Ȃ��A���s�ł���-1��Ԃ��I��
	}
	return combo[ato5].first; //ace�`five�̃X�g���[�g�̏ꍇ�擪�ł͂Ȃ���������l�����
}

bool HandFlashCheck(const std::deque<int>& hand) { //�t���b�V��(�S�ē����X�[�g)���`�F�b�N
	int suit = hand[0] / 13; //��X�[�g���o��
	for (auto itr = ++hand.begin(); itr != hand.end(); ++itr) { if (suit != *itr / 13) { return false; } } //�Ⴄ�X�[�g���������ꍇ�t���b�V���͂Ȃ�
	return true; //�����܂ł����ΐ����Atrue��Ԃ�
}

bool HandRoyalCheck(const Cmp_Hand::deque_map& combo) { //���C����(���т�a�`10)���`�F�b�N
	for (int i = 0; i < combo.size(); ++i) { if (combo[i].first != (int)Cmp_Hand::CardPower::ace - i) { return false; } } //combo�͐���ς݂Ȃ̂Ő���ɗ�O�I�Ȓl������Ύ��s
	return true;
}
int HandFlashReachCheck(const std::deque<int>& hand) { //�t���b�V�����[�`(�X�[�g�Ⴂ��1����)�`�F�b�N�A�Ԃ�l�̓X�[�g�̈Ⴄ�J�[�h�A���[�`�ɂȂ��ĂȂ��ꍇ-1
	int flash = -1;
	std::deque<std::deque<int>> suitVol = std::deque<std::deque<int>>(4); //[0]�ɃX�[�g�A[0][0]�ɂ��̃X�[�g�ɑ�����J�[�h���i�[����
	for (auto itr : hand) { suitVol[(int)(itr / (int)Cmp_Hand::CardPower::max)].push_back(itr); }

	for (auto itr : suitVol) { //�e�X�[�g�ɑ�����J�[�h�����`�F�b�N����
		if (itr.size() > 1 && itr.size() < 4) { return -1; } //����X�[�g��2������3������΃t���b�V���s��
		if (itr.size() == 1) { //����X�[�g��1���̏ꍇ
			if (flash != -1) { return -1; } //���ꂪ2��ڂ̎��s�������ꍇ�t���b�V���s��
			flash = itr[0]; //1���̃J�[�h���i�[
		}
	}
	return flash;
}
int HandStraightReachCheck(Cmp_Hand::deque_map combo, const std::deque<int>& hand) { //�X�g���[�g���[�`(�X�[�g�Ⴂ��1����)�`�F�b�N�A�Ԃ�l�̓X�[�g�̈Ⴄ�J�[�h�A���[�`�ɂȂ��ĂȂ��ꍇ-1
	int straight = -1;
	if (combo[0].second > 2) { return -1; } //����J�[�h��2���𒴂���ꍇ�X�g���[�g�͖���
	if (combo[1].second > 1) { return -1; } //�y�A���ł��Ă�ꍇ�X�g���[�g�͖���

	if (combo[0].second >= 2) { straight = combo[0].first; } //�d���J�[�h������ꍇ�s�v�J�[�h�͂���
	std::sort(combo.begin(), combo.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.first > b.first; }); //����J�[�h�ێ������Ɋ֌W�Ȃ��J�[�h�̋������ɕ��ёւ�

	if (combo[0].first == (int)Cmp_Hand::CardPower::ace && (combo[1].first == (int)Cmp_Hand::CardPower::five || combo[1].first == (int)Cmp_Hand::CardPower::four)) { //ace,two�̕��т̏ꍇace��one�ɂ��Ĕz��̍Ō�֊i�[����
		int copy = combo[0].second; //�擪��ace�̃J�[�h�������L��
		combo.erase(combo.begin()); //�擪���폜
		combo.push_back(std::pair<int, int>((int)Cmp_Hand::CardPower::one, copy)); //���ɒǉ�ace��one�ɉ��߂�����ǉ�
	}

	//one�̏ꍇ�̃X�g���[�g�`�F�b�N�������Aace�������A2345�̓�3���������ace��one�Ƃ��Ĉ���
	//if (combo[0].first == (int)CardDealer::CardPower::ace) {

	//}


	int start = combo[0].first - combo[1].first > 1; //��ԋ����J�[�h�Ǝ��̃J�[�h���q�����Ă���ꍇfalse�A�q�����Ă��Ȃ����true���Ԃ�Aint�^�Ȃ̂ő��X0�A1�ɕϊ������
	int changeCount = 0; //�q�����ĂȂ��J�[�h�����m�����񐔋L�^

	if (straight != -1 && combo[0].first - combo[1].first > 1) { return -1; } //�d���J�[�h�����銎�擪�Ǝ��̃J�[�h�̍���2�ȏ�̏ꍇ�d���J�[�h�Ɛ擪�J�[�h����������K�v������̂ŃX�g���[�g�͖���
	if (straight == -1 && start) { straight = combo[0].first; } //�擪�J�[�h�Ǝ��J�[�h���q�����ĂȂ������ꍇ�����J�[�h�ɐ擪�J�[�h���w��A�d���J�[�h���������ꍇ��������D��
	if (straight == -1) { straight = combo[combo.size() - 1].first == (int)Cmp_Hand::CardPower::one ? (int)Cmp_Hand::CardPower::ace : combo[combo.size() - 1].first; } //�����w�肪�Ȃ��ꍇ��Ԏア�J�[�h����������Aone�̏ꍇace�ɒ����Ă���

	int old = combo[start].first; //�O��̃J�[�h�̋�������

	for (int i = start + 1; i < combo.size(); ++i) { //�擪�ȊO�Ɍq�����ĂȂ��������Ȃ����`�F�b�N
		if (old - 1 != combo[i].first) { //�O�񐔒l�����񐔒l�ƌq���炩�������ꍇ
			if (changeCount > 0) { return -1; } //2��ڂ̎��s�Ȃ�X�g���[�g�͕s��
			old = old - 2; //���Ɍq����悤old��⊮���Ă����A�����first�ɍ��킹���2���ȏ�J�[�h���щz����\��������̂�-2�Ƃ����`�ɂ���
			changeCount++; //�q�����ĂȂ��J�[�h�J�E���g
			continue; //��蒼��
		}
		old = combo[i].first;
	}
	if (changeCount <= 0) { return -1; } //�q�����ĂȂ��J�[�h�����m���Ȃ������ꍇ�X�g���[�g�͖����Ƃ����������ł��Ă�

	for (auto itr : hand) { //combo�̓J�[�h���J�[�h�p���[�Ŋi�[���Ă�̂ł����ʏ�J�[�h�ɒ�������
		if (itr % (int)Cmp_Hand::CardPower::max == straight) { return itr; } //�s�v�ȃJ�[�h��hand���̈�v����J�[�h�p���[������΂��̃J�[�h��s�v�ȃJ�[�h�Ƃ��ĕԂ��ďI���
	}
	return 99999; //�����Ȃ��Ǝv�����G���[
}




void Cmp_Hand::HandPowerUpdate() {
	handPower.clear(); //���g�̃��Z�b�g
	deque_map combo = deque_map(); //first=�J�[�h�̋��� second=���̃J�[�h�̖��� �ō\�����ꂽ�J�[�h�i�[�z��
	std::deque<int> hand = CardNumExtract(card); //��D�𐔒l�����������i�[

	HandComboCheck(hand, combo); //����J�[�h���i�[����

	while (true) { //break���g���ď����̗�����R���g���[���������̂�while���̗p�A���[�v�̈Ӑ}�͂Ȃ�
		if (combo.begin()->second == 1) { //�����J�[�h��1�����Ȃ������ꍇ
			int max = HandStraightCheck(combo); //�����\������J�[�h�̒��ōő�J�[�h�p���[�A�X�g���[�g�̗L���`�F�b�N�����˂Ă���
			bool straight = max > 0; //max��0�ȏオ�����Ă���΃X�g���[�g�L��
			bool flash = HandFlashCheck(hand); //�t���b�V���]�����ʂ����Ă���

			handPower.push_back(combo.begin()->first); //combo����ő�J�[�h�p���[������Ă���
			for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { handPower.push_back(itr->first); } //�J�[�h�i�[

			if (straight && flash) { //�X�g���[�g�ƃt���b�V�����L���ȏꍇ�Ɍ��胍�C�����`�F�b�N���s��
				if (HandRoyalCheck(combo)) { handPower[0] = ((int)HandRank::RoyalStraightFlash) * (int)CardPower::max + max; } //���C�������L���������ꍇ���C�����X�g���[�g�t���b�V��
				else { handPower[0] = ((int)HandRank::StraightFlash) * (int)CardPower::max + max; } //�������ł���΃X�g���[�g�t���b�V��
				break; //�|�C���g�v�Z�I���
			}
			if (straight) { handPower[0] = ((int)HandRank::Straight) * (int)CardPower::max + max; break; } //�X�g���[�g��Ԃ�
			if (flash) { handPower[0] = ((int)HandRank::Flash) * (int)CardPower::max + handPower[0]; break; } //�t���b�V����Ԃ�

			break; //�|�C���g�v�Z�I���
		}

		if ((combo.begin() + 1)->second == 1) { //�J�[�h���y�A(aaa33�̂悤�ɓ����J�[�h�̑g���ł��Ă�A�����y�A�͑ΏۊO)�ł͂Ȃ��ꍇ
			HandRank rank = HandRank::OnePair; //�����J�[�h�̖����ɉ����ă����N������A��芸���������y�A
			if (combo.begin()->second == 3) { rank = HandRank::ThreeCard; } //3������΃X���[�J�[�h
			if (combo.begin()->second == 4) { rank = HandRank::FourCard; } //4���Ȃ�΃t�H�[�J�[�h

			handPower.push_back(((int)rank) * (int)CardPower::max + combo.begin()->first); //�����N�ɉ��������_����
			for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { handPower.push_back(itr->first); } //�]�����J�[�h������
			break; //�|�C���g�v�Z�I���
		}

		//�c��̓y�A�̏ꍇ�̓_�v�Z�̂�
		handPower.push_back(((int)(combo.begin()->second == 3 ? HandRank::FullHause : HandRank::TwoPair)) * (int)CardPower::max + combo.begin()->first); //�����J�[�h��3���������ꍇ�t���n�E�X�A�����łȂ��Ȃ�c�[�y�A
		for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { handPower.push_back(itr->first); } //�]�����J�[�h������
		break; //�|�C���g�v�Z�I���
	}
	handName = Hand2String(handPower); //�����𖼂��X�V
}

PK_Card* Cmp_Hand::ReachCheck() {
	deque_map combo = deque_map(); //first=�J�[�h�̋��� second=���̃J�[�h�̖��� �ō\�����ꂽ�J�[�h�i�[�z��
	std::deque<int> hand = CardNumExtract(card); //��D�𐔒l�����������i�[
	HandComboCheck(hand, combo); //����J�[�h���i�[����

	PK_Card* flash = Num2Card(HandFlashReachCheck(hand), card); //�t���b�V�������ɕs�v�ȃJ�[�h
	PK_Card* straight = Num2Card(HandStraightReachCheck(combo, hand), card); //�X�g���[�g�����ɕs�v�ȃJ�[�h

	if (flash != nullptr && straight != nullptr) { //�X�g���[�g�A�t���b�V�������\�������ꍇ
		if (flash->GetCard() % (int)Cmp_Hand::CardPower::max == straight->GetCard() % (int)Cmp_Hand::CardPower::max) { straight = flash; } //�X�g���[�g�̕ύX�J�[�h�ɏd���J�[�h���������ꍇ2�̃J�[�h�̓�hand�v�f�̎Ⴂ����Ԃ��̂����Aflash�Ɨv���J�[�h�p���[���ꏏ�������Ȃ�flash�̃J�[�h�ɍ��킹��
		return GetRand(1) ? flash : straight; //�����q�b�g�����ꍇ�ǂ����Ԃ�����GetRand�Ń����_�����肷��
	}

	return flash == nullptr ? straight : flash; //�󂶂�Ȃ�����Ԃ��A������̏ꍇstraight��Ԃ������g�͂ǂ������ꏏ������֌W�Ȃ�
}
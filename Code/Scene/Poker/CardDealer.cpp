#include <DxLib.h>

#include "CardDealer.h"
#include "PK_Card.h"
#include "Chara.h"

#include <algorithm>
#include <deque>
#include <numeric>
#include <random>
#include <unordered_map>
#include <utility>

CardDealer::CardDealer() :deck(std::deque<int>(52)), gen(std::mt19937()), top(0) { gen.seed((std::random_device())()); }

void CardDealer::Reset() {
	top = 0; //�R�D�̏��0�ɖ߂�
	std::iota(deck.begin(), deck.end(), 0); //0�`52�̒l���e�v�f�Ɋi�[
	std::shuffle(deck.begin(), deck.end(), gen); //�������Ă���l�������_������
}

int CardDealer::DeckDraw() {
	++top; //�R�D�������̂�1���₵�Ď��̓Y������
	return deck[top - 1]; //����̎R�D�̐��l��Ԃ�
}




void HandComboCheck(std::deque<int> hand, CardDealer::deque_map& get) { //hand�Ɍ��ݎ�D��n���Ƃ��̎�D�œ��������̃J�[�h�̌���get�ɓ���Ă����
	for (int i = 0; i < hand.size(); ++i) {
		if (hand[i] = -1) { continue; } //�`�F�b�N�ς݂�-1�D�̏ꍇ��΂�
		++get[hand[i] % 13].second; //��`�F�b�N�̃J�[�h�Ȃ�����Z���Ă���

		for (int j = i; j < hand.size(); ++j) {
			if (hand[i] % (int)CardDealer::CardPower::max != hand[j] % (int)CardDealer::CardPower::max) { continue; } //�D���Ⴄ�ꍇ��蒼��
			++get[hand[j] % 13].second; //���̎D�̖����J�E���g�𑝂₷
			hand[j] = -1; //�����D���`�F�b�N���Ȃ��悤���ׂ��D��-1�����
		}
	}
	std::sort(get.begin(), get.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.second == b.second ? a.first > b.first:a.second > b.second; }); //get�\�[�g�A����J�[�h���������A����J�[�h���������Ȃ�Y�������傫����
}

int HandStraightCheck(const CardDealer::deque_map& combo) { //�X�g���[�g(���l��1���݂ŕ���ł�)���`�F�b�N�A����ł�ꍇ�ł��傫���J�[�h�p���[�̕ԋp�A���s�̏ꍇ-1
	int old = combo.begin()->first; //�O��̐��l
	bool ato5 = false; //ace�`five�̃X�g���[�g�̏ꍇtrue�ɂ���
	for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) {
		if (old - itr->first == 1) { old = itr->first; continue; } //�A�ԂɂȂ��Ă���Ȃ玟�ɍs��
		if (old == (int)CardDealer::CardPower::ace && itr->first == (int)CardDealer::CardPower::five) { ato5 = true; old = itr->first; continue; } //�O��A�ō���5�Ȃ�A��1�Ƃ��Ĉ����ב�����
		return -1; //�����܂ŗ����ꍇ�X�g���[�g�Ȃ��A���s�ł���-1��Ԃ��I��
	}
	return combo[ato5].first; //ace�`five�̃X�g���[�g�̏ꍇ�擪�ł͂Ȃ���������l�����
}

bool HandFlashCheck(const std::deque<int>& hand) { //�t���b�V��(�S�ē����X�[�g)���`�F�b�N
	int suit = hand[0] / 13; //��X�[�g���o��
	for (auto itr = ++hand.begin(); itr != hand.end(); ++itr) { if (suit != *itr / 13) { return false; } } //�Ⴄ�X�[�g���������ꍇ�t���b�V���͂Ȃ�
	return true; //�����܂ł����ΐ����Atrue��Ԃ�
}

bool HandRoyalCheck(const CardDealer::deque_map& combo) { //���C����(���т�a�`10)���`�F�b�N
	for (int i = 0; i < combo.size(); ++i) { if (combo[i].first != (int)CardDealer::CardPower::ace - i) { return false; } } //combo�͐���ς݂Ȃ̂Ő���ɗ�O�I�Ȓl������Ύ��s
	return true;
}
int HandFlashReachCheck(const std::deque<int>& hand) { //�t���b�V�����[�`(�X�[�g�Ⴂ��1����)�`�F�b�N�A�Ԃ�l�̓X�[�g�̈Ⴄ�J�[�h�A���[�`�ɂȂ��ĂȂ��ꍇ-1
	int flash = -1;
	std::deque<std::deque<int>> suitVol = std::deque<std::deque<int>>(4); //[0]�ɃX�[�g�A[0][0]�ɂ��̃X�[�g�ɑ�����J�[�h���i�[����
	for (auto itr : hand) { suitVol[(int)(itr / (int)CardDealer::CardPower::max)].push_back(itr); }

	for (auto itr : suitVol) { //�e�X�[�g�ɑ�����J�[�h�����`�F�b�N����
		if (itr.size() > 1 && itr.size() < 4) { return -1; } //����X�[�g��2������3������΃t���b�V���s��
		if (itr.size() == 1) { //����X�[�g��1���̏ꍇ
			if (flash != -1) { return -1; } //���ꂪ2��ڂ̎��s�������ꍇ�t���b�V���s��
			flash = itr[0]; //1���̃J�[�h���i�[
		}
	}
	return flash;
}
int HandStraightReachCheck(CardDealer::deque_map combo, const std::deque<int>& hand) { //�X�g���[�g���[�`(�X�[�g�Ⴂ��1����)�`�F�b�N�A�Ԃ�l�̓X�[�g�̈Ⴄ�J�[�h�A���[�`�ɂȂ��ĂȂ��ꍇ-1
	int straight = -1;
	if (combo[0].second > 2) { return -1; } //����J�[�h��2���𒴂���ꍇ�X�g���[�g�͖���
	if (combo[1].second > 1) { return -1; } //�y�A���ł��Ă�ꍇ�X�g���[�g�͖���

	if (combo[0].second >= 2) { straight = combo[0].first; } //�d���J�[�h������ꍇ�s�v�J�[�h�͂���
	std::sort(combo.begin(), combo.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.first > b.first; }); //����J�[�h�ێ������Ɋ֌W�Ȃ��J�[�h�̋������ɕ��ёւ�
	
	if (combo[0].first == (int)CardDealer::CardPower::ace && (combo[1].first == (int)CardDealer::CardPower::five || combo[1].first == (int)CardDealer::CardPower::four)) { //ace,two�̕��т̏ꍇace��one�ɂ��Ĕz��̍Ō�֊i�[����
		int copy = combo[0].second; //�擪��ace�̃J�[�h�������L��
		combo.erase(combo.begin()); //�擪���폜
		combo.push_back(std::pair<int, int>((int)CardDealer::CardPower::one, copy)); //���ɒǉ�ace��one�ɉ��߂�����ǉ�
	}
	
	int start = combo[0].first - combo[1].first > 0; //��ԋ����J�[�h�Ǝ��̃J�[�h���q�����Ă���ꍇfalse�A�q�����Ă��Ȃ����true���Ԃ�Aint�^�Ȃ̂ő��X0�A1�ɕϊ������
	int changeCount = start; //�q�����ĂȂ��J�[�h�����m�����񐔋L�^�Astart��1�Ȃ�擪�Ǝ����q�����ĂȂ����炱�����1�J�n

	if (straight != -1 && combo[0].first - combo[1].first > 1) { return -1; } //�d���J�[�h�����銎�擪�Ǝ��̃J�[�h�̍���2�ȏ�̏ꍇ�d���J�[�h�Ɛ擪�J�[�h����������K�v������̂ŃX�g���[�g�͖���
	if (straight == -1 && start) { straight = combo[0].first; } //�擪�J�[�h�Ǝ��J�[�h���q�����ĂȂ������ꍇ�����J�[�h�ɐ擪�J�[�h���w��A�d���J�[�h���������ꍇ��������D��
	if (straight == -1) { straight = combo[combo.size() - 1].first == (int)CardDealer::CardPower::one ? (int)CardDealer::CardPower::ace : combo[combo.size() - 1].first; } //�����w�肪�Ȃ��ꍇ��Ԏア�J�[�h����������Aone�̏ꍇace�ɒ����Ă���

	int old = combo[start].first; //�O��̃J�[�h�̋�������
	
	for (int i = start + 1; i < combo.size(); ++i) { //�擪�ȊO�Ɍq�����ĂȂ��������Ȃ����`�F�b�N
		if (old - 1 != combo[i].first) { //�O�񐔒l�����񐔒l�ƌq���炩�������ꍇ
			if (changeCount > 0) { return -1; } //2��ڂ̎��s�Ȃ�X�g���[�g�͕s��
			old = old - 1; //���Ɍq����悤old��⊮���Ă���
			changeCount++; //�q�����ĂȂ��J�[�h�J�E���g
			continue; //��蒼��
		}
		old = combo[i].first;
	}
	if (changeCount <= 0) { return -1; } //�q�����ĂȂ��J�[�h�����m���Ȃ������ꍇ�X�g���[�g�͖����Ƃ����������ł��Ă�

	for (auto itr : hand) { //combo�̓J�[�h���J�[�h�p���[�Ŋi�[���Ă�̂ł����ʏ�J�[�h�ɒ�������
		if (itr % (int)CardDealer::CardPower::max == straight) { return itr; } //�s�v�ȃJ�[�h��hand���̈�v����J�[�h�p���[������΂��̃J�[�h��s�v�ȃJ�[�h�Ƃ��ĕԂ��ďI���
	}
	return 99999; //�����Ȃ��Ǝv�����G���[
}




std::deque<int> CardDealer::HandCheck(const Chara& chara) {
	std::deque<int> point = std::deque<int>();
	deque_map combo = deque_map(); //first=�J�[�h�̋��� second=���̃J�[�h�̖��� �ō\�����ꂽ�J�[�h�i�[�z��
	std::deque<int> hand; //��D�𐔒l�����������i�[
	chara.GetHandNum(hand); //�L���������D�z����擾

	HandComboCheck(hand, combo); //����J�[�h���i�[����


	if (combo.begin()->second == 1) { //�����J�[�h��1�����Ȃ������ꍇ
		int max = HandStraightCheck(combo); //�����\������J�[�h�̒��ōő�J�[�h�p���[�A�X�g���[�g�̗L���`�F�b�N�����˂Ă���
		bool straight = max > 0; //max��0�ȏオ�����Ă���΃X�g���[�g�L��
		bool flash = HandFlashCheck(hand); //�t���b�V���]�����ʂ����Ă���

		point.push_back(combo.begin()->first); //combo����ő�J�[�h�p���[������Ă���
		for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { point.push_back(itr->first); } //�J�[�h�i�[

		if (straight && flash) { //�X�g���[�g�ƃt���b�V�����L���ȏꍇ�Ɍ��胍�C�����`�F�b�N���s��
			if (HandRoyalCheck(combo)) { point[0] = ((int)HandRank::RoyalStraightFlash) * (int)CardPower::max + max; } //���C�������L���������ꍇ���C�����X�g���[�g�t���b�V��
			else { point[0] = ((int)HandRank::StraightFlash) * (int)CardPower::max + max; } //�������ł���΃X�g���[�g�t���b�V��
			return point; //�|�C���g�v�Z�I���
		}
		if (straight) { point[0] = ((int)HandRank::Straight) * (int)CardPower::max + max; return point; } //�X�g���[�g��Ԃ�
		if (flash) { point[0] = ((int)HandRank::Flash) * (int)CardPower::max + point[0]; return point; } //�t���b�V����Ԃ�

		return point; //�|�C���g�v�Z�I���
	}


	if (++combo.begin()->second == 1) { //�J�[�h���y�A(aaa33�̂悤�ɓ����J�[�h�̑g���ł��Ă�A�����y�A�͑ΏۊO)�ł͂Ȃ��ꍇ
		HandRank rank = HandRank::OnePair; //�����J�[�h�̖����ɉ����ă����N������A��芸���������y�A
		if (combo.begin()->second == 3) { rank = HandRank::ThreeCard; } //3������΃X���[�J�[�h
		if (combo.begin()->second == 4) { rank = HandRank::FourCard; } //4���Ȃ�΃t�H�[�J�[�h

		point.push_back(((int)rank) * (int)CardPower::max + combo.begin()->first); //�����N�ɉ��������_����
		for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { point.push_back(itr->first); } //�]�����J�[�h������
		return point; //�|�C���g�v�Z�I���
	}
	

	//�c��̓y�A�̏ꍇ�̓_�v�Z�̂�
	point.push_back(((int)(combo.begin()->second == 3 ? HandRank::FullHause : HandRank::TwoPair)) * (int)CardPower::max + combo.begin()->first); //�����J�[�h��3���������ꍇ�t���n�E�X�A�����łȂ��Ȃ�c�[�y�A
	for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { point.push_back(itr->first); } //�]�����J�[�h������
	return point; //�|�C���g�v�Z�I���
}

int CardDealer::ReachCheck(const Chara& chara) {
	deque_map combo = deque_map(); //first=�J�[�h�̋��� second=���̃J�[�h�̖��� �ō\�����ꂽ�J�[�h�i�[�z��
	std::deque<int> hand; //��D�𐔒l�����������i�[
	chara.GetHandNum(hand); //�L���������D�z����擾
	HandComboCheck(hand, combo); //����J�[�h���i�[����

	int flash = HandFlashReachCheck(hand); //�t���b�V�������ɕs�v�ȃJ�[�h
	int straight = HandStraightReachCheck(combo, hand); //�X�g���[�g�����ɕs�v�ȃJ�[�h

	if (flash > -1 && straight > -1) { //�X�g���[�g�A�t���b�V�������\�������ꍇ
		if (flash % (int)CardDealer::CardPower::max == straight % (int)CardDealer::CardPower::max) { straight = flash; } //�X�g���[�g�̕ύX�J�[�h�ɏd���J�[�h���������ꍇ2�̃J�[�h�̓�hand�v�f�̎Ⴂ����Ԃ��̂����Aflash�Ɨv���J�[�h�p���[���ꏏ�������Ȃ�flash�̃J�[�h�ɍ��킹��
		return GetRand(1) ? flash : straight; //�����q�b�g�����ꍇ�ǂ����Ԃ�����GetRand�Ń����_�����肷��
	}

	return flash == -1 ? straight : flash; //-1����Ȃ�����Ԃ��A����-1�̏ꍇstraight��Ԃ������g�͂ǂ������ꏏ������֌W�Ȃ�
}
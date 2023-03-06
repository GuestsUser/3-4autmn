#include <DxLib.h>
#include "PK_ShowDown.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Player.h"
#include "CardDealer.h"
#include "PokerFontData.h"

#include "Cmp_BetActionRecord.h"
#include "../Code/Component/ComponentArray.h"

Poker::ShowDown::ShowDown(Poker& set) :parent(&set), count(0), actionRecord(std::deque<Cmp_BetActionRecord*>((int)Poker::Character::length)), hand(std::deque<std::deque<int>>((int)Poker::Character::length, std::deque<int>(5))), handPos(std::deque<Vector3>((int)Poker::Character::length)), handString(std::deque<std::string>((int)Poker::Character::length)) {
	titlePos.SetXYZ(513, 189, 0); //�V���[�_�E���ł��鎖���������b�Z�[�W�̈ʒu�ݒ�

	//��D����\������ׂ̈ʒu�ݒ�
	handPos[0].SetXYZ(108, 382, 0);
	handPos[1].SetXYZ(455, 28, 0);
	handPos[2].SetXYZ(1012, 28, 0);
	handPos[3].SetXYZ(1039, 377, 0);
	handPos[4].SetXYZ(497, 400, 0);

	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}

void Poker::ShowDown::Update() {

	if (count == 60) {
		for (int i = 0; i < actionRecord.size(); ++i) { //�e�L�������`�F�b�N�������D�����J���鏈��
			if (IsFold(*actionRecord[i])) { continue; } //�Q�[�����珜�O����Ă����ꍇ�ȉ������͎��s���Ȃ�
			for (auto itr : *parent->chara[i]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::front); } //�����܂ł��ꂽ�L�����̓J�[�h��\���\����
		}
	}

	if (count == 120) {
		for (int i = 0; i < parent->chara.size(); ++i) { //�n���h�]�����s��
			hand[i] = CardDealer::HandCheck(*parent->chara[i]); //�e�L�����̎�D�]��������
			handString[i] = Hand2String(hand[i]); //�e�L�����̊������𕶎��񉻂��������i�[
		}
	}

	if (count == 180) {
		std::deque<Chara*> enableChara = std::deque<Chara*>(); //�������s���L�����Z��
		std::deque<Chara*> foldChara = std::deque<Chara*>(); //�t�H�[���h�����L�����Z��(�s�k�ς݂͏���)

		std::deque<std::deque<int>> enableHand = std::deque<std::deque<int>>(); //�������s���L�����̃n���h�]���Z��

		for (int i = 0; i < parent->chara.size(); ++i) { //�L����������������L�����Afold�L�����A���O�L�����Ɏd������
			if (actionRecord[i]->GetIsLose()) { continue; } //�s�k�ς݂̏ꍇ�����������L�����ֈڍs
			if (actionRecord[i]->GetActionRecord(Cmp_BetActionRecord::Action::fold)) { foldChara.push_back(parent->chara[i]); continue; } //fold���Ă�ꍇfoldCara�֊i�[�����L�����ֈڍs
			enableChara.push_back(parent->chara[i]); //���݃L������enableChara�֊i�[
			enableHand.push_back(hand[i]); //���݃L�����̃n���h�]���i�[
		}


		while (enableChara.size() > 0) { //enableChara�S�ĂɎx�����I����܂Ŏ��s
			std::deque<int> max = std::deque<int>(1, 0); //����x�����s���L�����̓Y�����W�A��芸�����v�f��1�Ŋi�[�l��0

			for (int i = 1; i < enableChara.size(); ++i) { //��ԋ����������L���������肷��
				if (enableHand[max[0]][0] > enableHand[i][0]) { continue; } //�ŋ��L�������ς�炸�ō��ł���ꍇ��蒼��
				if (enableHand[max[0]][0] < enableHand[i][0]) { max = std::deque<int>(1, i); continue; } //����̖��̕��������ꍇ�x�����s���L����������̕��ɕύX

				//�����܂ŗ����ꍇ���̋����͓����Ȃ̂Ŗ����Ȃ��Ȃ��J�[�h�̋����ŋ�����`�F�b�N����
				int sameCount; //���ݍŋ��L�����ƍ���L�����̓��������̃J�[�h����
				for (sameCount = 1; sameCount < enableHand[max[0]].size(); ++sameCount) { //�\���J�[�h�S�Ă��`�F�b�N
					if (enableHand[max[0]][sameCount] % (int)CardDealer::CardPower::max != enableHand[i][sameCount] % (int)CardDealer::CardPower::max) { break; } //�����̈Ⴄ�J�[�h�ɓ��������璆�f
				}
				if (sameCount >= enableHand[max[0]].size()) { max.push_back(i); continue; } //�S�ẴJ�[�h�����������Ȃ獡��L�������x�����ΏۂƂ��Ĕz��ɒǉ�����
				if (enableHand[max[0]][sameCount] % (int)CardDealer::CardPower::max < enableHand[i][sameCount] % (int)CardDealer::CardPower::max) { max = std::deque<int>(1, i); continue; } //����L�����̍\���J�[�h�̕���������΍ŋ��L����������̕��Ɍ���
			}

			//�f�o�b�O�p
			//std::deque<int> max = std::deque<int>(); //����x�����s���L�����̓Y�����W�A��芸�����v�f��1�Ŋi�[�l��0
			//for (int i = 0; i < enableChara.size(); ++i) { max.push_back(i); }

			std::deque<int> copy = max; //max��ҏW����ׂ̃R�s�[
			if (copy.size() == 1) { //�v�f��1�����Ȃ��ꍇ
				enableChara[copy[0]]->SetCoin(enableChara[copy[0]]->GetCoint() + parent->pot->PayOut(*enableChara[copy[0]])); //�����z�����
				copy.erase(copy.begin()); //�v�f����
			}
			else { std::sort(copy.begin(), copy.end(), [=](int a, int b) { return parent->pot->Inquiry(*enableChara[copy[a]]) < parent->pot->Inquiry(*enableChara[copy[b]]); }); } //�x���z�̏����\�[�g

			while (copy.size() > 0) { //copy����ɂȂ�܂ő�����
				std::deque<Chara*> same = std::deque<Chara*>(1, enableChara[copy[0]]); //�x���z����̃L�����܂Ƃ�
				int pay = parent->pot->Inquiry(*same[0]); //����̎x���z
				for (int i = 1; i < copy.size(); ++i) { //����x���z�Ɠ���̃L�����T��
					if (pay == parent->pot->Inquiry(*enableChara[copy[i]])) { same.push_back(enableChara[copy[i]]); } //����Ȃ�z��֊i�[
				}

				pay = parent->pot->PayOut(*same[0]) / same.size(); //�x���������s�A����x���z�L�����̐��������z���𓙕�
				for (int i = 0; i < same.size(); ++i) { //����x���z�̊e�L�����֎x����
					same[i]->SetCoin(same[i]->GetCoint() + pay); //����x���z�̃L�����֔z��
					for (int j = 0; j < copy.size(); ++j) { //�x�������L������copy���珜�O����ׂ̃��[�v
						if (enableChara[copy[j]] == same[i]) { copy.erase(copy.cbegin() + j); break; } //����x�������L������copy���珜�O
					}
				}

			}

			if (parent->pot->TotalAmount() <= 0) { ++count; return; } //�x�����̌��ʃ|�b�g�����z��0�ɂȂ����ꍇ���̎��_�ŏI���

			std::deque<Chara*> maxChara = std::deque<Chara*>(); //max�����enableChara������o��������ێ�����z��
			for (int i = 0; i < max.size(); ++i) { maxChara.push_back(enableChara[max[i]]); } //maxChara�֑Ή�Chara�Q�Ƃ��i�[


			for (int i = 0; i < maxChara.size(); ++i) { //����x���z�̊e�L�����֎x����
				for (int j = 0; j < enableChara.size(); ++j) { //�x�������L������copy���珜�O����ׂ̃��[�v
					if (enableChara[j] == maxChara[i]) { //enableChara���̂ǂ̗v�f���g���������肷��
						enableChara.erase(enableChara.begin() + j); //�Ή��v�f��enable���珜�O
						enableHand.erase(enableHand.begin() + j); //hand�̕��������Ă���
						break;
					}
				}
			}
		}
		FoldMemberPayOut(foldChara, *parent->pot); //�]����pot��fold�L�����֕��z

	}

	if (count == 240) {
		parent->run = parent->list[(int)Poker::Section::ini]; //�ŏ��̏�Ԃɖ߂�
		count = -1; //�J�E���g���Z�b�g

		LoseSet(parent->chara, actionRecord); //�s�k�󋵂̐ݒ�
		Poker::Section next = GameEndCheck(parent->chara, actionRecord); //�s�k�󋵂��玟�������ׂ��V�[�����擾

		if (next != Poker::Section::ini) { //ini(���s���ׂ�)�ȊO���������ꍇ
			parent->run = parent->list[(int)next]; //���̃V�[���Ɉڍs
			count = -1; //�J�E���g���Z�b�g
			return; //�I���
		}

	}

	++count;
}

void Poker::ShowDown::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "�V���[�_�E��!!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));

	if (count >= 120) {
		for (int i = 0; i < actionRecord.size(); ++i) { //�����ɒ��񂾃L�����̃n���h��\������
			if (IsFold(*actionRecord[i])) { continue; } //�Q�[�����珜�O����Ă����ꍇ�ȉ������͎��s���Ȃ�
			DrawStringToHandle(handPos[i].GetX(), handPos[i].GetY(), handString[i].c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal)); //�n���h�\��
		}
	}


}
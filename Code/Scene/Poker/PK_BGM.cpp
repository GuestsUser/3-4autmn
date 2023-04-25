#include "DxLib.h"
#include "PK_BGM.h"

#include "Cmp_Sound.h"

#include <algorithm>
#include <random>

void BGMListShuffle(std::deque<Cmp_Sound*>& bgm) {
	std::shuffle(bgm.begin(), bgm.end(), std::mt19937(std::random_device()())); //bgm���V���b�t��
}


PK_BGM::PK_BGM(Cmp_Transform ts) :bgm(std::deque<Cmp_Sound*>()), coolTime(90), count(0), runSub(0), resumeMemo(-1), ts(ts) {
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm1.wav"), -1, -1, false, &this->ts)); //�Ȃ̓���
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm2.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm3.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm4.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm5.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm6.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm7.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm8.wav"), -1, -1, false, &this->ts));

	ChangeVolumeSoundMem(255 * 0.55, bgm[0]->GetHandle()); //���ʐݒ�
	ChangeVolumeSoundMem(255 * 0.55, bgm[1]->GetHandle()); //���ʐݒ�
	ChangeVolumeSoundMem(255 * 0.55, bgm[2]->GetHandle()); //���ʐݒ�
	ChangeVolumeSoundMem(255 * 0.55, bgm[3]->GetHandle()); //���ʐݒ�
	ChangeVolumeSoundMem(255 * 0.5, bgm[4]->GetHandle()); //���ʐݒ�
	ChangeVolumeSoundMem(255 * 0.7, bgm[5]->GetHandle()); //���ʐݒ�
	ChangeVolumeSoundMem(255 * 0.5, bgm[6]->GetHandle()); //���ʐݒ�
	ChangeVolumeSoundMem(255 * 0.6, bgm[7]->GetHandle()); //���ʐݒ�


	BGMListShuffle(bgm); //�z����V���b�t��
}

void PK_BGM::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~�Ȃ���s���Ȃ�

	if (count == 0) { //���Ԍo�߂�0�̏ꍇ���܂ŋȂ�����Ă����̂ō���Ȃ��~�܂��Ă��܂������`�F�b�N
		for (auto itr : bgm) {
			if (CheckSoundMem(itr->GetHandle()) == 1) { return; } //����Ă���Ȃ��������ꍇUpdate���I��
		}
	}

	++count; //�����܂ŗ����΋Ȃ͎~�܂��Ă���̂ŃJ�E���g�o��

	if (count > coolTime) { //�J�E���g��coolTime�𒴂�����
		if (runSub >= bgm.size()) { //�S�Ă̋Ȃ��Đ����I�����ꍇ
			Reset(); //�Ȃ̍Đ�����Đ��J�n�ʒu��������
			SetRunUpdate(true); //������~�����Ȃ�
		}
		bgm[runSub]->Play(); //runSub�̋Ȃ��Đ�
		++runSub; //�Y������1�i�߂Ď��̋Ȃ̍Đ�����

		count = 0; //�J�E���g���Z�b�g
	}
}

void PK_BGM::Reset() {
	for (auto itr : bgm) { 
		StopSoundMem(itr->GetHandle()); //�Ȏ~��
		SetCurrentPositionSoundMem(0, itr->GetHandle()); //�Đ��ʒu�̏�����
	}
	SetRunUpdate(false); //�S�Ď~�߂Ă�Update�J�n�Ɠ�����count�������n�܂��Ă��܂��̂ŊJ�n�^�C�~���O���R���g���[�����ׂ�isUpdate��false�ɐݒ肷��
	BGMListShuffle(bgm); //���X�g�̏��Ԃ�V��������
	runSub = 0; //�Đ��Y�������ŏ�����ɍ��킹��
	count = 0; //�J�E���g���Z�b�g
	resumeMemo = -1; //���т��V�����Ȃ����̂őO��L�^�������|�����ĂȂ���ԂɃ��Z�b�g
}

void PK_BGM::Stop() {
	resumeMemo = -1; //memo�̋L�^�������|�����ĂȂ���ԂɃ��Z�b�g
	for (int i = 0; i < bgm.size(); ++i) {
		if (CheckSoundMem(bgm[i]->GetHandle())) { //����̋Ȃ��|�����Ă����ꍇ 
			resumeMemo = i; //memo�֋L�^
			StopSoundMem(bgm[resumeMemo]->GetHandle()); //�Đ�����bgm���~�߂�
			break; //�z��`�F�b�N�I���
		}
	}
}
void PK_BGM::Resume() {
	if (resumeMemo != -1) { bgm[resumeMemo]->Play(); } //memo�̋ȍĐ����ĊJ
}

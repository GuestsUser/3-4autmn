#pragma once
#include "Component.h"
#include "Cmp_Sound.h"

#include "Cmp_Transform.h"

#include <deque>

class PK_BGM :public Component {
	std::deque<Cmp_Sound*> bgm; //�Đ�bgm���X�g
	Cmp_Transform ts; //�ێ�bgm�̈ʒu�����肷��transform

	int coolTime; //bgm���~�܂��Ă���󋵂��炱�̎��ԕ��ҋ@���ĐV����bgm���Đ�����
	int count; //coolTime���̎��Ԍo�߂��v��ׂ̃J�E���g
	int runSub; //bgm���X�g���̂��̓Y�����̋Ȃ𗬂�

	int resumeMemo; //Stop�����s�������|�����Ă����Ȃ̓Y������ێ��A�����|�����ĂȂ������ꍇ-1������
public:
	PK_BGM(Cmp_Transform ts = Cmp_Transform());

	void Update(); //bgm���ɂ���Ȃ�A���ŗ���Update

	void FullReset() { Reset(); }
	void Reset(); //�S�Ă̋Ȃ��~�߁A�Đ��J�n�ʒu�����ɖ߂��A�e��ێ��ϐ�����������Update���s��؂�ABGM�������ĊJ�������^�C�~���O��Update���s���ĊJ����Ƃ悵

	void Stop(); //bgm���~�߂�
	void Resume(); //�~�߂�bgm���ĊJ����
};
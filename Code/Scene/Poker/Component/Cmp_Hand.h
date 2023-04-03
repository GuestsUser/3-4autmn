#pragma once
#include "Component.h"
#include <deque>
#include <string>

class PK_Card;
class PK_Chara;

class Cmp_Hand :public Component {
public:
	using deque_map = std::deque<std::pair<int, int>>; //deque���g�p�����ɂ��}�b�v�Amap��unorded_map��sort�ɑΉ����ĂȂ��̂ŗp��
	enum class HandRank { No, OnePair, TwoPair, ThreeCard, Straight, Flash, FullHause, FourCard, StraightFlash, RoyalStraightFlash }; //���̋�����
	enum class CardPower { one = -1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, max }; //�J�[�h���l�̋�����

private:
	std::deque<PK_Card*> card; //�摜�\���Ɏg���鏊���J�[�h����
	std::deque<int> handPower; //��L�z���Hand�Ƌ����r�ł���悤�����������A��������[0]�ɁA���ɂȂ��ĂȂ��J�[�h�̋���������ȍ~�Ɋi�[
	std::string handName; //�������̖��O��ێ�
public:
	Cmp_Hand();
	~Cmp_Hand();

	void Update();
	void Draw();
	void FullReset();
	void Reset();

	void HandPowerUpdate(); //�Ăяo����handPower�����݂�card�ɍ��킹�����ɕύX

	const std::deque<PK_Card*>* ReadCard() const { return &card; } //�J�[�h�z����o���A�ǂݏo����p
	std::deque<PK_Card*>* EditCard() { return &card; } //�J�[�h�z����o���A�ҏW�\

	std::deque<int> GetHandPower() const { return handPower; } //��Hand�Ƌ����r�ł���悤�ɂ����J�[�h�z���Ԃ�
	std::string GetHandName() const { return handName; } //�����𖼂�Ԃ�
	PK_Card* ReachCheck(); //�t���b�V���Ⴕ���̓X�g���[�g������1���Ŋ�������Ȃ�s�v�ȃJ�[�h��Ԃ��A�������Ȃ��Ȃ�-1�ŕԂ��A�s�v�ȃJ�[�h���X�g���[�g���t���b�V�����ňႤ�ꍇ�ǂ����Ԃ��������Ń����_�����肷��
};
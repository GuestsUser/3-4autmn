#pragma once
#include <deque>
#include <random>
#include <utility>

class Chara;

class CardDealer {
public:
	using deque_map = std::deque<std::pair<int, int>>; //deque���g�p�����ɂ��}�b�v�Amap��unorded_map��sort�ɑΉ����ĂȂ��̂ŗp��
	enum class HandRank { No, OnePair, TwoPair, ThreeCard, Straight, Flash, FullHause, FourCard, StraightFlash, RoyalStraightFlash }; //���̋�����
	enum class CardPower { one = -1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, max }; //�J�[�h���l�̋�����
private:
	std::mt19937 gen; //�����_���l�����@
	std::deque<int> deck; //�R�D
	int top; //�R�D�̈�ԏ�������Y����
public:
	CardDealer();
	void Reset(); //���E���h�I�����ɌĂяo���A�R�D�̏����������s���Ă����

	int DeckDraw(); //�R�D����1�����������ʎ�ɓ������J�[�h��Ԃ��A���s����ƎR�D������
	static std::deque<int> HandCheck(const Chara& chara); //�����D��n���Ɗ�������[0]�ɁA���ɂȂ��ĂȂ��J�[�h�̋���������ȍ~�Ɋi�[�����z��ŕԂ��Ă����
	static int ReachCheck(const Chara& chara); //�t���b�V���Ⴕ���̓X�g���[�g������1���Ŋ�������Ȃ�s�v�ȃJ�[�h��Ԃ��A�������Ȃ��Ȃ�-1�ŕԂ��A�s�v�ȃJ�[�h���X�g���[�g���t���b�V�����ňႤ�ꍇ�ǂ����Ԃ��������Ń����_�����肷��
};
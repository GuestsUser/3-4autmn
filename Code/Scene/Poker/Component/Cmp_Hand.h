#pragma once
#include "Component.h"
#include <deque>
#include <string>

class PK_Card;
class PK_Chara;

class Cmp_Hand :public Component {
public:
	using deque_map = std::deque<std::pair<int, int>>; //dequeを使用したにせマップ、mapもunorded_mapもsortに対応してないので用意
	enum class HandRank { No, OnePair, TwoPair, ThreeCard, Straight, Flash, FullHause, FourCard, StraightFlash, RoyalStraightFlash }; //役の強さ順
	enum class CardPower { one = -1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, max }; //カード数値の強さ順

private:
	std::deque<PK_Card*> card; //画像表示に使われる所持カード実体
	std::deque<int> handPower; //上記配列を他Handと強弱比較できるよう調整した物、完成役を[0]に、役になってないカードの強さをそれ以降に格納
	std::string handName; //完成役の名前を保持
public:
	Cmp_Hand();
	~Cmp_Hand();

	void Update();
	void Draw();
	void FullReset();
	void Reset();

	void HandPowerUpdate(); //呼び出しでhandPowerを現在のcardに合わせた物に変更

	const std::deque<PK_Card*>* ReadCard() const { return &card; } //カード配列取り出し、読み出し専用
	std::deque<PK_Card*>* EditCard() { return &card; } //カード配列取り出し、編集可能

	std::deque<int> GetHandPower() const { return handPower; } //他Handと強弱比較できるようにしたカード配列を返す
	std::string GetHandName() const { return handName; } //完成役名を返す
	PK_Card* ReachCheck(); //フラッシュ若しくはストレートがあと1枚で完成するなら不要なカードを返す、完成しないなら-1で返す、不要なカードがストレートかフラッシュかで違う場合どちらを返すか内部でランダム決定する
};
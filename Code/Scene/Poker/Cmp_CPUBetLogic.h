#pragma once
#include "../Code/Component/Component.h"
#include "Cmp_BetActionRecord.h"
#include <deque>

class Chara;
class PK_Dealer;

class Cmp_CPUBetLogic :public Component {
	std::deque<int> borderBase; //レイズ基準の元データ、ランダム範囲の形式で格納されており、基準更新の際この数値をランダム範囲としてランダム決定される
	std::deque<int> raiseBorderBase; //自主レイズを行う手の強さの基準
	std::deque<int> border; //レイズ基準、手の強さが格納されており、手の強さ以下の要素のpayLimitを使用する
	std::deque<int> raiseBorder; //自主レイズを行う手の強さ、borderにこの数値を加算した値を超えていれば自主レイズを行う

	std::deque<int> payLimit; //レイズ基準に対応したレイズ可能回数
	std::deque<int> raiseSplit; //レイズを行う際、この配列の要素数分だけレイズを分割して行う、配列の中身の値をレイズする
	bool raiseActive; //trueで自主レイズを行う

	int changeTiming; //基準更新タイミング、ゲーム実行回数がこの数値の余り0になったら基準更新
	int changeTimingLimit; //上記基準タイミングのランダム幅最大値 
	int oldGameCount; //基準を更新したゲームカウントを記録する

	PK_Dealer* dealer; //ディーラーの参照を持つ
public:
	Cmp_CPUBetLogic(PK_Dealer& setDealer);
	void Reset(); //ラウンド開始時に呼び出すとレイズ分割数とラウンド回数に応じて基準のリセットをしてくれる
	void FullReset() { Reset(); } //Resetと処理内容は同じ
	void Update() {}

	void RaiseVolDecision(const Chara& chara, bool isCheckReach); //ハンドの評価結果を引数に与える事でそれに応じたレイズ可能回数を決定する関数、boolにtrueを入れるとリーチチェックも加味した結果となる

	const std::deque<int>* ReadRaiseSplit() const { return &raiseSplit; } //分割レイズ数を記録した配列を読み取り専用で返す
	bool GetSelfRaise() { return raiseActive; } //自主レイズするか否かを返す
};
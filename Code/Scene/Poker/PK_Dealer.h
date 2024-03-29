#pragma once
#include "Btn.h"


class PK_Dealer { //ポーカーに関する色々なデータを管理するディーラーなクラス
	Btn btn; //ボタンポジション

	int baseBB; //初期BB、ラウンドが1巡するとBBはこの数値分上昇する
	int maxBet; //現在BBから最大何倍まで掛けられるかを示す数値
	int currentMaxBet; //現在の最大ベットがBBの何倍か格納する

	int BB; //現在BB
	int gameCount; //現在のラウンド数
	int playSub; //現在アクションを行うキャラの添え字を記録

public:
	PK_Dealer();
	void Draw(); //ボタンポジションを描写する

	void Reset(); //新しいラウンド開始時に呼び出す
	void FullReset(); //ゲームを再スタートする為の完全初期化

	int GetBB() const { return BB; } //現在BBを取得
	int GetMaxBet() const { return maxBet; } //maxBetを取得
	int GetCurrentMaxBet() const { return currentMaxBet; } //現在最大ベットを取得
	int GetGameCount() const { return gameCount; } //現在のゲーム回数を取得
	int GetActionCharaSub() const { return playSub; } //今回アクションさせるキャラの添え字を取得

	const Btn* ReadBtn() const { return &btn; } //ボタンポジションを読み取り専用形式で取得

	void SetCurrentMaxBet(int set) { currentMaxBet = set; } //最大ベットを更新する
	void SetActionChara(int set); //次アクションを行うキャラを設定する
};
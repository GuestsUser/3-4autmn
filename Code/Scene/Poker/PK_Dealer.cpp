#include "DxLib.h"

#include "Btn.h"
#include "PK_Dealer.h"
#include "Poker.h"
#include "PokerFontData.h"

#include <string>

PK_Dealer::PK_Dealer() :btn(Btn()), baseBB(100), addBB(50), maxBet(10) { FullReset(); } //maxBetはゲーム中変化しないのでFullResetには含めずこちらで10と定義しておく

void PK_Dealer::Draw() {
	btn.Draw(); //ボタン画像の描写
	DrawStringToHandle(554, 247, ("BB:" + std::to_string(BB)).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
}

void PK_Dealer::Reset() {
	++gameCount; //ラウンド数を増加する

	BB = baseBB + addBB * ((int)(gameCount / (int)Poker::Character::length)); //1巡したらBBをaddBB分増加させる

	btn.Reset(); //ボタンポジションもリセットする
	SetActionChara(btn.GetBtnPos() + 1); //最初にアクションを行うキャラをボタンポジションの次のキャラに設定する
}

void PK_Dealer::FullReset() {
	BB = baseBB; //BBを初期値に設定
	gameCount = 0; //ラウンド数を0に設定
	btn.FullReset(); //ボタンポジションもFullReset
	SetActionChara(btn.GetBtnPos() + 1); //最初にアクションを行うキャラをボタンポジションの次のキャラに設定する
}

void PK_Dealer::SetActionChara(int set) { playSub = set % (int)Poker::Character::length; }
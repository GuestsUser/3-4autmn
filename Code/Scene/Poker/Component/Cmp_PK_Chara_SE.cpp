#include "DxLib.h"
#include "Cmp_PK_Chara_SE.h"

#include "PK_Dealer.h"
#include "Cmp_Sound.h"

int Cmp_PK_Chara_SE::fewBorder = 7; //レイズ数がこの数値未満の場合コイン取得音にfewを使う


Cmp_PK_Chara_SE::Cmp_PK_Chara_SE(const Cmp_Transform* const soundPos) :soundPos(Cmp_Transform()) {
	if (soundPos != nullptr) { this->soundPos = *soundPos; } //位置情報を受け取っていた場合その情報をコピーする

	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/call.wav"), -1, -1, true, &this->soundPos)); //seを導入する
	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/fold.wav"), -1, -1, true, &this->soundPos));
	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/raise.wav"), -1, -1, true, &this->soundPos));
	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/cardChange.wav"), -1, -1, true, &this->soundPos));
	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/cardOpen.wav"), -1, -1, true, &this->soundPos));
	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/cardPlace.wav"), -1, -1, true, &this->soundPos));
	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/coinFew.wav"), -1, -1, true, &this->soundPos));
	sound.push_back(new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/coinMany.wav"), -1, -1, true, &this->soundPos));

	ChangeVolumeSoundMem(255 * 0.9, sound[0]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 1, sound[1]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 1, sound[2]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 1, sound[3]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 1, sound[4]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 1, sound[5]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 1, sound[6]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 0.9, sound[7]->GetHandle()); //音量設定


}

Cmp_PK_Chara_SE::Request Cmp_PK_Chara_SE::UseCoinSound(int pay, PK_Dealer& dealer) { //pay金額がボーダー以上ならmanyを、未満ならfewをrequest形式で返す
	return fewBorder <= (float)pay / dealer.GetBB() ? Cmp_PK_Chara_SE::Request::coinMany : Cmp_PK_Chara_SE::Request::coinFew;
}

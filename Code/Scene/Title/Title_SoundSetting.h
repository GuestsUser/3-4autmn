#pragma once

class Cmp_Sound;

class Title_SoundSetting {
public:
	static void SetUpTitleSelectBGM(Cmp_Sound& sound); //soundに入れられたサウンドにタイトルのbgm向けステータスを設定する
	static void SetUpTitleClick(Cmp_Sound& sound); //soundに入れられたサウンドにタイトル画面のクリック向けステータスを設定する


private:
	//実体精製禁止
	Title_SoundSetting() = delete;
	Title_SoundSetting(const Title_SoundSetting&) = delete;
};

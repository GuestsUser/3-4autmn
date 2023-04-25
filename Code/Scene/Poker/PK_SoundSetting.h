#pragma once
class Cmp_Sound;

class PK_SoundSetting {
public:
	static void SetUpCardPlace(Cmp_Sound& sound); //カード配布音としてステータスを設定
	static void SetUpFold(Cmp_Sound& sound); //foldした時の音としてステータスを設定
	static void SetUpCall(Cmp_Sound& sound); //callした時の音としてステータスを設定
	static void SetUpRaise(Cmp_Sound& sound); //raiseした時の音としてステータスを設定
	static void SetupCardChange(Cmp_Sound& sound); //カード交換した時の音としてステータスを設定
	static void SetupHandOpen(Cmp_Sound& sound); //手札公開した時の音としてステータスを設定
	static void SetUpCoinMany(Cmp_Sound& sound); //soundに入れられたサウンドにコイン入手(大量)se向けステータスを設定する
	static void SetUpCoinFew(Cmp_Sound& sound); //soundに入れられたサウンドにコイン入手(少量)se向けステータスを設定する
private:
	//実体精製禁止
	PK_SoundSetting() = delete;
	PK_SoundSetting(const PK_SoundSetting&) = delete;

};
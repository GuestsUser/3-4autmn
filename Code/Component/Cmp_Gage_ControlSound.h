#pragma once
#include "Component.h"

class Gage;
class Cmp_Sound;

class Cmp_Gage_ControlSound :public Component { //ゲージ量が変化した時soundを鳴らすGage向け追加機能
	Gage* parent; //このコンポーネントを持つ親
	const Cmp_Sound* const sound; //鳴らすサウンド
	float oldVol; //前フレームのゲージ量

	bool isSoundStop; //trueの間はUpdateは実行するがサウンドは鳴らさない
	bool isSelfSoundDel; //trueならsoundの削除管理はこちらで行う

public:
	Cmp_Gage_ControlSound(Gage* parent, const Cmp_Sound* const sound, bool isSelfSoundDel) :parent(parent), sound(sound), oldVol(0), isSoundStop(true), isSelfSoundDel(isSelfSoundDel) {}
	~Cmp_Gage_ControlSound();

	void FullReset() { Reset(); }
	void Reset();

	void Update();
	void SetSoundStop(bool set) { isSoundStop = set; } //ゲージ操作による音鳴らしを行うかどうか設定
};
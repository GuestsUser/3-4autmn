#include "Cmp_Gage_ControlSound.h"

#include "Cmp_Sound.h"
#include "Gage.h"


Cmp_Gage_ControlSound::~Cmp_Gage_ControlSound() {
	if (isSelfSoundDel) { delete sound; } //削除管理を行う指令が出ていればこちらで削除する
}

void Cmp_Gage_ControlSound::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止状態なら終わり

	float vol = parent->GetVol(); //現在ゲージ取得
	if (vol == oldVol) { return; } //ゲージ操作なければ終わり

	oldVol = vol; //前回値を更新
	if (isSoundStop) { return; } //音鳴らし停止命令が出ていれば終わり

	sound->Play(); //サウンドを鳴らす
}

void Cmp_Gage_ControlSound::Reset() { 
	oldVol = parent->GetVol(); //前回値を現在ゲージに強制的に合わせる
	isSoundStop = true; //サウンドは鳴らない状態に設定
}

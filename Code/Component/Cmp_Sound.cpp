#include "DxLib.h"

#include "Component.h"
#include "Cmp_Sound.h"
#include "Cmp_Transform.h"

#include "ConstVal.h"

#include <cmath>

Cmp_Sound::Cmp_Sound(const int& handle, int rad, int playType, int topPositionFlag, Cmp_Transform* ts) :handle(handle), rad(rad), ts(ts), playType(playType), topPositionFlag(topPositionFlag), isSelfTs(true) {
	if (ts == nullptr) { this->ts = new Cmp_Transform(); } //tsに何も入ってなければ新たに作成する
	else { isSelfTs = false; } //外部から渡された場合削除管理はこちらで行わない
	if (this->rad == -1) { this->rad = std::sqrt(std::pow(WINDOW_X, 2) + std::pow(WINDOW_Y, 2)); } //radの初期値設定、画面全体を半径に設定
	if (this->playType == -1) { this->playType = DX_PLAYTYPE_BACK; } //playTypeの初期値設定、playした時その終了を待たない
	SetRad(this->rad); //半径情報を反映する
}

Cmp_Sound::~Cmp_Sound() {
	if (isSelfTs) { delete ts; } //こちらで管理する事になってた場合削除
	DeleteSoundMem(handle); //読み込んだサウンドの開放
}

void Cmp_Sound::Play()const {
	Set3DPositionSoundMem(VGet(ts->ReadPos().GetX(), ts->ReadPos().GetY(), ts->ReadPos().GetZ()), handle); //3d空間上にサウンドを設定
	PlaySoundMem(handle, playType, topPositionFlag); //サウンド鳴らし
}

void Cmp_Sound::Stop()const { StopSoundMem(handle); }

void Cmp_Sound::SetRad(float set) { 
	rad = set; //半径設定
	Set3DRadiusSoundMem(rad, handle); //設定を反映
}
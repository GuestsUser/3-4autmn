#pragma once

class Cmp_Sound;
class Cmp_Transform;

class SoundSetting {
public:
	static Cmp_Sound* CreateDefaultButtonClickSound(Cmp_Transform* ts = nullptr); //ボタンクリックされた時の音を作成して返す

private:
	//実体精製禁止
	SoundSetting() = delete;
	SoundSetting(const SoundSetting&) = delete;

};
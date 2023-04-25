#include "DxLib.h"
#include "PK_BGM.h"

#include "Cmp_Sound.h"

#include <algorithm>
#include <random>

void BGMListShuffle(std::deque<Cmp_Sound*>& bgm) {
	std::shuffle(bgm.begin(), bgm.end(), std::mt19937(std::random_device()())); //bgmをシャッフル
}


PK_BGM::PK_BGM(Cmp_Transform ts) :bgm(std::deque<Cmp_Sound*>()), coolTime(90), count(0), runSub(0), resumeMemo(-1), ts(ts) {
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm1.wav"), -1, -1, false, &this->ts)); //曲の導入
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm2.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm3.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm4.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm5.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm6.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm7.wav"), -1, -1, false, &this->ts));
	bgm.push_back(new Cmp_Sound(LoadSoundMem("Resource/bgm/Poker_BGM/bgm8.wav"), -1, -1, false, &this->ts));

	ChangeVolumeSoundMem(255 * 0.55, bgm[0]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 0.55, bgm[1]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 0.55, bgm[2]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 0.55, bgm[3]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 0.5, bgm[4]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 0.7, bgm[5]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 0.5, bgm[6]->GetHandle()); //音量設定
	ChangeVolumeSoundMem(255 * 0.6, bgm[7]->GetHandle()); //音量設定


	BGMListShuffle(bgm); //配列をシャッフル
}

void PK_BGM::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止なら実行しない

	if (count == 0) { //時間経過が0の場合今まで曲が流れていたので今回曲が止まってしまったかチェック
		for (auto itr : bgm) {
			if (CheckSoundMem(itr->GetHandle()) == 1) { return; } //流れている曲があった場合Updateを終了
		}
	}

	++count; //ここまで来れれば曲は止まっているのでカウント経過

	if (count > coolTime) { //カウントがcoolTimeを超えたら
		if (runSub >= bgm.size()) { //全ての曲を再生し終えた場合
			Reset(); //曲の再生順や再生開始位置を初期化
			SetRunUpdate(true); //動作を停止させない
		}
		bgm[runSub]->Play(); //runSubの曲を再生
		++runSub; //添え字を1つ進めて次の曲の再生準備

		count = 0; //カウントリセット
	}
}

void PK_BGM::Reset() {
	for (auto itr : bgm) { 
		StopSoundMem(itr->GetHandle()); //曲止め
		SetCurrentPositionSoundMem(0, itr->GetHandle()); //再生位置の初期化
	}
	SetRunUpdate(false); //全て止めてもUpdate開始と同時にcount処理が始まってしまうので開始タイミングをコントロールすべくisUpdateはfalseに設定する
	BGMListShuffle(bgm); //リストの順番を新しくする
	runSub = 0; //再生添え字を最初からに合わせる
	count = 0; //カウントリセット
	resumeMemo = -1; //並びが新しくなったので前回記録を何も掛かってない状態にリセット
}

void PK_BGM::Stop() {
	resumeMemo = -1; //memoの記録を何も掛かってない状態にリセット
	for (int i = 0; i < bgm.size(); ++i) {
		if (CheckSoundMem(bgm[i]->GetHandle())) { //今回の曲が掛かっていた場合 
			resumeMemo = i; //memoへ記録
			StopSoundMem(bgm[resumeMemo]->GetHandle()); //再生中のbgmを止める
			break; //配列チェック終わり
		}
	}
}
void PK_BGM::Resume() {
	if (resumeMemo != -1) { bgm[resumeMemo]->Play(); } //memoの曲再生を再開
}

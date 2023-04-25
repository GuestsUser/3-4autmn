#pragma once
#include "Component.h"

class Cmp_Transform;

class Cmp_Sound :public Component { //サウンドを保持するコンポーネント、Playを実行するとサウンドを再生する
	Cmp_Transform* ts;
	bool isSelfTs; //Transformコンポーネントをコンストラクタで省いた場合これをtrueにしてTransformの削除等はこちらで行う

	int handle; //サウンドハンドル
	int playType; //PlaySoundMemに渡すPlayTypeに相当する
	int topPositionFlag; //PlaySoundMemに渡すTopPositionFlagに相当する

	float rad; //音の聞こえる半径
public:
	Cmp_Sound(const int& handle, int rad = -1, int playType = -1, int topPositionFlag = true, Cmp_Transform* ts = nullptr); //rad,playtypeに設定されてる初期値-1はそのままならコンストラクタで別の値に置き換える、設定したい初期値を出す為多くのヘッダーインクルードを余儀なくされた故の措置
	~Cmp_Sound();

	void Update() {}
	void Play()const; //サウンド再生
	void Stop()const; //サウンド停止、StopSoundMemでいいがPlayがあるので統一の為に用意

	const Cmp_Transform* const ReadTranform() const { return ts; } //読み取り専用形式でTransformを取得
	Cmp_Transform* EditTranform() { return ts; } //書き換え可能な形式でTransformを取得

	void SetPlayType(int set) { playType = set; }
	void SetTopPositionFlag(int set) { topPositionFlag = set; }
	void SetRad(float set);

	int GetHandle()const { return handle; }
};
#pragma once
#include "Component.h"
#include "Cmp_Sound.h"

#include "Cmp_Transform.h"

#include <deque>

class PK_BGM :public Component {
	std::deque<Cmp_Sound*> bgm; //再生bgmリスト
	Cmp_Transform ts; //保持bgmの位置を決定するtransform

	int coolTime; //bgmが止まっている状況からこの時間分待機して新しいbgmを再生する
	int count; //coolTime分の時間経過を計る為のカウント
	int runSub; //bgmリスト内のこの添え字の曲を流す

	int resumeMemo; //Stopを実行した時掛かっていた曲の添え字を保持、何も掛かってなかった場合-1が入る
public:
	PK_BGM(Cmp_Transform ts = Cmp_Transform());

	void Update(); //bgm内にある曲を連続で流すUpdate

	void FullReset() { Reset(); }
	void Reset(); //全ての曲を止め、再生開始位置を元に戻し、各種保持変数を初期化しUpdate実行を切る、BGM処理を再開したいタイミングでUpdate実行を再開するとよし

	void Stop(); //bgmを止める
	void Resume(); //止めたbgmを再開する
};
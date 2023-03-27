#include "DxLib.h"

#include "Component.h"
#include "BetLogicInitializeData.h"
#include "Cmp_CPUBetLogic.h"

#include "PK_CardDealer.h"
#include "PK_Card.h"
#include "PK_Chara.h"
#include "PK_Dealer.h"

#include <deque>

/*
(Tのハイカード)～(8のワンペア)以下 0
(2のワンペア)～(Qのワンペア)未満 1 +(3)～(8)
(6のワンペア)～(2のツーペア)未満 3 +(3)～(7)
(Qのワンペア)～(6のツーペア)未満 5 +(1)～(3)
(5のツーペア)～(Tのツーペア)未満 7 +(0)～(2)
(Tのツーペア)～(4のスリーカード)以上 10 +(0)～(1)
ストレート、フラッシュの完成待ち (3)～(10)
*/


Cmp_CPUBetLogic::Cmp_CPUBetLogic(PK_Dealer& setDealer) :changeTimingLimit(4), changeTiming(1), oldGameCount(0), raiseActive(false), dealer(&setDealer), borderBase(std::deque<int>()), border(std::deque<int>()), payLimit(std::deque<int>()), raiseSplit(std::deque<int>()) {
	//定数データの初期化

	BorderBaseIni(borderBase);
	RaiseBorderBaseIni(raiseBorderBase);
	PayLimitiIni(payLimit);

	int size = borderBase.size() / 2; //ボーダー系の確保要素数
	border.resize(size); //指定要素数領域確保
	raiseBorder.resize(size);
}

void Cmp_CPUBetLogic::Reset() {
	raiseSplit.resize(0); //分割レイズ数を初期化
	raiseActive = false;
	int gameCount = dealer->GetGameCount(); //現在ゲーム回数を取得

	if ((gameCount - oldGameCount) % changeTiming == 0) { //更新タイミングだった場合更新処理
		oldGameCount = gameCount; //今回のゲームカウントを記録
		changeTiming = GetRand(changeTimingLimit - 1) + 1; //次の更新タイミングを決定、0になってしまわない様に+1する

		for (int i = 0; i < border.size(); ++i) {
			int sub = (int)i * 2; //今回の最低ボーダーへアクセスする添え字
			int low = borderBase[sub]; //最低値
			if (i >= 1 && low < border[i - 1]) { low = border[i - 1] + 1; } //前の要素のボーダーが今回の最低値を上回っている場合大きい方を採用、前回の値とぶつからないように+1している
			border[i] = GetRand(borderBase[sub + 1] - low) + low; //ボーダー設定

			raiseBorder[i] = GetRand(raiseBorderBase[sub + 1] - raiseBorderBase[sub]) + raiseBorderBase[sub]; //レイズボーダー設定
		}
	}
}

void Cmp_CPUBetLogic::RaiseVolDecision(const PK_Chara& chara, bool isCheckReach) {
	std::deque<int> handRank; //手札を数値化した物を格納
	chara.GetHandNum(handRank); //キャラから手札配列を取得
	
	int rank = 0; //手の強さがborder内の何処にあるかを示す内部ランク
	int vol = 0; //レイズ可能回数記録

	for (rank = 0; rank < border.size(); ++rank) { //手の強さからレイズ可能回数を割り出す
		vol = GetRand(payLimit[rank * 2 + 1] - payLimit[rank * 2]) + payLimit[rank * 2]; //今回のレイズ可能回数
		if (handRank[0] < border[rank]) { break; } //手の強さが今回のボーダーに達していなければ終わり
	}
	if (rank >= border.size()) { rank = border.size() - 1; } //手の強さがボーダーの上限を超えていた場合圏内に納める

	raiseActive = handRank[0] >= GetRand(borderBase[rank * 2 + 1] - borderBase[rank * 2]) + borderBase[rank * 2] + raiseBorder[rank]; //内部ランク内のボーダーベースとレイズベースからランダム数値を取り出して2つを加算した値以上の手の強さなら自主レイズを行う

	if (isCheckReach && PK_CardDealer::ReachCheck(chara) != 1) { //リーチチェック
		vol = GetRand(payLimit[payLimit.size() - 1] - payLimit[payLimit.size() - 2]) + payLimit[payLimit.size() - 2]; //リーチが掛かっていればそちらにレイズ基準を合わせる
		rank = border.size() + 1; //使用ランクをリーチ用の物に変更
		raiseActive = round((double)GetRand(10) / 10.0); //リーチの場合自主レイズはランダム決定する
	}
	if (!raiseActive) { //自主レイズしない場合
		raiseSplit.push_back(vol); //分割はせず全てsplit[0]に格納
		return; //終わり
	}

	while (vol > 0) { //レイズ可能回を分割する
		raiseSplit.push_back(GetRand(vol - 1) + 1); //今回のレイズ回数
		vol -= raiseSplit[raiseSplit.size() - 1]; //今回の回数は使用済みとしてレイズ可能回数から減算
	}
}

#include "PK_Chara.h"
#include "PK_CPU.h"
#include "PK_CPU_Main.h"

#include "PK_Pot.h"
#include "PK_Dealer.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_Transform.h"
#include "Cmp_PK_Chara_SE.h"
#include "Cmp_Sound.h"

#include "PK_SectionLibrary.h"

#include <deque>

void PK_CPU::Main::Update() {
	++count;
	if (count > waitTime) { //指定待機時間を超えた場合実行アクションを決定する
		count = 0; //カウントリセット

		int raise = 0; //このキャラのレイズ可能回数
		for (auto itr : *parent->betData->ReadRaiseSplit()) { raise += itr; } //分割されたレイズ可能回数を一つに纏める
		raise *= parent->dealer->GetBB(); //現在BBをレイズ可能回数に掛けてレイズ可能額に変更する

		int betRequest = parent->pot->GetCurrentMaxBet(); //現在最大ベット金額
		int oldPay = parent->pot->Inquiry(*parent); //このキャラの前回までの支払額
		int pay = betRequest - oldPay; //支払金額


		Cmp_BetActionRecord::Action action = Cmp_BetActionRecord::Action::fold; //実行すべきアクションを格納
		if (raise > betRequest) { action = ActionDecision(parent->betData); } //現在最大ベットがレイズ可能額を超えていなければレイズ、コールする
		if (parent->record->GetRaiseRunCount() > 0 && raise * 5 > parent->pot->GetCurrentMaxBet()) { action = ActionDecision(parent->betData); } //1度レイズしたことがある場合レイズ可能額の5倍まではレイズを受ける
		if (action == Cmp_BetActionRecord::Action::raise && parent->record->GetRaiseRunCount() >= parent->betData->ReadRaiseSplit()->size()) { action = Cmp_BetActionRecord::Action::call; } //レイズ可能額全てを使い切っていた場合コールになる


		if (action == Cmp_BetActionRecord::Action::raise) { //レイズ額出し処理
			int runCount = parent->record->GetRaiseRunCount(); //今回のsplit読み出し開始位置を入れる
			int raiseAdd = RaiseCalculation(*parent->betData->ReadRaiseSplit(), runCount, oldPay, betRequest, parent->dealer->GetBB(), parent->GetCoint()); //レイズによる増分を得る

			parent->record->SetRaiseRunCount(runCount); //使用済み分割数を記録する
			if (raiseAdd <= 0) { action = Cmp_BetActionRecord::Action::call; } //レイズしても届かなかったり所持金の問題で指定分レイズできなかった場合callにする
			else { pay += raiseAdd; } //普通にレイズできれば増分を加える
		}
		if (action == Cmp_BetActionRecord::Action::call && pay == 0) { action = Cmp_BetActionRecord::Action::check; } //指定アクションがcallで金額支払いが不要の場合チェックになる
		if (parent->GetCoint() - pay <= 0) { //支払額が所持金以上になる場合
			action = Cmp_BetActionRecord::Action::allIn; //allInになる
			pay = parent->GetCoint(); //支払額を所持金に合わせる
		}

		parent->record->SetActionRecord(action, true); //該当アクションを動作済みにする
		parent->record->SetFinalAction(action); //該当アクションを最終アクションにする
		parent->record->SetIsAction(true); //アクション済みに設定

		Cmp_PK_Chara_SE::Request request = Cmp_PK_Chara_SE::Request::call; //鳴らすseの指示を格納
		if (action == Cmp_BetActionRecord::Action::raise || action == Cmp_BetActionRecord::Action::allIn) { request = Cmp_PK_Chara_SE::Request::raise; } //raise又はallInしていればraise音を指定
		if (action == Cmp_BetActionRecord::Action::fold) { request = Cmp_PK_Chara_SE::Request::fold; } //fold音を指定
		if (action != Cmp_BetActionRecord::Action::check) { parent->se->ReadSE(request)->Play(); } //check以外なら指定された音を鳴らす
		

		if (action == Cmp_BetActionRecord::Action::call || action == Cmp_BetActionRecord::Action::raise) { parent->pot->SetMainPot(pay, *parent); } //call、raiseの場合メインポットへ
		if (action == Cmp_BetActionRecord::Action::allIn) { parent->pot->SetSidePot(pay, *parent); } //allInの場合サイドポットへ
		if (action != Cmp_BetActionRecord::Action::fold) { parent->SetCoin(parent->GetCoint() - pay); } //fold以外の場合所持金から支払額を減算する(checkの場合payは0なので弾く必要なし)

		return; //終わり
	}
	parent->record->SetFinalAction(Cmp_BetActionRecord::Action::noAction); //アクションを実行してないのでnoActionを設定

}

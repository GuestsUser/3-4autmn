#include "PK_SectionLibrary.h"

#include "../Code/ConstVal.h"

#include "Btn.h"
#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"
#include "PokerFontData.h"

#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"

#include <algorithm>
#include <deque>
#include <typeinfo>
#include <string>
#include <cmath>


PK_Card* Power2Card(std::deque<PK_Card*>& hand, int target) { //handからtargetに渡されたカードの強さと一致するカードを抽出する
	for (auto itr : hand) {
		if (itr->GetCard() % (int)CardDealer::CardPower::max == target) { return itr; } //targetと一致するPK_Card参照を返す
	}
}

Cmp_BetActionRecord::Action ActionDecision(Cmp_CPUBetLogic* betLogic) { //入れられたbetLogicによってraiseすべきかcallすべきか返す
	return betLogic->GetSelfRaise() ? Cmp_BetActionRecord::Action::raise : Cmp_BetActionRecord::Action::call;
}

bool BetIgnore(Cmp_BetActionRecord* record) { //キャラのアクション記録を渡す事でそのキャラのベットをスキップすべきか否か返す、trueでスキップ
	return record->GetActionRecord(Cmp_BetActionRecord::Action::allIn) || record->GetActionRecord(Cmp_BetActionRecord::Action::fold) || record->GetIsLose(); //allIn、Fold、敗北済みの場合ベットをスキップ
}

bool IsFold(Cmp_BetActionRecord& record) { //recordのキャラがアクションを終わらせた又はfoldで除外された等そのフェーズ中干渉できなくなっていればtrueを返す
	return record.GetActionRecord(Cmp_BetActionRecord::Action::fold) || record.GetIsLose() || record.GetIsAction(); //foldしている、敗北済み、アクション実行済みでtrueを返す
}

int FoldCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //ゲームから抜けたキャラ数を返す、centerにrecordへ使用する添え字を入れるとそのキャラを中心にチェックする
	int dropCount = 1; //このラウンドから抜けたキャラを記録する

	for (int i = 1; i < (int)Poker::Character::length; ++i) {
		Cmp_BetActionRecord current = *actionRecord[(center + i) % (int)Poker::Character::length]; //今回チェックするキャラ、そのアクセスショートカット
		dropCount += current.GetActionRecord(Cmp_BetActionRecord::Action::fold) || current.GetIsLose(); //飛ばし条件の何れかに掛かっていれば+1する
	}
	return dropCount;
}

int ActionEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //アクション終了済みキャラ数を返す、centerにrecordへ使用する添え字を入れるとそのキャラを中心に終了済みキャラ数をチェックする
	int endCount = 1; //アクションが終わったキャラ数を記録する
	for (endCount; endCount < (int)Poker::Character::length; ++endCount) {
		Cmp_BetActionRecord current = *actionRecord[(center + endCount) % (int)Poker::Character::length]; //今回チェックするキャラ、そのアクセスショートカット
		if (current.GetIsAction()) { continue; } //アクション終了済みならやり直し
		if (BetIgnore(&current)) { continue; } //アクション不能ならやり直し
		break; //ここまで来たキャラはアクション可能なので終わり
		//if (!(BetIgnore(&current) || current.GetIsAction())) { break; } //チェックキャラが終了条件の1つにも引っかからなかった場合中断
	}
	return endCount;
}

int ChangeEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //Change専用EndCount、上記はBetIgnoreなのでChangeには使えないから用意
	int endCount = 1; //アクションが終わったキャラ数を記録する
	for (endCount; endCount < (int)Poker::Character::length; ++endCount) {
		Cmp_BetActionRecord current = *actionRecord[(center + endCount) % (int)Poker::Character::length]; //今回チェックするキャラ、そのアクセスショートカット
		if (!IsFold(current)) { break; } //チェックキャラが終了条件の1つにも引っかからなかった場合中断
	}
	return endCount;
}

int EnableCharaSearch(std::deque<Cmp_BetActionRecord*>& actionRecord, int center) { //上記EndCountでは終了キャラを調べたがこちらはcenterから最短の未敗北キャラ添え字を返す
	int add = 0;
	for (add; add < actionRecord.size(); ++add) { //centerを中心に対象キャラが敗北しているか調べる
		Cmp_BetActionRecord current = *actionRecord[(center + add) % actionRecord.size()]; //今回チェックするキャラ、そのアクセスショートカット
		if (current.GetIsAction()) { continue; } //アクション終了済みならやり直し
		if (BetIgnore(&current)) { continue; } //アクション不能ならやり直し
		break; //ここまで来たキャラはアクション可能なので終わり
	}
	if (add >= actionRecord.size()) { return -1; } //全員操作不能になっていた場合-1を返す
	return (center + add) % actionRecord.size(); //centerの次にすぐ行動可能なキャラ添え字を返す
}


int RaiseCalculation(const std::deque<int>& split, int& runCount, int oldPay, int betRequest, int BB, int coin) {
	//ラウンド中での総支払額と分割レイズを何処まで使うかを返す、splitに分割レイズデータ、runCountにsplit読み出し開始位置を(編集される、次の読み出し開始位置まで移動される)、oldPayに前回までの支払額、betRequestに現在最大ベットを、BBに現在BBを、coinに所持金を入れる
	int adjustSB = oldPay % BB != 0 ? oldPay : 0; //SBが前回支払額に含まれている(BBで割り切れない=SB)場合それを取り除いた値を最終レイズ額とする
	for (runCount; runCount < split.size();) { //支払額が現在ベットを上回るよう分割レイズを調整使用する処理
		int nowPayMent = split[runCount] * BB; //今回のsplit支払額
		if (coin - (oldPay + nowPayMent) < 0) { break; } //レイズで所持金を0未満にしてしまう場合今回分は使わず終了

		oldPay += nowPayMent; //今回分の支払額を加える
		++runCount; //runCountを進める、このタイミングで実行する事に意味がある
		if (oldPay > betRequest) { break; } //現在の分割数でベット最大を超えたら終了
	}

	return oldPay - betRequest - adjustSB; //レイズによる増加額を返す、SBを取り除いた値とする
}

void SequenceNextReset(const std::deque<Cmp_BetActionRecord*>& chara) { //次シーケンスへ移行する際実行するアクション記録リセット用関数
	for (auto itr : chara) {
		itr->SetActionRecord(Cmp_BetActionRecord::Action::check, false); //allInとLoose以外のアクションをリセット
		itr->SetActionRecord(Cmp_BetActionRecord::Action::call, false);
		itr->SetActionRecord(Cmp_BetActionRecord::Action::raise, false);
		itr->SetIsAction(false); //アクション未実行状態に戻す
	}
}

void BBSBLevy(int BBpos, std::deque<Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord, Cmp_Gage_Border& gageBorder, Cmp_Gage_UpperBorder& gageUpper, Pot& pot, PK_Dealer& dealer) { //BB、SBポジションキャラからBB、SBを回収

	int iniActionChara = dealer.GetActionCharaSub(); //アクションを実行するキャラの初期設定記憶
	float playerCoin = chara[(int)Poker::Character::player]->GetCoint(); //プレイヤーの保持コイン記憶

	if (playerCoin - dealer.GetBB() * dealer.GetMaxBet() <= 0) { gageUpper.SetBorder(playerCoin / (dealer.GetBB() * dealer.GetMaxBet())); } //最大ベット可能額がプレイヤー所持金を超えていた場合掛金上限を所持金に合わせる
	for (int i = 0; i < 2; ++i) { //BB、SBの2回徴収が必要なのでi<2
		int levy = EnableCharaSearch(actionRecord, BBpos + i); //今回のキャラチェック位置
		int coin = chara[levy]->GetCoint(); //現在所持金
		int pay = dealer.GetBB() / (i + 1); //支払額
		chara[levy]->SetBBView((Chara::BBView)i); //支払額に応じてBB支払いかSB支払いか表示を設定する

		if (coin - pay <= 0) { //支払額が所持金を上回っていた場合
			pay = coin; //持ってる分を支払額に設定する
			actionRecord[levy]->SetActionRecord(Cmp_BetActionRecord::Action::allIn, true); //強制allIn
			actionRecord[levy]->SetIsAction(true); //アクション済みにされる

			int newActionChara = EnableCharaSearch(actionRecord, levy); //位置更新に合わせた新しいアクション実行キャラ
			if (newActionChara <= -1) { newActionChara = iniActionChara; } //全員アクション済みになっていた場合初期のキャラを指定する
			dealer.SetActionChara(newActionChara); //位置更新に合わせて初めにアクションを開始するキャラを更新する
		}
		float border = (float)pay / (dealer.GetBB() * dealer.GetMaxBet()); //今回支払に応じたプレイヤーゲージの下限設定
		if (border > gageBorder.GetBorder()) { //今回下限が今までの下限を超えていた場合
			pot.SetMainPot(pay, *chara[levy]); //メインポットへBB、SB支払い
			gageBorder.SetBorder(border); //下限再設定
		}
		else { pot.SetSidePot(pay, *chara[levy]); } //下限以下の支払いだった場合サイドポットとして再振り分けを行う

		chara[levy]->SetCoin(coin - pay); //支払い分所持金から差し引く
	}

}

void LoseSet(const std::deque<Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord) { //現在所持金に合わせて敗北設定を行う
	for (int i = 0; i < chara.size(); ++i) { actionRecord[i]->SetIsLose(chara[i]->GetCoint() <= 0); } //所持金が0以下になったら敗北に設定する
}

void FullReset(std::deque<Chara*>& chara, Pot& pot, PK_Dealer& dealer, CardDealer& cardDealer) { //各種fullResetを実行しPreから新しいゲームを始められるようにする
	pot.Reset();
	dealer.FullReset();
	cardDealer.Reset();
	for (auto chara : chara) { chara->FullReset(); }
}

void PlayerButtonAnalyze(const std::deque<Button*>& button, Button** action, Button** fold) { //buttonにplayerのボタンをいれるとactionにアクション用ボタン、foldにfold用ボタンを入れて返してくれる
	for (auto itr : button) {
		if ((itr->EditAlwaysCmp<Cmp_Image>())->GetAnimeLength() == 1) { *fold = itr; } //分割画像枚数が1ならfoldボタン
		else { *action = itr; } //違うならアクションボタン
	}
}

std::string Hand2String(const std::deque<int>& hand) {
	switch ((CardDealer::HandRank)(hand[0] / (int)CardDealer::CardPower::max)) {
	case CardDealer::HandRank::No: return "ハイカード"; break;
	case CardDealer::HandRank::OnePair: return "ワンペア"; break;
	case CardDealer::HandRank::TwoPair: return "ツーペア"; break;
	case CardDealer::HandRank::ThreeCard: return "スリーカード"; break;
	case CardDealer::HandRank::Straight: return "ストレート!"; break;
	case CardDealer::HandRank::Flash: return "フラッシュ!"; break;
	case CardDealer::HandRank::FullHause: return "フルハウス!"; break;
	case CardDealer::HandRank::FourCard: return "フォーカード!!"; break;
	case CardDealer::HandRank::StraightFlash: return "ストレートフラッシュ!!"; break;
	case CardDealer::HandRank::RoyalStraightFlash: return "ロイヤルストレートフラッシュ!!!"; break;
	}

}

void FoldMemberPayOut(std::deque<Chara*>& chara, Pot& pot) { //foldキャラへPayOut
	Chara* maxChara = chara[0]; //最大支払額を持つキャラ
	int max = pot.Inquiry(*maxChara); //最大支払額
	for (int i = 1; i < chara.size(); ++i) {
		int current = pot.Inquiry(*chara[i]); //今回キャラの支払額
		if (max < current) { //今回キャラが最大ベット額を持っていればmax系の中身を交換
			max = current;
			maxChara = chara[i];
		}
	}
	max = pot.PayOut(*maxChara) / chara.size(); //最大支払額を持つキャラでポットから金額取り出し
	for (int i = 0; i < chara.size(); ++i) { chara[i]->SetCoin(chara[i]->GetCoint() + max); } //残りを分配
}

Poker::Section GameEndCheck(const std::deque<Chara*>& chara, const std::deque<Cmp_BetActionRecord*>& actionRecord) { //現在の敗北状況から向かうべきシーンを返す
	int loseCount = 0; //敗北キャラ数のカウント
	for (auto itr : actionRecord) { loseCount += itr->GetIsLose(); } //全キャラをチェックし敗北キャラ数をカウントしてゆく

	Poker::Section val = Poker::Section::ini; //返す値、ゲームを続行すべきならiniを返す
	if (loseCount >= (int)Poker::Character::length - 1) { val = Poker::Section::gameclear; } //1キャラ以外全てが敗北していた場合ゲームクリアを設定
	if (actionRecord[(int)Poker::Character::player]->GetIsLose()) { val = Poker::Section::gameover; } //プレイヤーが敗北していた場合ゲームオーバーを設定、クリアとオーバーではオーバーが優先

	return val;
}
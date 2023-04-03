#pragma once
#include "Poker.h"
#include "Cmp_BetActionRecord.h"

#include <deque>
#include <string>

class PK_Card;
class PK_Dealer;
class PK_Chara;
class PK_Pot;
class PK_CardDealer;

class Button;
class Cmp_CPUBetLogic;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;


PK_Card* Power2Card(std::deque<PK_Card*>& hand, int target); //handからtargetに渡されたカードの強さと一致するカードを抽出する

Cmp_BetActionRecord::Action ActionDecision(Cmp_CPUBetLogic* betLogic); //入れられたbetLogicによってraiseすべきかcallすべきか返す
bool BetIgnore(Cmp_BetActionRecord* record); //キャラのアクション記録を渡す事でそのキャラのベットをスキップすべきか否か返す、trueでスキップ
bool IsFold(Cmp_BetActionRecord& record); //recordのキャラがアクションを終わらせた又はfoldで除外された等そのフェーズ中干渉できなくなっていればtrueを返す
int FoldCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center); //ゲームから抜けたキャラ数を返す、centerにrecordへ使用する添え字を入れるとそのキャラを中心にチェックする
int ActionEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center); //アクション終了済みキャラ数を返す、centerにrecordへ使用する添え字を入れるとそのキャラを中心に終了済みキャラ数をチェックする
int ChangeEndCount(std::deque<Cmp_BetActionRecord*>& actionRecord, int center); //Change専用EndCount、上記はBetIgnoreなのでChangeには使えないから用意
int EnableCharaSearch(std::deque<Cmp_BetActionRecord*>& actionRecord, int center); //上記EndCountでは終了キャラを調べたがこちらはcenterから最短の未敗北キャラ添え字を返す

int RaiseCalculation(const std::deque<int>& split, int& runCount, int oldPay, int betRequest, int BB, int coin); //ラウンド中での総支払額と分割レイズを何処まで使うかを返す、splitに分割レイズデータ、runCountにsplit読み出し開始位置を(編集される、次の読み出し開始位置まで移動される)、oldPayに前回までの支払額、betRequestに現在最大ベットを、BBに現在BBを、coinに所持金を入れる
void SequenceNextReset(const std::deque<Cmp_BetActionRecord*>& chara); //次シーケンスへ移行する際実行するアクション記録リセット用関数
void BBSBLevy(int BBpos, std::deque<PK_Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord, Cmp_Gage_Border& gageBorder, Cmp_Gage_UpperBorder& gageUpper, PK_Pot& pot, PK_Dealer& dealer); //BB、SBポジションキャラからBB、SBを回収
void LoseSet(const std::deque<PK_Chara*>& chara, std::deque<Cmp_BetActionRecord*>& actionRecord); //現在所持金に合わせて敗北設定を行う
void PartsFullReset(std::deque<PK_Chara*>& chara, PK_Pot& pot, PK_Dealer& dealer, PK_CardDealer& cardDealer); //各種fullResetを実行しPreから新しいゲームを始められるようにする

void PlayerButtonAnalyze(const std::deque<Button*>& button, Button** action, Button** fold); //buttonにplayerのボタンをいれるとactionにアクション用ボタン、foldにfold用ボタンを入れて返してくれる

void FoldMemberPayOut(std::deque<PK_Chara*>& chara, PK_Pot& pot); //foldキャラへPayOut

Poker::Section GameEndCheck(const std::deque<PK_Chara*>& chara, const std::deque<Cmp_BetActionRecord*>& actionRecord); //現在の敗北状況から向かうべきシーンを返す
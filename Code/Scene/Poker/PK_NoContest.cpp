#include <DxLib.h>
#include "PK_NoContest.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "Pot.h"
#include "PK_Player.h"
#include "PokerFontData.h"

#include "Cmp_BetActionRecord.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"

Poker::NoContest::NoContest(Poker& set) :parent(&set), count(0), payOutTime(60), clickStartTime(120), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	titlePos.SetXYZ(513, 189, 0); //ノーコンテストである事を示すメッセージの位置設定
	explainPos.SetXYZ(484, 312, 0); //ボタン説明配置位置

	nextButton.SetClick(new Cmp_Button_ClickCheck()); //クリックチェック用コンポーネント追加

	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}

void Poker::NoContest::Update() {
	nextButton.Update(); //ボタンUpdate実行

	if (count == payOutTime) {
		Chara* enableChara = nullptr; //降りなかったキャラが入る
		std::deque<Chara*> foldChara = std::deque<Chara*>(); //フォールドしたキャラ纏め(敗北済みは除く)

		for (int i = 0; i < parent->chara.size(); ++i) { //キャラを勝負をするキャラ、foldキャラ、除外キャラに仕分ける
			if (actionRecord[i]->GetIsLose()) { continue; } //敗北済みの場合何もせず次キャラへ移行
			if (actionRecord[i]->GetActionRecord(Cmp_BetActionRecord::Action::fold)) { foldChara.push_back(parent->chara[i]); continue; } //foldしてる場合foldCaraへ格納し次キャラへ移行
			enableChara = parent->chara[i]; //現在キャラをenableCharaへ格納
		}
		enableChara->SetCoin(enableChara->GetCoint() + parent->pot->PayOut(*enableChara)); //金額総取り
		if (parent->pot->TotalAmount() <= 0) { ++count; return; } //金額がなくなれば終わり
		FoldMemberPayOut(foldChara, *parent->pot); //余っていればfoldキャラへ分配

	}

	if (count == clickStartTime) { //クリック検知開始タイミングになったら

		LoseSet(parent->chara, actionRecord); //敗北状況の設定
		Poker::Section next = GameEndCheck(parent->chara, actionRecord); //敗北状況から次向かうべきシーンを取得

		if (next != Poker::Section::ini) { //ini(続行すべき)以外が入った場合
			parent->run = parent->list[(int)next]; //そのシーンに移行
			count = -1; //カウントリセット
			return; //終わり
		}

		nextButton.SetRunClickMonitor(true); //クリック検知開始
	}

	if (nextButton.GetRunUpdateClick()) { //クリックされた場合
		parent->run = parent->list[(int)Poker::Section::ini]; //最初の状態に戻る

		nextButton.SetRunUpdateClick(false); //クリック状態を戻す
		nextButton.SetRunDrawClick(false); //念の為Drawも戻す
		nextButton.SetRunClickMonitor(false); //クリック検知の無効化
		count = -1; //カウントリセット
	}

	++count;
}

void Poker::NoContest::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "ノーコンテスト!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "画面をクリックで次ゲームへ", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}

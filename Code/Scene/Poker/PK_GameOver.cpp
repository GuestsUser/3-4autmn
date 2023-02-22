#include <DxLib.h>
#include "PK_GameOver.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "PokerFontData.h"

#include "../Code/Component/Button.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"

Poker::GameOver::GameOver(Poker& set) :parent(&set), count(0), clickStartTime(60), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false) {
	titlePos.SetXYZ(513, 189, 0); //ゲームオーバーである事を示すメッセージの位置設定
	explainPos.SetXYZ(472, 312, 0); //ボタン説明配置位置

	nextButton.SetClick(new Cmp_Button_ClickCheck()); //クリックチェック用コンポーネント追加
}

void Poker::GameOver::Update() {
	nextButton.Update(); //ボタンUpdate実行
	if (count == clickStartTime) { nextButton.SetRunClickMonitor(true); } //開始タイミングになったらクリック検知開始

	if (nextButton.GetRunUpdateClick()) { //クリックされた場合
		FullReset(parent->chara, *parent->pot, *parent->dealer, *parent->cardDealer); //新しいゲームの準備をする
		parent->run = parent->list[(int)Poker::Section::pre]; //最初の状態に戻る

		nextButton.SetRunUpdateClick(false); //クリック状態を戻す
		nextButton.SetRunDrawClick(false); //念の為Drawも戻す
		nextButton.SetRunClickMonitor(false); //クリック検知の無効化
		count = -1; //カウントリセット
	}

	++count;
}

void Poker::GameOver::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "ゲームオーバー!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "画面をクリックで新しく始める", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}
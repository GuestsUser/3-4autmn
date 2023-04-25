#include <DxLib.h>
#include "PK_GameClear.h"

#include "Scene.h"
#include "Poker.h"
#include "ConstVal.h"

#include "PK_SectionLibrary.h"
#include "PokerFontData.h"

#include "Button.h"
#include "Cmp_3DSoundListener.h"
#include "Cmp_Button_ClickCheck.h"
#include "Cmp_ButtonOverlapGroup.h"
#include "Cmp_Sound.h"

Poker::GameClear::GameClear(Poker& set) :parent(&set), count(0), clickStartTime(60), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false) {
	titlePos.SetXYZ(513, 189, 0); //ゲームクリアである事を示すメッセージの位置設定
	explainPos.SetXYZ(472, 312, 0); //ボタン説明配置位置

	nextButton.EditClick()->SetCmp(new Cmp_Button_ClickCheck()); //クリックチェック用コンポーネント追加
	parent->pauseButon->EditAlways()->EditCmp<Cmp_ButtonOverlapGroup>()->EditGroup()->push_back(&nextButton); //ポーズボタンに重なっている次シーン移行ボタンを重なり無効化コンポーネントへ格納する

	sound = new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/gameClear.wav"), -1, -1, true, Cmp_3DSoundListener::EditTransform());
}

void Poker::GameClear::Update() {
	nextButton.Update(); //ボタンUpdate実行
	if (count == 0) { sound->Play(); } //初めてのタイミングならサウンドを鳴らす
	if (count == clickStartTime) { nextButton.SetRunClickMonitor(true); } //開始タイミングになったらクリック検知開始

	if (nextButton.GetRunUpdateClick()) { parent->SetNextSection(Poker::Section::newgamereset); } //クリックされた場合ゲームの完全リセットシーンへ移行
	++count;
}

void Poker::GameClear::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "ゲームクリア!!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "画面をクリックで新しく始める", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}

void Poker::GameClear::Reset() {
	nextButton.EditClick()->SetRunUpdate(false); //クリック状態を戻す
	nextButton.EditClick()->SetRunDraw(false); //念の為Drawも戻す
	nextButton.SetRunClickMonitor(false); //クリック検知の無効化
	count = 0; //カウントリセット
}
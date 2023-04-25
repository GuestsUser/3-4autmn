#include "DxLib.h"
#include "Poker.h"
#include "Cmp_PK_Pause.h"
#include "PK_Pause_DataSetting.h"

#include "PK_Pause_PauseEnd.h"
#include "PokerFontData.h"

#include "Button.h"
#include "PK_BGM.h"
#include "Cmp_3DSoundListener.h"
#include "Cmp_Button_ClickSound.h"
#include "Cmp_ButtonGroup.h"
#include "Cmp_Image.h"
#include "OriginMath.h"
#include "SoundSetting.h"

#include <deque>
#include <string>

Cmp_PK_Pause::Cmp_PK_Pause(Button& set, Poker& poker) :parent(&set), poker(&poker), runClose(false), count(0) {
	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause_back.png")), 1); //背景作成

	std::deque<Cmp_Transform*> ts;
	for (int i = 0; i < 3; ++i) { //ボタン作成
		button.push_back(new Button(0, 0, 270 / 2, 80 / 2));
		ts.push_back(button[i]->EditTransform()); //	ボタン位置を揃える為のTransform詰め

		button[i]->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause_tile.png")), 1, ts[i]));
		button[i]->EditClick()->SetCmp(new Cmp_ButtonGroup(*button[i], button)); //ボタングループ追加
		button[i]->EditClick()->SetCmp(new Cmp_Button_ClickSound(*SoundSetting::CreateDefaultButtonClickSound(Cmp_3DSoundListener::EditTransform()))); //クリックされた時に鳴る音を追加
	}
	DataSetting::BackPlace(*back); //背景の位置設定
	DataSetting::ButtonNameImageSet(button); //ボタンに表示するメッセージの設定
	DataSetting::ButtonAppendCmpSet(*this, button); //ボタンが押されたら際の機能を設定
	OriginMath::MatrixPlacePos(ts, 1, 0, 374 - 275, Vector3(640, 275)); //ボタンの位置設定
}

void Cmp_PK_Pause::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止で実行しない

	if (count == 0) { //ポーズボタンを押したタイミングだった場合
		parent->SetRunClickMonitor(false); //親ボタンのクリック検知を切る
		poker->ControlBGM()->Stop(); //bgmを止める、再開はPauseEndの方で行う
	}

	back->Update(); //背景Update
	for (auto itr : button) { itr->Update(); } //ボタンUpdate

	++count; //カウント経過

	if (runClose) { //ボタンコンポーネントから終了の指示があった場合
		Cmp_PK_Pause::PauseEnd::Close(*this); //Update処理をPokerの各sectionへ戻す処理
		parent->Reset();
		for (auto itr : button) { itr->Reset(); } //保持するボタンのリセット
		runClose = false; //終了指令をfalseに戻す
		count = 0; //カウントリセット
	}
}

void Cmp_PK_Pause::Draw() {
	if (!GetRunDraw()) { return; } //実行禁止で実行しない
	back->Draw(); //背景描写
	for (auto itr : button) { itr->Draw(); } //ボタン描写
}

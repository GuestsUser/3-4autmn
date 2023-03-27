#include "DxLib.h"

#include "../Code/Scene/Scene.h"
#include "../Code/Component/Button.h"
#include "Title_Select.h"
#include "Title_Select_Explain.h"
#include "Title_Select_ButtonCreator.h"

#include <deque>

Title_Select::Title_Select() :explain(std::deque<Title_Select_Explain*>()), button(std::deque<Button*>()), run(nullptr) {
	BGM = LoadSoundMem("Resource/bgm/Select.wav");
	SetFontSize(36); //描写文字サイズ指定

	Title_Select_ButtonCreator::Creat(*this, explain, button, run); //次シーンへ飛ぶ為のボタンを作成しbuttonやexplainに格納する
}

Title_Select::~Title_Select() {
	for (int i = 0; i < button.size(); ++i) {
		delete button[i]; //newしたbuttonの削除
		delete explain[i]; //newした説明シーンの削除
	}
}

void Title_Select::Update() {
	if (CheckSoundMem(BGM) == 0) {
		ChangeVolumeSoundMem(110, BGM);
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
	}
	if (run != nullptr) { //runに何か入っていた場合そちらを優先実行
		run->Update(); //run実行

		run = run->GetNext(); //runに設定された次の実行シーンを取得runに設定
		if (run == nullptr) { return; }  //空にされたら抜け、次回からは平常時のUpdateを実行する
		for (auto itr : explain) {
			if (run == itr) { return; } //explainと同じ物があった場合抜け、次回もrunを実行する
		}
		StopSoundMem(BGM);
		SetNext(run); //ここまで来たら設定されたシーンはゲーム実行シーンになるのでセレクト画面を終了しそちらに移行する
		return;
	}

	//runに何も入ってない場合
	for (auto itr : button) { itr->Update(); } //ボタンupdateを実行
	if (run != nullptr) { //ボタン入力で次シーンへ移行する際再利用の為ボタンの状態をリセットしておく
		for (auto itr : button) { itr->Reset(); } 
	}
}

void Title_Select::Draw() {
	if (run != nullptr) { run->Draw(); } //runに何か入っていた場合そちらを優先実行
	else {
		for (auto itr : button) { itr->Draw(); } //ボタンdrawを実行
	}
}

#include "DxLib.h"

#include "Title_Select_Explain.h"
#include "Cmp_SelectSelector.h"
#include "../Code/OriginMath.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/Component/Cmp_ButtonGroup.h"
#include "../Code/Component/Button.h"
#include "../Code/Scene/Scene.h"
#include "Cmp_3DSoundListener.h"
#include "Cmp_Button_ClickSound.h"
#include "Cmp_Sound.h"
#include "Title_Select_Explain_PageScrollExplain.h"
#include "Title_SoundSetting.h"
#include "SoundSetting.h"

#include <deque>
#include <string>
#include <sstream>
#include <functional>

Title_Select_Explain::Title_Select_Explain(std::deque<Cmp_Image*>& setImage, std::function<Scene* ()> sceneCreator) :image(&setImage), page(0), scrollExplain(new Title_Select_Explain_PageScrollExplain()){
	run = this; //次回実行にはニュートラルとして自身を入れておく

	for (auto itr : *image) { itr->EditTranform()->EditPos().SetXYZ(640, 360, 0); } //ここで説明画像の表示位置を設定する
	scroll = new Cmp_Sound(LoadSoundMem("Resource/se/scroll.wav")); //スクロール音作成
	Title_SoundSetting::SetUpExplainScroll(*scroll); //スクロール音ステータス設定

	if (image->size() <= 1) { scrollExplain->SetRunUpdateDraw(false, false); } //スクロール不可なページ数の場合explainは実行禁止にする
	for (int i = 0; i < 2; ++i) { //ボタン設定
		button.push_back(new Button(1165 - 200 * i, 680, 150 / 2, 60 / 2)); //空ボタンを追加
		
		const char* name = nullptr;
		switch (i) { //読込画像決定用名前設定
		case 0: name = "Resource/image/Explain_Button1.png"; break;
		case 1: name = "Resource/image/Explain_Button2.png"; break;
		}

		button[i]->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph(name)), 1, button[i]->EditTransform())); //ボタンに画像を追加
		button[i]->EditClick()->SetCmp(new Cmp_ButtonGroup(*button[i], button)); //ボタンが押された際、押されたボタン以外を停止する機能の追加
		button[i]->EditClick()->SetCmp(new Cmp_Button_ClickSound(*SoundSetting::CreateDefaultButtonClickSound(Cmp_3DSoundListener::EditTransform()))); //クリックされた時に鳴る音を追加
	}
	button[0]->EditClick()->SetCmp(new Cmp_SelectSelector(sceneCreator, &run)); //決定ボタンが押されたらsceneCreatorで作成したシーンへ移行する設定
	button[1]->EditClick()->SetCmp(new Cmp_SelectSelector([]() -> Scene* { return nullptr; }, &run)); //戻るボタンが押されたらゲームセレクトへ戻る設定

}

Title_Select_Explain::~Title_Select_Explain() {
	for (auto itr : *image) { delete itr; } //各要素はnewで精製されているので消しておく
	for (auto itr : button) { delete itr; }

	delete image; //imageは他所で作られた参照をこちらで管理する形式なので消しておく
	delete scroll; //スクロール音の削除
	delete scrollExplain; //スクロール可能説明文の削除
}

void Title_Select_Explain::Update() {
	for (auto itr : *image) { itr->Update(); } //各種更新処理
	for (auto itr : button) { itr->Update(); }
	scrollExplain->Update();

	//表示ページ更新処理
	int max = image->size(); //ページ最大数
	int oldPage = page; //ページ操作を検知する為の現在ページ記録変数
	if (max > 1) { //ページが複数ある場合
		int rotate = GetMouseWheelRotVol(); //マウスホイール回転量
		if (rotate <= -1) { page = (page + 1) % max; } //前方にまわしたらページ+1
		if (rotate >= 1) { page = page - 1 < 0 ? (page + max - 1) % max : (page - 1) % max; } //奥にまわした場合ページ-1
		if (oldPage != page) { scroll->Play(); } //ページ操作があった場合サウンドを鳴らす
	}
	
	if (run != this) { 
		SetNext(run); //自身以外をrunに設定されたらそこへ向かえという意味合いなのでSetNext
		Reset(); //次使う時の為にResetを呼んでおく
	}
}
void Title_Select_Explain::Draw() {
	GetMouseWheelRotVol(); //最初の実行はDrawの方が早いのでマウスホイールの回転量を初期化する意味合いでこれを記す
	SetNext(this); //次使う時こちらが早いのでSetNextの初期化用に

	std::string pageNum = std::to_string(page + 1) + "/" + std::to_string(image->size()); //現在のページ数表示
	DrawString(1100, 32, pageNum.c_str(), GetColor(255, 255, 255)); //カラーは仮の物
	scrollExplain->Draw(); //ページが複数あった場合ページめくり可能である事を表示する

	(*image)[page]->Draw();
	for (auto itr : button) { itr->Draw(); }

}

void Title_Select_Explain::Reset() {
	page = 0; //初期ページに戻す
	run = this; //実行シーンを自身に戻す
	for (auto itr : button) { itr->Reset(); } //ボタンの状態をリセット
}
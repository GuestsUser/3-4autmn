#include "DxLib.h"

#include "Scene_Explain.h"
#include "Cmp_SelectSelector.h"
#include "../Code/OriginMath.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/Component/Cmp_ButtonGroup.h"
#include "../Code/Component/Button.h"
#include "../Code/Scene/Scene.h"

#include "Scene_GameTitle.h" //シーンジャンプのテストとしてタイトル画面を利用する

#include <deque>
#include <string>
#include <sstream>

Scene_Explain::Scene_Explain(std::deque<Cmp_Image*>& setImage, Scene* playGame) :image(&setImage), cursor(std::deque<Cmp_Image*>()), page(0) {
	run = this; //次回実行にはニュートラルとして自身を入れておく

	for (auto itr : *image) { itr->EditTranform()->EditPos().SetXYZ(640, 360, 0); } //ここで説明画像の表示位置を設定する

	if (image->size() > 1) { //説明画像が複数枚ある場合
		for (int i = 0; i < 2; ++i) {
			cursor.push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Cursor.png")), 1)); //ここに矢印画像の読み込みを入れる
			cursor[i]->EditTranform()->EditRotate().SetZ((270 - 180 * i) * OriginMath::Deg2Rad); //画像向きの設定、i==0は上向き、i==1は下向き
			cursor[i]->EditTranform()->EditPos().SetXYZ(1280 / 2, 640 * (i % 2) + 80 / 2, 0); //ここに位置設定を入れる
		}
	}
	
	for (int i = 0; i < 2; ++i) { //ボタン設定
		button.push_back(new Button(1165 - 200 * i, 680, 150, 60)); //空ボタンを追加
		
		const char* name = nullptr;
		Scene* playScene = nullptr;
		switch (i) { //読込画像決定用名前設定とクリック時に移行するシーンの設定
		case 0: name = "Resource/image/Explain_Button1.png"; playScene = playGame;  break; //playScene = new Scene_GameTitle(); //こちらを使えばタイトル画面へ移行する
		case 1: name = "Resource/image/Explain_Button2.png"; playScene = nullptr;  break;
		}

		button[i]->SetAlways(new Cmp_Image(*new int(LoadGraph(name)), 1, button[i]->EditTransform())); //ボタンに画像を追加
		button[i]->SetClick(new Cmp_ButtonGroup(*button[i], button)); //ボタンが押された際、押されたボタン以外を停止する機能の追加
		button[i]->SetClick(new Cmp_SelectSelector(playScene, &run, button)); //ボタンが押された際、runへexplain[i]を入れる機能の追加
	}
}

Scene_Explain::~Scene_Explain() {
	for (auto itr : *image) { delete itr; } //各要素はnewで精製されているので消しておく
	for (auto itr : cursor) { delete itr; }
	for (auto itr : button) { delete itr; }

	delete image; //imageは他所で作られた参照をこちらで管理する形式なので消しておく
}

void Scene_Explain::Update() {
	for (auto itr : *image) { itr->Update(); } //各種更新処理
	for (auto itr : cursor) { itr->Update(); }
	for (auto itr : button) { itr->Update(); }

	//表示ページ更新処理
	int max = image->size(); //ページ最大数
	if (max > 1) { //ページが複数ある場合
		int rotate = GetMouseWheelRotVol(); //マウスホイール回転量
		if (rotate <= -1) { page = (page + 1) % max; } //前方にまわしたらページ+1
		if (rotate >= 1) { page = page - 1 < 0 ? (page + max - 1) % max : (page - 1) % max; } //奥にまわした場合ページ-1
	}
	
	if (run != this) { 
		SetNext(run); //自身以外をrunに設定されたらそこへ向かえという意味合いなのでSetNext
		page = 0; //次使う用の初期化
		run = this; //次使う時用に戻しておく
	}
}
void Scene_Explain::Draw() {
	GetMouseWheelRotVol(); //最初の実行はDrawの方が早いのでマウスホイールの回転量を初期化する意味合いでこれを記す
	SetNext(this); //次使う時こちらが早いのでSetNextの初期化用に

	std::string pageNum = std::to_string(page + 1) + "/" + std::to_string(image->size()); //現在のページ数表示
	DrawString(1100, 32, pageNum.c_str(), GetColor(255, 255, 255)); //カラーは仮の物
	(*image)[page]->Draw();
	//for (auto itr : *image) { itr->Draw(); } //各種更新処理
	for (auto itr : cursor) { itr->Draw(); }
	for (auto itr : button) { itr->Draw(); }

}
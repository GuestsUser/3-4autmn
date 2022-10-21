#include "DxLib.h"
#include "Scene_GameTitle.h"
#include "Scene_Select.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"

Scene_GameTitle::Scene_GameTitle() : keyOld(KEY_FREE), image(LoadGraph("Resource/image/Title.png")) {} //初期化
Scene_GameTitle::~Scene_GameTitle() { DeleteGraph(image); } //読み込み画像の削除

void Scene_GameTitle::Update() { //毎回実行する処理
	int now = key->GetKeyState(REQUEST_MOUSE_LEFT); //現在のマウス左ボタンの入力状態の取得

	if (keyOld != KEY_FREE && now == KEY_PULL) { SetNext(new Scene_GameTitle()); } //前回までキーが離しっぱなしでない且つキーを離した瞬間次シーンへ移行

	keyOld = now; //今回の値を前回の物に記録する
}

void Scene_GameTitle::Draw() { DrawGraph(0, 0, image, FALSE); }

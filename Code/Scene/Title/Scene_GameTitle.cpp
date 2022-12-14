#include "DxLib.h"
#include "Scene_GameTitle.h"
#include "Scene_Select.h"
#include "Scene_Select.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"

Scene_GameTitle::Scene_GameTitle() : keyOld(KEY_FREE), image(LoadGraph("Resource/image/Title.png")),BGM(LoadSoundMem("Resource/bgm/Title.wav")),Click(LoadSoundMem("Resource/se/Pause_Click.wav")) {} //初期化
Scene_GameTitle::~Scene_GameTitle() { DeleteGraph(image); } //読み込み画像の削除

void Scene_GameTitle::Update() { //毎回実行する処理
	if (CheckSoundMem(BGM) == 0) {
		ChangeVolumeSoundMem(110, BGM);
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
	}
	int now = key->GetKeyState(REQUEST_MOUSE_LEFT); //現在のマウス左ボタンの入力状態の取得
	

	if (keyOld != KEY_FREE && now == KEY_PULL) { 
		PlaySoundMem(Click, DX_PLAYTYPE_BACK);
		SetNext(new Scene_Select()); 
		StopSoundMem(BGM);
	} //前回までキーが離しっぱなしでない且つキーを離した瞬間次シーンへ移行

	keyOld = now; //今回の値を前回の物に記録する
}

void Scene_GameTitle::Draw() { DrawGraph(0, 0, image, FALSE); }

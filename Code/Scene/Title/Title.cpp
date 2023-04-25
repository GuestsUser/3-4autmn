#include "DxLib.h"
#include "Title.h"
#include "Title_Select.h"
#include "Title_SoundSetting.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"

#include "Cmp_Sound.h"

Title::Title() : keyOld(KEY_FREE), image(LoadGraph("Resource/image/Title.png")) { //初期化
	bgm = new Cmp_Sound(LoadSoundMem("Resource/bgm/Title.wav"));
	click = new Cmp_Sound(LoadSoundMem("Resource/se/Pause_Click.wav"));

	Title_SoundSetting::SetUpTitleSelectBGM(*bgm); //bgmのステータスを設定
	Title_SoundSetting::SetUpTitleClick(*click); //clickのステータスを設定
	bgm->Play(); //bgmを流す
}
Title::~Title() { 
	DeleteGraph(image); //読み込み画像の削除
	delete bgm; //作成したサウンドの削除
	delete click;
}

void Title::Update() { //毎回実行する処理
	int now = key->GetKeyState(REQUEST_MOUSE_LEFT); //現在のマウス左ボタンの入力状態の取得
	
	if (keyOld != KEY_FREE && now == KEY_PULL) { 
		click->Play(); //クリック音を鳴らす
		bgm->Stop(); //bgmを止める
		SetNext(new Title_Select());
	} //前回までキーが離しっぱなしでない且つキーを離した瞬間次シーンへ移行

	keyOld = now; //今回の値を前回の物に記録する
}

void Title::Draw() { DrawGraph(0, 0, image, FALSE); }

//この部分のコメントアウトを外すとデバッグ終了時にnewの開放し忘れをメモリ数で通知してくれる
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#define new  ::new( _NORMAL_BLOCK, __FILE__, __LINE__ )

#include "DxLib.h"
#include "ConstVal.h"
#include "./Scene/Title/Scene_GameTitle.h"
#include "GetKey.h"
#include "SceneManager.h"
#include "Worldval.h"
#include "GlovalLoading.h"
//最初に実行したいシーンのヘッダーをインクルードしておく

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //デバッグ表示を可能にする
	ChangeWindowMode(true);

	if (DxLib_Init() == -1) { return -1; }		//初期化と異常が認められた場合の終了

	int fps = 1000000 / FPS; //割る値を変えると1秒間に行う処理回数を変更できる
	LONGLONG now = GetNowHiPerformanceCount();
	LONGLONG old = now;

	//ウィンドウの初期設定
	SetWindowText("PAC MAN");			//画面タイトル設定
	SetGraphMode(WINDOW_X, WINDOW_Y, 32);		//画面モードの設定
	SetBackgroundColor(0, 0, 0);		//画面の背景色の設定
	SetDrawScreen(DX_SCREEN_BACK);

	WorldVal::SetUp(); //シーンを跨いだ変数共有クラスの初期化
	GlovalLoading(); //GlovalLoading.cppの関数、WorldVal::Getで取り出せる値の用意を行うサンプル

	key = new KeySystem(); //キー入力受付用クラスの実体作成
	SceneManager* scm = new SceneManager(new Scene_GameTitle()); //引数に最初に実行したいシーン実体を入れる

	while (ProcessMessage() == 0 && (!CheckHitKey(KEY_INPUT_ESCAPE)) && key->GetKeyState(SELECT_KEY) != KEY_PUSH) { //GetKeyシステム使用例、backボタンが押された瞬間にfalseとなる
		//_RPTF1(_CRT_WARN, "%s\n", "test"); //デバッグ表示

		now = GetNowHiPerformanceCount(); //現在時刻の取得
		if (now - old > fps) { //前フレームの現在時刻との差が実行タイミングになっていた場合ゲーム処理、描写の実行
			key->KeyInput(); //キー入力更新
			old = now - (now - old); //差が実行タイミング以上だった場合そのままoldに現在時刻を入れると切り捨てられてしまうのでoldから実行タイミング超過分を引く事で超過分を加味した形にする
			ClearDrawScreen(); //画面の初期化
			if (!scm->Update()) { break; } //ウィンドウを閉じる指示を出されてたら終了
			scm->Draw(); //画面描写
		}
		ScreenFlip();
	}
	WorldVal::Destruct(); //値共有の実体破棄
	delete key;
	delete scm;
	DxLib_End();// ＤＸライブラリ使用の終了処理
	return 0;
}
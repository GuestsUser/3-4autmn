#include "SceneManager.h"
#include "./Scene/Scene.h"

bool SceneManager::Update() {
	//while (true) { //移行後のシーンも一度はupdateを呼び出す為ループ仕様
	//	run->Update(); //update実行
	//	Scene* next = run->GetNext(); //次シーンの取得
	//	if (run == next) { break; } //継続だったらループ抜け

	//	delete run; //移行を命令されたら現在シーンの削除
	//	if (next == nullptr) { run = nullptr; return false; } //終了処理
	//	run = next; //実行するシーンを次回の物に更新
	//}
	while (true) { //移行後のシーンはupdateの呼び出しを行わない仕様
		run->Update(); //update実行
		Scene* next = run->GetNext(); //次シーンの取得
		if (next != nullptr) { break; } //次回実行が空にされてなければループ抜け

		delete run; //現在シーンの削除
		run = nullptr; //値を空に
		return false; //mainにゲーム終了を通知する
	}
	return true; //Drawに処理を移す
}

void SceneManager::Draw() { run->Draw(); }
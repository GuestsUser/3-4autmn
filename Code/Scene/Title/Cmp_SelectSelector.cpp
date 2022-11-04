#include "Cmp_SelectSelector.h"
#include "../Code/Scene/Scene.h"
#include "../Code/Component/Button.h"

#include <deque>

void Cmp_SelectSelector::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止状態なら終了
	if (count == limit) { *gameRef = run; } //実行タイミングになったら指定シーンへ実行シーンを変更
	if (count > limit) { //処理がセレクト画面に戻ってきた時の処理
		for (auto itr : group) {
			itr->SetRunUpdateClick(false); //各ボタンは非クリック状態に戻す
			itr->SetRunUpdate(true); //ボタンの更新を再開する
			itr->SetRunClickMonitor(true); //クリック検知を有効化
		}
		count = 0; //再利用できるようcountは0に戻す
		return;
	}
	++count;
}

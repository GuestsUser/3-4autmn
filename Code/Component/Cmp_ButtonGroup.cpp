#include "Component.h"
#include "Button.h"
#include "Cmp_ButtonGroup.h"

#include <deque>

void Cmp_ButtonGroup::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止状態なら終了
	for (auto itr : group) { itr->SetRunUpdate(false); } //全てボタンのupdateを切る
	parent->SetRunUpdate(true); //親のボタンのupdateを有効化する
	parent->SetRunClickMonitor(false); //親のボタンのクリックを検知しないようにする

	SetRunUpdate(false); //自身の実行を切る
}
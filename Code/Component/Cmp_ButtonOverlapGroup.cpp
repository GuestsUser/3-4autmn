#include "Component.h"
#include "Button.h"
#include "Cmp_ButtonOverlapGroup.h"

#include <deque>

Cmp_ButtonOverlapGroup::Cmp_ButtonOverlapGroup(Button& setParent, bool setGroupDelManage, std::deque<Button*>* setArray) :parent(&setParent), group(setArray), isGroupDelManage(setGroupDelManage) {
	old = parent->GetPushState(); //範囲内クリック状態の初期化

	if (group == nullptr) { group = new std::deque<Button*>(); } //groupが空だった場合新規作成
	for (auto itr : *group) { monitorStateMemo.push_back(itr->GetRunClickMonitor()); } //group内Buttonのクリック検知状態記録変数の準備
}

Cmp_ButtonOverlapGroup::~Cmp_ButtonOverlapGroup() {
	if (isGroupDelManage) { delete group; } //groupの削除権があれば消しておく
}

void Cmp_ButtonOverlapGroup::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止状態なら終了
	if (old == parent->GetPushState()) { return; } //前回とクリック状態が同じの場合何もしない

	old = parent->GetPushState(); //oldを今回の物に揃える
	if (group->size() != monitorStateMemo.size()) { monitorStateMemo.resize(group->size()); } //groupの格納数とmonitor記憶変数のサイズを合わせる

	if (old == Button::State::free) { //今回がfreeにされていた場合
		for (int i = 0; i < group->size(); ++i) { (*group)[i]->SetRunClickMonitor(monitorStateMemo[i]); } //group内buttonのクリック検知動作可否を元に戻す
	}
	else { //pushにされていた場合
		for (int i = 0; i < group->size(); ++i) {
			monitorStateMemo[i] = (*group)[i]->GetRunClickMonitor(); //現在のクリック検知動作可否を保存する
			(*group)[i]->SetRunClickMonitor(false); //クリック検知をしないよう設定
		}
	}
}
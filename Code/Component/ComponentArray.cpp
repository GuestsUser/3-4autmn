#include "ComponentArray.h"

void ComponentArray::FullReset() {
	for (auto itr : cmp) { itr->FullReset(); } //完全初期化
}
void ComponentArray::Reset() {
	for (auto itr : cmp) { itr->Reset(); } //初期化
}

void ComponentArray::EraseCmp(Component* set) {
	for (auto itr : cmp) { if (itr == set) { delete set; return; } }
}
void ComponentArray::ClearCmp() {
	for (auto itr : cmp) { delete itr; }
}

void ComponentArray::Update() {
	if (!GetRunUpdate()) { return; } //このコンポーネント自身が実行不可なら追加機能も実行しない
	for (auto itr : cmp) { if (itr->GetRunUpdate()) { itr->Update(); } }
}
void ComponentArray::Draw() {
	if (!GetRunDraw()) { return; } //このコンポーネント自身が実行不可なら追加機能も実行しない
	for (auto itr : cmp) { if (itr->GetRunDraw()) { itr->Draw(); } }
}
void ComponentArray::SetRunUpdateBundle(bool set) {
	for (auto itr : cmp) { itr->SetRunUpdate(set); }
}
void ComponentArray::SetRunDrawBundle(bool set) {
	for (auto itr : cmp) { itr->SetRunDraw(set); }
}
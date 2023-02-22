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
	if (!GetRunUpdate()) { return; }
	for (auto itr : cmp) { if (itr->GetRunUpdate()) { itr->Update(); } }
}
void ComponentArray::Draw() {
	if (!GetRunDraw()) { return; }
	for (auto itr : cmp) { if (itr->GetRunDraw()) { itr->Draw(); } }
}
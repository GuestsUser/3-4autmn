#include "Component.h"
#include "Button.h"
#include "Cmp_ButtonGroup.h"

#include <deque>

void Cmp_ButtonGroup::Update() {
	for (auto itr : group) {
		if (itr != parent) { itr->SetRunUpdate(false); } //自身を持つButton以外のgroup内全てのButtonのUpdateを切る
	}
	SetRunUpdate(false); //自身の実行を切る
	SetRunDraw(false); //Drawは使ってないが念の為
}
#include "Cmp_SelectSelector.h"
#include "../Code/Scene/Scene.h"
#include "../Code/Component/Button.h"

#include <deque>

void Cmp_SelectSelector::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止状態なら終了
	if (count == limit) { //実行タイミングになったら実行シーンを変更
		if (run != nullptr) { *gameRef = run; } //runに何か入ってあればgameRefへ移し替え
		else { *gameRef = sceneCreator(); } //runが空ならsceneCreatorで新しいシーンを作成
	}
	++count;
}


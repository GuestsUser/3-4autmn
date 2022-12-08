#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Result.h"

SR_Result::SR_Result() {
	Result = LoadGraph("Resource/image/SR_MAP.png");
}

void SR_Result::Update() {
}

void SR_Result::Draw() {
	DrawGraph(0,0,Result,false);
}
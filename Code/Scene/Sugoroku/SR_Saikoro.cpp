#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "MapLoad.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"
#include <stdio.h>
#include <stdlib.h>

SR_Saikoro::SR_Saikoro() {
	LoadDivGraph("Resource/image/SR_Saikoro1.png",6,6,1,75,75,SR_Saikoro1,true);	/*âÊëúì«Ç›çûÇ›*/
	LoadDivGraph("Resource/image/SR_Saikoro2.png",6,6,1,75,75,SR_Saikoro2,true);	/*âÊëúì«Ç›çûÇ›*/
	y = 0;
	d = 0;
	i = 0;
	count = 0;
	SRand(123456); // óêêîÇÃèâä˙ílÇ123456Ç…ê›íËÇ∑ÇÈ
}

void SR_Saikoro::Update() {
	count++;
	if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
		Shuffle = true;
	}
	if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
		Shuffle = false;
	}
	if ((count / 4) % 2 == 0) {
		if (Shuffle == true) {
			/*y = rand() % 6 + 1;
			d = rand() % 6 + 1;*/
			y = GetRand(5);
			d = GetRand(5);
		}
	}
	DrawGraph(300, 300, SR_Saikoro1[y], true);
	DrawGraph(300, 400, SR_Saikoro2[d], true);
	Sum = y + d + 2;
}

void SR_Saikoro::Draw() {
	DrawString(0, 0, "ëoòZÉãÅ[Éãê‡ñæâÊëú", GetColor(255, 255, 255));
	DrawFormatString(900, 600, GetColor(255, 255, 255), "%d", Sum);
	DrawGraph(1050, 600, SR_Saikoro1[y], true);
	DrawGraph(1140, 600, SR_Saikoro2[d], true);
}

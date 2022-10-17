#pragma once

class PageOne {
private:
	int *card[5][13];

	int Mouse_X; //マウスのX座標
	int Mouse_Y; //マウスのY座標
	int Player_X; //プレイヤーのX座標
	int Player_Y; //プレイヤーのY座標

public:
	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();
};

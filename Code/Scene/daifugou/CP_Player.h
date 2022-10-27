#pragma once

class CareerPoker {
private:
	int i, y;
	int rule;//ルールの画像
	int stage;//ステージの画像
	int cards[5][13];//トランプ画像
public:
	void CP_Player_Initialize();
	void CP_Player_Finalize();
	void CP_Player_Update();
	void CP_Player_Draw();
};
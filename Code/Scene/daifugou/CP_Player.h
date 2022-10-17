#pragma once

class CareerPoker {
private:
	int rule;//ルールの画像
	int stage;//ステージの画像
public:
	void CP_Player_Initialize();
	void CP_Player_Finalize();
	void CP_Player_Update();
	void CP_Player_Draw();
};
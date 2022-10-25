#pragma once

class Karu_Game{
private:
	int Karu_Bg;	//ƒQ[ƒ€”wŒi
	int Karu_fuda;	//‚©‚é‚½‚ÌD‰æ‘œŠi”[—p

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();
};
#pragma once

class Karu_Game{
private:
	int Karu_Bg;	//�Q�[���w�i
	int Karu_fuda;	//���邽�̎D�摜�i�[�p

public:
	void Karu_Game_Initialize();
	void Karu_Game_Finalize();
	void Karu_Game_Update();
	void Karu_Game_Draw();
};
#pragma once

class CareerPoker {
private:
	int i, y;
	int rule;//���[���̉摜
	int stage;//�X�e�[�W�̉摜
	int cards[5][13];//�g�����v�摜
public:
	void CP_Player_Initialize();
	void CP_Player_Finalize();
	void CP_Player_Update();
	void CP_Player_Draw();
};
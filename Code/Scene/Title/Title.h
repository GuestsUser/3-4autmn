#pragma once
#include "./../Scene.h"

class Title : public Scene { //�ŏ��̃^�C�g�����
private:
	int keyOld; //�O��̍��N���b�N���͏�Ԃ�ۑ�����
	int image; //�^�C�g���摜�i�[�p�ϐ�
	int Click;
	int BGM;
public:
	Title();
	~Title();
	void Update();
	void Draw();
};
#pragma once
#include "./../Scene.h"

class Scene_GameTitle : public Scene { //�ŏ��̃^�C�g�����
private:
	int keyOld; //�O��̍��N���b�N���͏�Ԃ�ۑ�����
	int image; //�^�C�g���摜�i�[�p�ϐ�
	int Click;
	int BGM;
public:
	Scene_GameTitle();
	~Scene_GameTitle();
	void Update();
	void Draw();
};
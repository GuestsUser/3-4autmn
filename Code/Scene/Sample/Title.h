#pragma once
#include "./../Scene.h"

class Title : public Scene {
private:
	enum class State { Moving, Stop }; //Moving=�^�C�g����ʂ��ォ�����Ă��鏈�����s�� Stop=���V�[���ֈڍs����ׂɃ{�^�����͂��󂯕t���鏈�����s��
	State state; //Update�Ō��ݎ��s���ׂ������𕪊򂷂�ׂ̕ϐ�

	//���W�ϐ�
	int posX;
	int posY;
	int titleImage; //�^�C�g���摜�i�[�p�ϐ�
	int scrollSpeed; //��ʃX�N���[���̃X�s�[�h

	int* score; //WorldVal�����ɓ��ꂽ�A�h���X��ێ�����ϐ�
	int* hiscore; //��L���l�̕ۑ��p�ϐ�

	void Move(); //�摜�X�N���[���p�֐�
public:
	Title();
	~Title();
	void Update();
	void Draw();

};

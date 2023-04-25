#pragma once
#include "./../Scene.h"

#include "Cmp_3DSoundListener.h"

class Cmp_Sound;

class Title : public Scene { //�ŏ��̃^�C�g�����
private:
	int keyOld; //�O��̍��N���b�N���͏�Ԃ�ۑ�����
	int image; //�^�C�g���摜�i�[�p�ϐ�

	Cmp_Sound* bgm; //bgm�̃T�E���h���Ǘ�����R���|�[�l���g
	Cmp_Sound* click; //�N���b�N�̃T�E���h���Ǘ�����R���|�[�l���g
public:
	Title();
	~Title();
	void Update();
	void Draw();
};
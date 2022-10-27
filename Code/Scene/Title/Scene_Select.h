#pragma once
#include "./../Scene.h"

#include <deque>

class Button;
class Scene_Explain;

class Scene_Select :public Scene { //�Z���N�g���
	std::deque<Scene_Explain*> explain; //�Q�[���̐������
	std::deque<Button*> button; //������ʂ֔�΂��ׂ̃{�^��

	Scene* run; //���ݎ��s����V�[���Anullptr�Ŏ��g�Aexplain�̉��ꂩ�Ȃ炻�̃V�[���Aexplain�ɖ����V�[���������Ă����ꍇSetNext��run���Z�b�g���Ďw��Q�[���ֈڍs

public:
	Scene_Select();
	~Scene_Select();

	void Update();
	void Draw();
};
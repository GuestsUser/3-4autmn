#pragma once
#include "./../Scene.h"

#include <deque>

class Button;
class Title_Select_Explain;

class Title_Select :public Scene { //�Z���N�g���
	std::deque<Title_Select_Explain*> explain; //�Q�[���̐������
	std::deque<Button*> button; //������ʂ֔�΂��ׂ̃{�^��

	Scene* run; //���ݎ��s����V�[���Anullptr�Ŏ��g�Aexplain�̉��ꂩ�Ȃ炻�̃V�[���Aexplain�ɖ����V�[���������Ă����ꍇSetNext��run���Z�b�g���Ďw��Q�[���ֈڍs
private:
	int BGM;
public:
	Title_Select();
	~Title_Select();

	void Update();
	void Draw();
};
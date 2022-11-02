#pragma once
#include "../Code/Scene/Scene.h"

#include <deque>

class Cmp_Image;
class Button;
class Scene;

class Scene_Explain :public Scene {
	std::deque<Cmp_Image*>* image; //�����p�摜�A�Ăяo������deque�z����쐬���A���̃A�h���X���󂯎��`��
	std::deque<Cmp_Image*> cursor; //�X�N���[���\�ł��鎖���������摜
	std::deque<Button*> button; //�Q�[����ʂɔ�ԋ@�\������[0]�{�^���ƃZ���N�g��ʂɔ��[1]�{�^��
	Scene* run; //�����s����V�[������
	int page; //�����摜�̌��݃y�[�W��
	
public:
	Scene_Explain(std::deque<Cmp_Image*>& setImage, Scene* playGame);
	~Scene_Explain();

	void Update();
	void Draw();
};
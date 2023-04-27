#pragma once
#include "../Code/Scene/Scene.h"

#include <deque>
#include <functional>

class Cmp_Image;
class Cmp_Sound;
class Button;
class Scene;

class Title_Select_Explain :public Scene {
	std::deque<Cmp_Image*>* image; //�����p�摜�A�Ăяo������deque�z����쐬���A���̃A�h���X���󂯎��`��
	std::deque<Cmp_Image*> cursor; //�X�N���[���\�ł��鎖���������摜
	std::deque<Button*> button; //�Q�[����ʂɔ�ԋ@�\������[0]�{�^���ƃZ���N�g��ʂɔ��[1]�{�^��
	Cmp_Sound* scroll; //�}�E�X�z�C�[�����삪�������ꍇ�炷��
	Scene* run; //�����s����V�[������
	int page; //�����摜�̌��݃y�[�W��
	
public:
	Title_Select_Explain(std::deque<Cmp_Image*>& setImage, std::function<Scene* ()> sceneCreator);
	~Title_Select_Explain();

	void Update();
	void Draw();

	void Reset();
	void FullReset() { Reset(); }
};
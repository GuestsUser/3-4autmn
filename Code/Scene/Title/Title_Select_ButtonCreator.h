#pragma once

#include <deque>

class Button;
class Title_Select_Explain;
class Scene;

class Title_Select_ButtonCreator {

public:
	static void Creat(Scene& parent, std::deque<Title_Select_Explain*>& explain, std::deque<Button*>& button, Scene*& run); //�Z���N�g��ʂɕ\������e��Q�[���֔�ԃ{�^���̍쐬���s��

	//���̐����֎~
	Title_Select_ButtonCreator() = delete;
	Title_Select_ButtonCreator(const Title_Select_ButtonCreator&) = delete;
};
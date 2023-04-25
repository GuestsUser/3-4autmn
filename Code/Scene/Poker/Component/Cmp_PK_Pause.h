#pragma once
#include "Component.h"
#include <deque>

class Button;
class Cmp_Image;
class Poker;

class Cmp_PK_Pause :public Component { //�|�[�Y�{�^������N������|�[�Y��ʁA�����ꂽ���N���������̂�click�Ɋi�[���鎖�Apoker�ɏ�����߂��ہA�e�{�^���̑��@�\�����Z�b�g�������̂ł��̃R���|�[�l���g�͍Ō�ɕt���鎖
	Poker* poker; //�e�{�^������������poker�V�[��
	Button* parent; //���̃R���|�[�l���g�����e�{�^��

	Cmp_Image* back; //�w�i�摜
	std::deque<Button*> button; //�^�C�g�����֑J�ڂ���ׂ�UI�\���{�^������

	bool runClose; //true�ɂȂ�����Reset�����s���ă|�[�Y��ʂ��I������
	int count; //�|�[�Y��ʊJ�n����̌o�ߎ��ԋL�^
public:
	Cmp_PK_Pause(Button& set, Poker& poker);
	~Cmp_PK_Pause() { delete back; }

	void Update();
	void Draw();
private:
	void CloseOrder() { runClose = true; } //���s�����runClose��true�ɂ���A���L�����N���X�����@�\

	class DataSetting; //button�𐳂����ʒu�ɐݒ肷�铙�̃f�[�^�ݒ�N���X
	class PauseEnd; //�|�[�Y��ʏI���@�\�����N���X
	class NewGame; //�|�[�Y��ʂ���ăQ�[�����ŏ�����n�߂�ׂ̋@�\�����N���X
	class GameEnd; //�|�[�Y��ʂ���ăQ�[���Z���N�g�֖߂�ׂ̋@�\�����N���X
};
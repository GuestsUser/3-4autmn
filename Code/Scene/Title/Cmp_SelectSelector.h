#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Scene/Scene.h"

#include <deque>

class Button;

class Cmp_SelectSelector :public Component { //�Z���N�g��ʂŃQ�[�����Z���N�g�������A�Q�[���̐����֏������΂��ׂ�Button�p�ǉ��@�\
	int count; //Update�����s����Ă���̃J�E���g
	int limit; //count�����̒l�ɂȂ�������s�V�[������������

	Scene** gameRef; //���ۂɎ��s���s���Ă���V�[�����i�[����ύX�̎Q��(����ŏ�肭�������A�Ⴕ����Scene*�^�ł������̂��e�X�g������)
	Scene* run; //�N���b�N���ꂽ����s��������V�[��
	std::deque<Button*> group; //�{�^���O���[�v�A��{�I�Ƀ{�^���̏W�܂��Scene�ɑ����Ă�̂ł�����ł͍폜�Ǘ����s��Ȃ�

public:
	Cmp_SelectSelector(Scene* set, Scene** ref, std::deque<Button*>& setArray, int setLimit = 30) :run(set), gameRef(ref), group(setArray), count(0),limit(setLimit) { }

	void Update();

	const int GetRunTiming() const { return limit; } //�V�[�����ڂ��ւ��鏈�������s����^�C�~���O��Ԃ��֐�
};
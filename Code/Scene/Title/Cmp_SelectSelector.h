#pragma once
#include "../Code/Component/Component.h"

#include <deque>
#include <functional>

class Scene;
class Button;

class Cmp_SelectSelector :public Component { //�{�^�����N���b�N�������AgameRef��run�����閔��sceneCreator�ŐV���ȃV�[�������gameRef�փZ�b�g����Button�p�ǉ��@�\
	int count; //Update�����s����Ă���̃J�E���g
	int limit; //count�����̒l�ɂȂ�������s�V�[������������

	Scene** gameRef; //���ۂɎ��s���s���Ă���V�[�����i�[����ϐ��̎Q��
	Scene* run; //�N���b�N���ꂽ����s��������V�[��
	std::function<Scene* ()> sceneCreator; //���s�Q�[���V�[�����쐬����֐��|�C���^
public:
	Cmp_SelectSelector(Scene* set, Scene** ref, int setLimit = 30) :run(set), sceneCreator(nullptr), gameRef(ref), count(0), limit(setLimit) { }
	Cmp_SelectSelector(std::function<Scene* ()> sceneCreator, Scene** ref, int setLimit = 30) :run(nullptr), sceneCreator(sceneCreator), gameRef(ref), count(0), limit(setLimit) { }

	void Update();
	void Reset() { count = 0; } //�ė��p�ł���悤count��0�ɖ߂�
	void FullReset() { Reset(); } //Reset�Ɠ��l

	const int GetRunTiming() const { return limit; } //�V�[�����ڂ��ւ��鏈�������s����^�C�~���O��Ԃ��֐�
};
#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Scene/Scene.h"

class Cmp_SelectSelector :public Component {
	int count; //Update�����s����Ă���̃J�E���g
	int limit; //count�����̒l�ɂȂ�������s�V�[������������

	Scene** gameRef; //���ۂɎ��s���s���Ă���V�[�����i�[����ύX�̎Q��(����ŏ�肭�������A�Ⴕ����Scene*�^�ł������̂��e�X�g������)
	Scene* run; //�N���b�N���ꂽ����s��������V�[��

public:
	Cmp_SelectSelector(Scene* set, Scene** ref, int setLimit = 30) :run(set), gameRef(ref), count(0),limit(setLimit) { }
	~Cmp_SelectSelector();

	void Update();
};
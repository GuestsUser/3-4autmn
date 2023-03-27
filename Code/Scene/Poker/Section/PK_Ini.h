#pragma once
#include "Scene.h"
#include "Poker.h"
#include "Component.h"

#include <deque>

class Cmp_BetActionRecord;

class Poker::Ini :public Scene { //���E���h�J�n���̏������L����Update�����������N���X
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������

public:
	Ini(Poker& set);
	void Update();
};

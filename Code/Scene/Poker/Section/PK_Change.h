#pragma once
#include "Scene.h"
#include "Poker.h"

#include "Component.h"

#include <deque>

class Cmp_BetActionRecord;

class Poker::Change :public Scene { //�J�[�h���e�L�����֔z��t�F�C�Y
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������

	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
public:
	Change(Poker& set);
	void Update();
};
#pragma once
#include "Scene.h"
#include "Poker.h"

#include "Component.h"
#include "OriginMath.h"

#include <deque>
#include <string>

class Cmp_BetActionRecord;
class Cmp_Sound;

class Poker::ShowDown :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������

	std::deque<std::deque<int>> hand; //�e�L�����̃n���h�]����ێ�
	std::deque<Vector3> handPos; //�e�L�����̃n���h��\������ׂ̈ʒu�W�ߔz��
	std::deque<std::string> handString; //�e�L�����̃n���h��string�^�ŕێ�����z��

	int count;

	Vector3 titlePos; //�V���[�_�E���ł��鎖���������b�Z�[�W�̕\���ʒu
public:
	ShowDown(Poker& set);
	void Update();
	void Draw();
};
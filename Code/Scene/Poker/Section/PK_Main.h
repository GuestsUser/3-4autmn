#pragma once
#include "Scene.h"
#include "Poker.h"
#include "Component.h"

#include <deque>

class Cmp_BetActionRecord;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;
class Gage;

class Poker::Main :public Scene { //���C���x�b�g�t�F�C�Y
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������

	Gage* playerGage; //�v���C���[�ێ��̃Q�[�W
	Cmp_Gage_Border* playerGageBorder; //�v���C���[�̃Q�[�W�����ݒ�@�\�̃R���|�[�l���g
	Cmp_Gage_UpperBorder* playerGageUpper; //�v���C���[�̃Q�[�W����ݒ�@�\�̃R���|�[�l���g

	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	int phase; //���ꂪ����ڂ̃x�b�g�t�F�C�Y�������Ă����ϐ�
	int count; //���ԃJ�E���g

public:
	Main(Poker& set);
	void Update();
	void SetPhase(int set) { phase = set; } //���݂̃x�b�g�t�F�C�Y���Z�b�g�Arun��Main����ꂽ�����Ă����Ƃ���
};

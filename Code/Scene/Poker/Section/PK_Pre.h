#pragma once
#include "Scene.h"
#include "Poker.h"
#include "Component.h"

#include <deque>

class Cmp_BetActionRecord;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;
class Gage;

class Poker::Pre :public Scene { //�J�[�h���e�L�����֔z��t�F�C�Y
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������
	Gage* playerGage; //�v���C���[�ێ��̃Q�[�W
	Cmp_Gage_Border* playerGageBorder; //�v���C���[�̃Q�[�W�����ݒ�@�\�̃R���|�[�l���g
	Cmp_Gage_UpperBorder* playerGageUpper; //�v���C���[�̃Q�[�W����ݒ�@�\�̃R���|�[�l���g

public:
	Pre(Poker& set);
	void Update();
};
#pragma once
#include "../Scene.h"
#include "Poker.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Button.h"

#include <deque>

class Cmp_Image;
class Cmp_BetActionRecord;
class Vector3;

class Poker::NoContest :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������
	Button nextButton; //�N���b�N���鎖�Ŏ��V�[���ֈڍs����

	int count;
	int payOutTime; //���̃^�C�~���O�Ŏx�������s��
	int clickStartTime; //count�����̐��l�ɒB����ƃ{�^���N���b�N�̌��m���J�n����
	int blink; //���̎��ԊԊu�Ő�����_�ł�����

	Vector3 titlePos; //�m�[�R���e�X�g�ł��鎖���������b�Z�[�W�̕\���ʒu
	Vector3 explainPos; //�{�^�������̔z�u�ʒu
public:
	NoContest(Poker& set);
	void Update();
	void Draw();
};
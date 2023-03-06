#pragma once
#include "Poker.h"
#include "../Code/Component/Component.h"
#include <deque>

class PK_Dealer;
class Chara;
class Cmp_Image;

class Vector3;

class Cmp_ThinkingImage :public Component {
	Cmp_Image* image; //�l�����ł��鎖�������ׂ̉摜���i�[����ׂ̕ϐ�
	PK_Dealer* dealer; //�f�B�[���[�̎Q��
	Poker::Character parent; //���̃R���|�[�l���g�����L�����N�^�[�ԍ�

public:
	Cmp_ThinkingImage(Poker::Character parent, PK_Dealer& setDealer, const Vector3& place);

	~Cmp_ThinkingImage() { delete image; }


	void Update();
	void Draw();
};
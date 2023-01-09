#pragma once
#include "../Code/Component/Component.h"
#include <deque>

class PK_Dealer;
class Chara;
class Cmp_Image;

class Vector3;

class Cmp_ThinkingImage :public Component {
	Cmp_Image* image; //�l�����ł��鎖�������ׂ̉摜���i�[����ׂ̕ϐ�
	Chara* parent; //���̃R���|�[�l���g�����L�����̎Q��
	PK_Dealer* dealer; //�f�B�[���[�̎Q��
	std::deque<Chara*>* chara; //�L�����N�^�[���l�߂��z��̎Q��

	bool isPlayer; //parent���v���C���[�������ꍇtrue���L�^����

public:

	Cmp_ThinkingImage(Chara& setParent, std::deque<Chara*>& setChara, PK_Dealer& setDealer, const Vector3& place);

	~Cmp_ThinkingImage() { delete image; }


	void Update();
	void Draw();
};
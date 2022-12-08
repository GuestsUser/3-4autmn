#pragma once
#include "Component.h"
#include "../Code/OriginMath.h"

#include "../Code/GetKey.h"

#include <deque>

class Gage;

class Cmp_Gage_MouseControl :public Component {
	Gage* parent; //��������e�Q�[�W
	Vector3 area; //�}�E�X�ڐG���m�͈́A�Q�[�W���̉摜�̒��S�ʒu����̔��a�̌`���ŕێ�
	float step; //�Q�[�W�̍��ݕ��A�}�E�X�|�C���^���摜�T�C�Y/step�̈ʒu���z����x100/step��vol�����Z����

	int monitorKey; //���̃{�^�������������Q�[�W������s��
	bool control; //true�̊Ԃ̓Q�[�W������s���A���m�͈͓��Ń}�E�X�w��{�^�����������u�Ԃ��牟���Ă��true�A�������u��false�ɂȂ�
public:
	Cmp_Gage_MouseControl(Gage& setParent, const Vector3& setArea, float setStep = 100, int setKey = REQUEST_MOUSE_LEFT);

	void Update();
};
#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/OriginMath.h"

#include <deque>



class Button : public Component { //Component���p�����Ă��邪�ǉ��@�\�Ƃ������P�̐�������^�C�v�Ȃ̂Ŗ�����Cmp��t���Ȃ�����
	Cmp_Transform pos; //�{�^�����W�A���S���W�ɂȂ�
	Cmp_Transform area; //�N���b�N���m�͈́APos�Ɍ��m���a������
	bool isMonitorClick; //true�ŃN���b�N���m�Afalse�Ȃ猟�m���Ȃ�

	std::deque<Component*> always; //���Update�ADraw�����s����R���|�[�l���g
	std::deque<Component*> click; //�N���b�N�����m�����u��Update�ADraw��L��������R���|�[�l���g
	
public:
	Button(bool monitorSet = true, int setX = 0, int setY = 0, int setAreaX = 0, int setAreaY = 0) :pos(Cmp_Transform()), area(Cmp_Transform()), isMonitorClick(monitorSet), always(std::deque<Component*>()), click(std::deque<Component*>()) {
		pos.EditPos().SetXYZ(setX, setY, 0);
		area.EditPos().SetXYZ(setAreaX, setAreaY, 0);
	}
	~Button();

	void Update();
	void Draw();




	void SetAlways(Component* cmp) { always.push_back(cmp); } //cmp��always�֒ǉ�
	void EraseAlways(Component* cmp); //cmp���̂��폜���Aalways��������O�Aalways�ɑ��݂��Ȃ��R���|�[�l���g���w�肵���ꍇ�폜���Ȃ�
	void ClearAlways(); //always����ɂ���A�����Ă����R���|�[�l���g���̂͑S�č폜�����

	void SetClick(Component* cmp) { //cmp��click�֒ǉ�
		always.push_back(cmp); //�z��ɒǉ�
		cmp->SetRunUpdate(false); //�w��R���|�[�l���g��Update�ADraw�̓N���b�N�����m�������Atrue�ɂ����
		cmp->SetRunDraw(false);
	}
	void EraseClick(Component* cmp); //cmp���̂��폜���Aclick��������O
	void ClearClick(); //click����ɂ���A�����Ă����R���|�[�l���g���̂͑S�č폜�����


	const Cmp_Transform* ReadTransform() const { return &pos; } //���W�n����ǂݎ���p�`���Ŏ擾
	Cmp_Transform* EditTransform() { return &pos; } //���W�n����ҏW�\�ȏ�ԂŎ擾
	const Vector3* ReadArea() const { return &(area.ReadPos()); } //�N���b�N�͈͂�ǂݎ���p�`���Ŏ擾
	Vector3* EditArea() { return &(area.EditPos()); } //�N���b�N�͈͂�ҏW�\�ȏ�ԂŎ擾
};
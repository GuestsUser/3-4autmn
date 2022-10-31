#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/OriginMath.h"

#include <deque>



class Button : public Component { //Component���p�����Ă��邪�ǉ��@�\�Ƃ������P�̐�������^�C�v�Ȃ̂Ŗ�����Cmp��t���Ȃ�����
	enum class State { free, push }; //free=���펞�Apush=area�͈͓��ō��{�^�����������u�Ԃ���area���O��킸�������u�Ԃ܂�	
	State state; //�N���b�N��Ԃ��L�����Ă������߂̕ϐ�

	Cmp_Transform pos; //�{�^�����W�A���S���W�ɂȂ�
	Cmp_Transform area; //�N���b�N���m�͈́APos�Ɍ��m���a������AScale�̓N���b�N�����ۏk������@�\�����s�����ۊg�嗦�����ɖ߂���pos����l���󂯎�鎖�Ɏg�p����
	bool isMonitorClick; //true�ŃN���b�N���m�Afalse�Ȃ猟�m���Ȃ�

	std::deque<Component*> always; //���Update�ADraw�����s����R���|�[�l���g
	std::deque<Component*> click; //�N���b�N�����m�����u��Update�ADraw��L��������R���|�[�l���g
	
public:
	Button(int setX = 0, int setY = 0, int setAreaX = 0, int setAreaY = 0, bool monitorSet = true) :pos(Cmp_Transform()), area(Cmp_Transform()), isMonitorClick(monitorSet), state(State::free), always(std::deque<Component*>()), click(std::deque<Component*>()) {
		pos.EditPos().SetXYZ(setX, setY, 0);
		area.EditPos().SetXYZ(setAreaX, setAreaY, 0);
	}
	~Button();

	void Update();
	void Draw();



	void SetRunClickMonitor(bool set) { isMonitorClick = set; } //�N���b�N�����m���邩��ݒ�Atrue�Ō��m����Afalse�ł��Ȃ�
	const bool GetRunClickMonitor()const { return isMonitorClick; } //�N���b�N���m�̎��s�ۂ̎擾


	void SetRunUpdateAlways(bool set); //always��isUpdate���ꊇ�ݒ�
	void SetRunDrawAlways(bool set); //always��isDraw���ꊇ�ݒ�
	void SetRunUpdateClick(bool set); //click��isUpdate���ꊇ�ݒ�
	void SetRunDrawClick(bool set); //click��isDraw���ꊇ�ݒ�

	const bool GetRunUpdateAlways()const; //always��isUpdate�𒲍����A1�ł�true����������true��Ԃ�
	const bool GetRunDrawAlways()const; //always��isDraw�𒲍����A1�ł�true����������true��Ԃ�
	const bool GetRunUpdateClick()const; //click��isUpdate�𒲍����A1�ł�true����������true��Ԃ�
	const bool GetRunDrawClick()const; //click��isDraw�𒲍����A1�ł�true����������true��Ԃ�
	



	void SetAlways(Component* cmp) { always.push_back(cmp); } //cmp��always�֒ǉ�
	void EraseAlways(Component* cmp); //cmp���̂��폜���Aalways��������O�Aalways�ɑ��݂��Ȃ��R���|�[�l���g���w�肵���ꍇ�폜���Ȃ�
	void ClearAlways(); //always����ɂ���A�����Ă����R���|�[�l���g���̂͑S�č폜�����

	void SetClick(Component* cmp) { //cmp��click�֒ǉ�
		click.push_back(cmp); //�z��ɒǉ�
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
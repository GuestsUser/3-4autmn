#pragma once
#include "Component.h"
#include "ComponentArray.h"
#include "Cmp_Transform.h"

#include <deque>

//always��click�ɂ���
//always��click��Update��Button::Update�Ŏ��s����邪���̎��s����always��click�̏��ɂȂ��Ă���
//click�̓N���b�N�����m�����u�Ԃ���Update�ADraw�ǂ�������s�����

class Button : public Component { //Component���p�����Ă��邪�ǉ��@�\�Ƃ������P�̐�������^�C�v�Ȃ̂Ŗ�����Cmp��t���Ȃ�����
	enum class State { free, push }; //free=���펞�Apush=area�͈͓��ō��{�^�����������u�Ԃ���area���O��킸�������u�Ԃ܂�	
	State state; //�N���b�N��Ԃ��L�����Ă������߂̕ϐ�

	Cmp_Transform pos; //�{�^�����W�A���S���W�ɂȂ�
	Cmp_Transform area; //�N���b�N���m�͈́APos�Ɍ��m���a������AScale�̓N���b�N�����ۏk������@�\�����s�����ۊg�嗦�����ɖ߂���pos����l���󂯎�鎖�Ɏg�p����
	bool isMonitorClick; //true�ŃN���b�N���m�Afalse�Ȃ猟�m���Ȃ�

	ComponentArray always; //���Update�ADraw�����s����R���|�[�l���g
	ComponentArray click; //�N���b�N�����m�����u��Update�ADraw��L��������R���|�[�l���g
public:
	Button(int setX = 0, int setY = 0, int setAreaX = 0, int setAreaY = 0, bool monitorSet = true);

	void Update();
	void Draw();
	void Reset(); //always�̎��s�n��true�ɁAclick��false�ɐݒ肵�ǉ��@�\��Reset���Ăяo��
	void FullReset(); //Reset�̋@�\�ƒǉ��@�\��Reset�Ăяo���̑���FullReset���Ăяo�����

	void SetRunClickMonitor(bool set) { isMonitorClick = set; } //�N���b�N�����m���邩��ݒ�Atrue�Ō��m����Afalse�ł��Ȃ�
	bool GetRunClickMonitor()const { return isMonitorClick; } //�N���b�N���m�̎��s�ۂ̎擾

	bool GetRunUpdateAlways() const { return always.GetRunUpdate(); } //always::Update�����s�\�ł����true��Ԃ�
	bool GetRunUpdateClick() const { return click.GetRunUpdate(); } //click::Update�����s�\�ł����true��Ԃ�
	bool GetRunDrawAlways() const { return always.GetRunDraw(); } //always::Draw�����s�\�ł����true��Ԃ�
	bool GetRunDrawClick() const { return click.GetRunDraw(); } //click::Draw�����s�\�ł����true��Ԃ�
	
	ComponentArray* EditAlways() { return &always; } //always�̃R���|�[�l���g�W��ҏW�\�ȏ�ԂŕԂ�
	ComponentArray* EditClick() { return &click; } //click�̃R���|�[�l���g�W��ҏW�\�ȏ�ԂŕԂ�
	const ComponentArray* ReadAlways() const { return &always; } //always�̃R���|�[�l���g�W��ǂݎ���p�ŕԂ�
	const ComponentArray* ReadClick() const { return &click; } //click�̃R���|�[�l���g�W��ǂݎ���p�ŕԂ�


	Cmp_Transform* EditTransform() { return &pos; } //���W�n����ҏW�\�ȏ�ԂŎ擾
	Vector3* EditArea() { return &(area.EditPos()); } //�N���b�N�͈͂�ҏW�\�ȏ�ԂŎ擾
	const Cmp_Transform* ReadTransform() const { return &pos; } //���W�n����ǂݎ���p�`���Ŏ擾
	const Vector3* ReadArea() const { return &(area.ReadPos()); } //�N���b�N�͈͂�ǂݎ���p�`���Ŏ擾
};
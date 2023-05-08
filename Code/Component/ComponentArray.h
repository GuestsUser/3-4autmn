#pragma once

#include "Component.h"
#include <deque>
#include <typeinfo>

class ComponentArray: public Component { //�R���|�[�l���g��ǉ��@�\�Ƃ����`�ŕ������Ă�@�\
	std::deque<Component*> cmp;

public:
	ComponentArray() :cmp(std::deque<Component*>()) {}
	virtual ~ComponentArray() { ClearCmp(); }

	void Reset(); //�ǉ��@�\��Reset���Ăяo��
	void FullReset(); //�ǉ��@�\��FullReset���Ăяo��
	void Update(); //�ǉ��@�\��Update�����s�A���̃R���|�[�l���g���g�����s�֎~��ԂȂ�ǉ��@�\��Update�����s���Ȃ�
	void Draw(); //�ǉ��@�\��Draw�����s�AUpdate���l���s�֎~�Ȃ�ǉ��@�\�̕������s���Ȃ�

	void SetRunUpdateBundle(bool set); //�ǉ��@�\��isUpdate�ꊇ�w��
	void SetRunDrawBundle(bool set); //�ǉ��@�\��isDraw�ꊇ�w��

	void SetCmp(Component* set) { cmp.push_back(set); } //�ǉ��@�\�̒ǉ�
	void EraseCmp(Component* set); //�w��ǉ��@�\�폜
	void ClearCmp(); //�ǉ��@�\�S�폜

	std::deque<Component*>* EditCmpFull() { return &cmp; } //�R���|�[�l���g�S�Ă��擾�A�e�R���|�[�l���g�̒��g���C�ɂ��Ȃ��ꍇ��������g�p
	const std::deque<Component*>* ReadCmpFull() const { return &cmp; } //�R���|�[�l���g�S�Ă��擾�A������͓ǂݏo����p


	template<class T> T* EditCmp() { //�R���|�[�l���g�擾
		const type_info& master = typeid(T); //�擾����R���|�[�l���g�̌^�����Ă���
		for (Component* get : cmp) {
			if (typeid(*get) == master) { return dynamic_cast<T*>(get); }
		}
		return nullptr;
	}

	template<class T> void EditCmpMulti(std::deque<T*>& setArray) { //�R���|�[�l���g�擾�A�����N���X�̃R���|�[�l���g����������ꍇ�����S�Ă�Ԃ��^�C�v�AsetArray�Ɍ������ʂ����ĕԂ�
		const type_info& master = typeid(T); //�擾����R���|�[�l���g�̌^�����Ă���
		for (Component* get : cmp) {
			if (typeid(*get) == master) { setArray.push_back(dynamic_cast<T*>(get)); }
		}
	}

	template<class T> T* ReadCmp() const { //�R���|�[�l���g�擾�A�擾�����R���|�[�l���g�͏��������s�\�̓ǂݏo����p�`��
		const type_info& master = typeid(T); //�擾����R���|�[�l���g�̌^�����Ă���
		for (Component* get : cmp) {
			if (typeid(*get) == master) { return dynamic_cast<T*>(get); }
		}
		return nullptr;
	}
};
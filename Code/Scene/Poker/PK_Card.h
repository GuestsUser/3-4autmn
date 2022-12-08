#pragma once
#include "../Code/Component/Component.h"
#include <deque>

class Cmp_Image;
class Cmp_Transform;

class PK_Card :public Component { //�J�[�h�ɕK�v�ȕϐ��Q��Z�߂��N���X
	Cmp_Image* image; //�J�[�h�摜
	Cmp_Image* markingImage; //�}�[�L���O�p�摜
	int card; //�J�[�h�摜����ړI�̉摜�����o���Y�����ϐ�

	std::deque<Component*> cmp;
public:
	PK_Card();
	~PK_Card();

	void Reset(); //�V�������E���h���J�n���鎞�Ăяo���A�����ڂ��������(�}�[�L���O�Ȃ��A�����\��)�ɖ߂�
	void Place(int x, int y); //�J�[�h��z�u����

	const Cmp_Transform* ReadTransform() const; //���W�n����ǂݎ���p�`���Ŏ擾

	void Update() {}
	void Draw();

	int GetCard() const { return card; } //image�Ŏg�p����J�[�h�Y������Ԃ�

	void SetCard(int number) { card = number; } //image�Ŏg�p����Y������n���ăJ�[�h�̋����Ǝ�ނ�ݒ肷��
	void SetVisible(bool set); //false���Ɖ�ʏ�ł͗��Ԃ��ŕ\�������Atrue�ŃJ�[�h��������\�ŕ\��
	void SetMarking(bool set); //true�ŃJ�[�h�Ƀ}�[�L���O��\��

	void SetCmp(Component* set) { cmp.push_back(set); } //�ǉ��@�\�̒ǉ�
	template<class T> T* EditCmp() const { //�R���|�[�l���g�擾
		const type_info& master = typeid(T); //�擾����R���|�[�l���g�̌^�����Ă���
		for (Component* get : cmp) {
			if (typeid(*get) == master) { return dynamic_cast<T*>(get); }
		}
		return nullptr;
	}
};
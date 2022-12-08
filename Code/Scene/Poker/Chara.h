#pragma once
#include "../Code/Component/Component.h"
#include <deque>

#include <typeinfo>

class Cmp_Image;
class Cmp_Transform;
class PK_Card;

class Chara :public Component {
	static int coinIni; //�����������L�^�p�ϐ�
	int coin;
	std::deque<PK_Card*> card;
	std::deque<Cmp_Image*> coinBack;
	std::deque<Component*> cmp;

public:
	Chara();
	virtual ~Chara();
	void FullReset();
	void Reset();

	void Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos);
	void Update();
	void Draw();

	int GetCoint() const { return coin; }
	const std::deque<PK_Card*>* ReadCard() const { return &card; }
	void GetHandNum(std::deque<int>& set) const; //�n���h�𐔒l�����������擾�Aset�z����Ɋi�[���ĕԂ�

	void SetCoin(int set) { coin = set; }
	std::deque<PK_Card*>* EditCard() { return &card; }

	void SetCmp(Component* set) { cmp.push_back(set); } //�ǉ��@�\�̒ǉ�
	void EraseCmp(Component* set); //�w��ǉ��@�\�폜
	void ClearCmp(); //�ǉ��@�\�S�폜

	std::deque<Component*>* EditCmpFull() { return &cmp; } //�R���|�[�l���g�S�Ă��擾�A�e�R���|�[�l���g�̒��g���C�ɂ��Ȃ��ꍇ��������g�p

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
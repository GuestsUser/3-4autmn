#include "../Code/GetKey.h"
#include "Button.h"
#include "../Code/Component/Component.h"

#include <deque>


void Button::Update() {
	if (!GetRunUpdate()) { return; } //���s�̋����o�ĂȂ��ꍇ�I���
	for (auto itr : always) { itr->Update(); }
	for (auto itr : click) { itr->Update(); }


}

void Button::Draw() {
	if (!GetRunUpdate()) { return; } //���s�̋����o�ĂȂ��ꍇ�I���
	for (auto itr : always) { itr->Draw(); }
	for (auto itr : click) { itr->Draw(); }


}

Button::~Button() {
	ClearAlways();
	ClearClick();
}

void Button::SetAlways(Component* cmp) {
	for (Component* get : always) {
		if (get == cmp) { return; } //�w��R���|�[�l���g���ǉ��ς݂������ꍇ�ǉ������I��
	}
	always.push_back(cmp); //�����܂ŗ�����cmp�͐V�����R���|�[�l���g�Ȃ̂Ō��ɒǉ�
}

void Button::EraseAlways(Component* cmp) {
	for (Component* get : always) {
		if (get == cmp) { 
			//always.erase(get);
			delete get;
		}
	}
}

void Button::EraseAlways(Component* cmp) {
	for (auto itr = always.begin(); itr != always.end(); ++itr) { //�C�e���[�^�[�Ŏ擾�����������̂�for each�ł͂Ȃ�for���g��
		if (cmp == *itr) { //�C�e���[�^�[�ƃR���|�[�l���g����v�����ꍇ
			delete cmp; //�폜
			always.erase(itr); //�z�񂩂珜�O
			return; //�z�������Ă��܂����̂ŃC�e���[�^�[�������ɂȂ�������I���
		}
	}

}


void Button::ClearAlways() {
	for (Component* get : always) { delete get; } //�i�[����Ă��R���|�[�l���g�̍폜
	always.clear(); //�z��v�f�̑S����
}

void Button::EraseClick(Component* cmp) {
	for (auto itr = click.begin(); itr != click.end(); ++itr) { //�C�e���[�^�[�Ŏ擾�����������̂�for each�ł͂Ȃ�for���g��
		if (cmp == *itr) { //�C�e���[�^�[�ƃR���|�[�l���g����v�����ꍇ
			delete cmp; //�폜
			click.erase(itr); //�z�񂩂珜�O
			return; //�z�������Ă��܂����̂ŃC�e���[�^�[�������ɂȂ�������I���
		}
	}

}

void Button::ClearClick() {
	for (Component* get : click) { delete get; } //�i�[����Ă��R���|�[�l���g�̍폜
	click.clear(); //�z��̗v�f��S�폜
}




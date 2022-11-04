#include "../Code/GetKey.h"
#include "../Code/OriginMath.h"
#include "Button.h"
#include "Component.h"
#include "Cmp_Transform.h"


#include <deque>


void Button::Update() {
	if (!GetRunUpdate()) { return; } //���s�̋����o�ĂȂ��ꍇ�I���
	for (auto itr : always) { itr->Update(); } //�ǉ��@�\��Update���s
	for (auto itr : click) { itr->Update(); }

	Vector3 current = pos.ReadPos(); //�ʒu�ւ̃A�N�Z�X�V���[�g�J�b�g
	Vector3 rad = area.ReadPos(); //�͈͂ւ̃A�N�Z�X�V���[�g�J�b�g
	int x = -1; //�}�E�Xx
	int y = -1; //�}�E�Xy
	GetMousePoint(&x, &y); //�}�E�X�ʒu�擾
	bool hit = x < current.GetX() + rad.GetX() && x > current.GetX() - rad.GetX() && y < current.GetY() + rad.GetY() && y > current.GetY() - rad.GetY(); //�͈͓��ɃJ�[�\��������ꍇtrue


	if (!isMonitorClick) { return; } //�N���b�N���m�֎~�������Ă���΂����ŏI���
	switch (state) {
	case Button::State::free: //���펞����
		if (hit && key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //�J�[�\�����͈͓��ɂ����Ԃŉ������u�Ԃ����m
			float shrink = 0.7; //�N���b�N�����ۂ̏k���\���ׂ̈̊g��{��

			area.EditScale() = pos.ReadScale(); //���݂̊g��󋵂�area�ɕۑ�����
			pos.EditScale() *= shrink; //���݃T�C�Y�ɏk���{�����|���ďk���T�C�Y���o��
			state = State::push; //state��������Ԃֈڍs����
		}
		
		break;

	case Button::State::push: //�����Ă���Ԃ̏���
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PULL) { //�������u�Ԃ����m
			pos.EditScale() = area.ReadScale(); //�g�嗦�����̕��ɖ߂�
			state = State::free; //state�𕽏�ֈڍs����

			if (hit) { //�͈͓��ɃJ�[�\������������Ԃŗ������ꍇclick�̏��������s���ׂ��A�e����s�ۂ�true�ɂ���
				for (auto itr : click) { 
					itr->SetRunUpdate(true); 
					itr->SetRunDraw(true);
					itr->Update(); //���̌�Draw�����s�����̂�Update�����s���Ă���
				}
			}
		}


		break;
	}

}

void Button::Draw() {
	if (!GetRunDraw()) { return; } //���s�̋����o�ĂȂ��ꍇ�I���
	for (auto itr : always) { itr->Draw(); }
	for (auto itr : click) { itr->Draw(); }


}

Button::~Button() {
	ClearAlways();
	ClearClick();
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

void Button::SetRunUpdateAlways(bool set) {
	for (auto itr : always) { itr->SetRunUpdate(set); }
}
void Button::SetRunDrawAlways(bool set) {
	for (auto itr : always) { itr->SetRunDraw(set); }
}
void Button::SetRunUpdateClick(bool set) {
	for (auto itr : click) { itr->SetRunUpdate(set); }
}
void Button::SetRunDrawClick(bool set) {
	for (auto itr : click) { itr->SetRunDraw(set); }
}


const bool Button::GetRunUpdateAlways()const {
	for (auto itr : always) { //always�S����
		if (itr->GetRunUpdate()) { return true; } //true��1�ł������true��Ԃ�
	}
	return false; //1��true��������Ȃ����false��Ԃ�
}
const bool Button::GetRunDrawAlways()const {
	for (auto itr : always) { //always�S����
		if (itr->GetRunDraw()) { return true; } //true��1�ł������true��Ԃ�
	}
	return false; //1��true��������Ȃ����false��Ԃ�
}
const bool Button::GetRunUpdateClick()const {
	for (auto itr : click) { //click�S����
		if (itr->GetRunUpdate()) { return true; } //true��1�ł������true��Ԃ�
	}
	return false; //1��true��������Ȃ����false��Ԃ�
}
const bool Button::GetRunDrawClick()const {
	for (auto itr : click) { //click�S����
		if (itr->GetRunDraw()) { return true; } //true��1�ł������true��Ԃ�
	}
	return false; //1��true��������Ȃ����false��Ԃ�
}



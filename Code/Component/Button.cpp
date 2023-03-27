#include "Button.h"

#include "Component.h"
#include "ComponentArray.h"
#include "Cmp_Transform.h"

#include "../Code/GetKey.h"
#include "../Code/OriginMath.h"

#include <deque>

void AppendArrayStateReset(ComponentArray& always, ComponentArray& click) { //always��click�̎��s�n�������̕��ɒ���
	always.SetRunUpdate(true); //��Ɏ��s�ł���悤true
	always.SetRunDraw(true);

	click.SetRunUpdate(false); //�N���b�N�����u�Ԏ��s�J�n����悤false
	click.SetRunDraw(false);
}

void ButtonStateReset(Button& button) { //button��Update�����s��Ԃ����Z�b�g
	button.SetRunUpdate(true);
	button.SetRunDraw(true);
	button.SetRunClickMonitor(true);
}

Button::Button(int setX, int setY, int setAreaX, int setAreaY, bool monitorSet) :pos(Cmp_Transform()), area(Cmp_Transform()), isMonitorClick(monitorSet), state(State::free), always(ComponentArray()), click(ComponentArray()) {
	pos.EditPos().SetXYZ(setX, setY, 0);
	area.EditPos().SetXYZ(setAreaX, setAreaY, 0);
	AppendArrayStateReset(always, click); //click�͍ŏ�������s����Ȃ��悤�ɐݒ肷��
}

void Button::Update() {
	if (!GetRunUpdate()) { return; } //���s�̋����o�ĂȂ��ꍇ�I���
	if (isMonitorClick) { //�N���b�N���m�����AMonitor��false�Ȃ���s���Ȃ�
		Vector3 current = pos.ReadPos(); //�ʒu�ւ̃A�N�Z�X�V���[�g�J�b�g
		Vector3 rad = area.ReadPos(); //�͈͂ւ̃A�N�Z�X�V���[�g�J�b�g
		int x = -1; //�}�E�Xx
		int y = -1; //�}�E�Xy
		GetMousePoint(&x, &y); //�}�E�X�ʒu�擾
		bool hit = x < current.GetX() + rad.GetX() && x > current.GetX() - rad.GetX() && y < current.GetY() + rad.GetY() && y > current.GetY() - rad.GetY(); //�͈͓��ɃJ�[�\��������ꍇtrue

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
					click.SetRunUpdate(true);
					click.SetRunDraw(true);
				}
			}
			break;
		}
	}

	always.Update(); //�ǉ��@�\��Update���s
	click.Update();
}

void Button::Draw() {
	if (!GetRunDraw()) { return; } //���s�̋����o�ĂȂ��ꍇ�I���
	always.Draw(); //�ǉ��@�\��Draw���s
	click.Draw();
}

void Button::Reset() {
	AppendArrayStateReset(always, click); //�ǉ��@�\�̎��s�ۂ����ɖ߂�
	ButtonStateReset(*this); //button�̃N���b�N���m�A���s��Ԃ����ɖ߂�
	always.Reset(); //�ǉ��@�\��Reset���Ăяo��
	click.Reset();
}

void Button::FullReset() {
	AppendArrayStateReset(always, click); //�ǉ��@�\�̎��s�ۂ����ɖ߂�
	ButtonStateReset(*this); //button�̃N���b�N���m�A���s��Ԃ����ɖ߂�
	always.FullReset(); //�ǉ��@�\��FullReset���Ăяo��
	click.FullReset();
}

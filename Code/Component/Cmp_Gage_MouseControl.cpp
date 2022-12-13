#include "DxLib.h"
#include "Gage.h"

#include "Component.h"
#include "Cmp_Gage_MouseControl.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include "../Code/GetKey.h"
#include "../Code/OriginMath.h"

#include <deque>
#include <math.h>

Cmp_Gage_MouseControl::Cmp_Gage_MouseControl(Gage& setParent, const Vector3& setArea, float setStep, int setKey) :parent(&setParent), area(setArea), step(setStep), monitorKey(setKey), control(false) {}


void Cmp_Gage_MouseControl::Update() {
	if (!GetRunUpdate()) { return; }

	int mouseX = -1; //�}�E�Xx
	int mouseY = -1; //�}�E�Xy
	GetMousePoint(&mouseX, &mouseY); //�}�E�X�ʒu�擾



	if (control) { //�Q�[�W���쏈��
		Vector3 imagePos[] = { Vector3(), Vector3() ,Vector3() ,Vector3() }; //���̉摜�̕ό`���_�A����A�E��A�E���A�����̊i�[��
		Cmp_Transform iniScale = Cmp_Transform(*parent->ReadBaseGage()->ReadTranform()); //�M���ĂȂ���Ԃ̎��̊g�嗦�𕜌�����
		iniScale.EditScale().SetX(parent->GetIniSize()); //�����gx�g�嗦���i�[

		int sizeX = -1; //�摜�T�C�Y�i�[�p
		int sizeY = -1;
		GetGraphSize(*parent->ReadFullGage()->ReadImage(), &sizeX, &sizeY); //�T�C�Y�擾
		OriginMath::VertexModification(imagePos, Vector3(sizeX, sizeY), iniScale, parent->ReadFullGage()->GetDrawHorizonPivot(), OriginMath::VerticalPivot::center); //���̉摜��ό`

		for (int i = 1; i < 4; ++i) { imagePos[i] -= imagePos[0]; } //imagePos[0]����ɕύX����
		mouseX -= imagePos[0].GetX(); //�}�E�X�������ύX��K�p
		mouseY -= imagePos[0].GetY();

		float imageRotate = parent->ReadFullGage()->ReadTranform()->ReadRotate().GetZ(); //�摜�̉�]���擾

		float mouseLine = sqrt(pow(mouseX * cos(imageRotate), 2) + pow(mouseY * sin(imageRotate), 2)); //�摜��]�ɉ����ă}�E�X���猴�_�܂ł̃��C������擾���鐔�l�ɐ������|����
		float fullLine = sqrt(pow(imagePos[1].GetX(), 2) + pow(imagePos[1].GetY(), 2)); //�Q�[�W�̍ő�l����

		float gage = mouseLine / fullLine; //����̃Q�[�W�ʁA�X�e�b�v����O
		parent->SetVol((float)(1 / step) * (int)(gage / (1 / step))); //step�̔{���ȉ��̃Q�[�W�ʂ͐؂�̂Ă���悤�ɃQ�[�W�փZ�b�g

		if (key->GetKeyState(monitorKey) == KEY_PULL) { control = false; } //�Ď��L�[�������ꂽ��Q�[�W������ꎞ�I��
		return; //�I���
	}



	Vector3 pos[] = { Vector3(), Vector3() ,Vector3() ,Vector3() }; //����̈�̕ό`���_�A����A�E��A�E���A�����̊i�[��
	OriginMath::VertexModification(pos, area, *parent->ReadBaseGage()->ReadTranform(), parent->ReadFullGage()->GetDrawHorizonPivot(), parent->ReadFullGage()->GetDrawVerticalPivot()); //�}�E�X������Q�[�W�摜�ɍ��킹�ĕό`

	if (fmod(parent->ReadBaseGage()->ReadTranform()->ReadRotate().GetZ(), OriginMath::MPI / 2) == 0) { //�Q�[�W�ɉ�]���������ĂȂ������ꍇ
		control = mouseX > pos[0].GetX() && mouseX < pos[1].GetX() && mouseY > pos[0].GetY() && mouseY < pos[2].GetY() && key->GetKeyState(monitorKey) == KEY_PUSH; //���ʂɔ͈̓`�F�b�N����
		return; //�����
	}

	LinerFunction line[] = { LinerFunction(pos[0],pos[1]),LinerFunction(pos[1],pos[2]),LinerFunction(pos[2],pos[3]),LinerFunction(pos[3],pos[0]) }; //����̈�̋��E���ꎟ�֐��ŕێ�

	bool plus = false; //�}�E�X�ʒu����x���֕��s�ɐ���L�΂����ہAline�ɐڐG����x�ʒu���}�E�Xx���傫�������ꍇ�����true�Ƃ���
	bool minus = false; //x��菬�����Ȃ炱������true�ɂ���
	
	for (int i = 0; i < 4; ++i) { //��]�ɉ������͈̓`�F�b�N
		int next = (i + 1) % 4; //line��0��1�̂悤�ɗv�f�̏�����������1�傫�����ֈ�����Ă������̂�line��2�_���Ai���n�_�Anext���I�_�Ƃ��Ďg����

		int x = line[i].GetX(mouseY); //�}�E�Xy�ƍ���̃��C�����ڐG����x�n�_

		int min = pos[i].GetX(); //��]�ɂ��pos�z��̍��W���傫���v�f���ς�鎖������̂�min�Abig�ɓ����Ƃ����`�őΉ�����
		int big = pos[next].GetX();
		if (pos[i].GetX() > pos[next].GetX()) { min = pos[next].GetX(); big = pos[i].GetX(); } //�v�f�̑召��������ꍇ���꒼��
		if (x >= min && x <= big) { //x��line��2�_�̊Ԃɂ������ꍇtrue
			if (x > mouseX) { plus = true; } //x���}�E�X���傫���ꍇplus��true
			else { minus = true; } //�����łȂ��Ȃ�minus��true
		}
		if (plus && minus) { break; } //�}�E�X�ʒu����x���֕��s�ɐL�΂�������line�ɐڐG���Ď~�߂��ہA+������-�����ɉ��тĂ����ꍇ�͈͓��Ƀ}�E�X�����݂���̂ł�������͕s�v
	}

	if (plus && minus && key->GetKeyState(monitorKey) == KEY_PUSH) { control = true; } //����͈͓��ɂ��銎�Ď��L�[���������Ȃ玟����Q�[�W������J�n����
}
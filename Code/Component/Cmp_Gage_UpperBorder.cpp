#include "Component.h"
#include "Cmp_Gage_UpperBorder.h"

#include "Gage.h"

void Cmp_Gage_UpperBorder::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~�Ŏ��s���Ȃ�
	if (parent->GetVol() * 1 > border) { parent->SetVol(border); } //�{�[�_�[���Q�[�W�������Ă���ꍇ�{�[�_�[�̒l�ɃZ�b�g����
}
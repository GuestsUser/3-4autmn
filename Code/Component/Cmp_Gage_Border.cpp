#include "Component.h"
#include "Cmp_Gage_Border.h"

#include "Gage.h"

void Cmp_Gage_Border::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~�Ŏ��s���Ȃ�
	if (parent->GetVol() * 100 < border) { parent->SetVol(border * 0.01); } //�{�[�_�[���Q�[�W��������Ă���ꍇ�{�[�_�[�̒l�ɃZ�b�g����
}
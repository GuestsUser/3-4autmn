#include "Component.h"
#include "Cmp_Gage_Border.h"

#include "Gage.h"

void Cmp_Gage_Border::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~�Ŏ��s���Ȃ�
	if (parent->GetVol() < border) { parent->SetVol(border); } //�{�[�_�[���Q�[�W��������Ă���ꍇ�{�[�_�[�̒l�ɃZ�b�g����
}
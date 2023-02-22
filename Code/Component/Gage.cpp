#include "Gage.h"

#include "Component.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include "../Code/OriginMath.h"

#include <deque>

Gage::Gage(Cmp_Image& baseImgae, Cmp_Image& fullImage, int iniVol) :base(&baseImgae), full(&fullImage), vol(iniVol) {
	fullImage.SstDrawPivot(OriginMath::HorizonPivot::left, OriginMath::VerticalPivot::center); //�L�������ݒ�
	iniSize = fullImage.ReadTranform()->ReadScale().GetX(); //�����g�嗦�擾
}

void Gage::Reset() { cmp.Reset(); } //�R���|�[�l���g��Reset���Ăяo��
void Gage::FullReset() { cmp.FullReset(); } //�R���|�[�l���g��FullReset���Ăяo��


Gage::~Gage() {
	delete full;
	delete base;
}

void Gage::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~���o�Ă���Ύ��s���Ȃ�
	cmp.Update(); //�ǉ��@�\�̎��s
}

void Gage::Draw() {
	if (!GetRunDraw()) { return; } //���s�֎~���o�Ă���Ύ��s���Ȃ�

	full->EditTranform()->EditScale().SetX(iniSize * vol); //�Q�[�W���̃T�C�Y�ݒ�

	base->Draw(); //�x�[�X�`��
	full->Draw(); //���̕`��

	cmp.Draw(); //�ǉ��@�\�`�ʎ��s
}
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

Gage::~Gage() {
	delete full;
	delete base;
	for (auto itr : cmp) { delete itr; }
}

void Gage::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~���o�Ă���Ύ��s���Ȃ�
	for (auto itr : cmp) { itr->Update(); } //�ǉ��@�\�̎��s
}

void Gage::Draw() {
	if (!GetRunDraw()) { return; } //���s�֎~���o�Ă���Ύ��s���Ȃ�

	full->EditTranform()->EditScale().SetX(iniSize * vol * 0.01); //�Q�[�W���̃T�C�Y�ݒ�

	base->Draw(); //�x�[�X�`��
	full->Draw(); //���̕`��
}
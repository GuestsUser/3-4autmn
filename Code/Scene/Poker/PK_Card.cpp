#include "DxLib.h"

#include "PK_Card.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"

#include <deque>

PK_Card::PK_Card() :card(0), cmp(std::deque<Component*>()) {
	int* handle = new int[53];
	LoadDivGraph("Resource/image/poker_card.png", 53, 13, 5, 120, 150, handle); //�J�[�h�摜�ǂݍ���
	image = new Cmp_Image(*handle, 53); //�J�[�h�摜�i�[

	markingImage= new Cmp_Image(*new int(LoadGraph("Resource/image/poker_card.png")), 1); //�}�[�L���O�摜���i�[

	Reset(); //�����ڂ̏�����
}
PK_Card::~PK_Card() { //new�����摜�n�͏I���Ƌ��ɍ폜
	delete image;
	delete markingImage;
	for (auto itr : cmp) { delete itr; }
}

void PK_Card::Reset() {
	SetVisible(false); //�J�[�h�𗠑��\����
	SetMarking(false); //�}�[�L���O�͔�\����
}

void PK_Card::Place(int x, int y) {
	image->EditTranform()->EditPos().SetXYZ(x, y, 0);
	markingImage->EditTranform()->EditPos().SetXYZ(x, y, 0);
}

void PK_Card::Draw() {
	if (!GetRunDraw()) { return; } //���s�֎~���߂�����Ύ��s���Ȃ�
	image->Draw();
	markingImage->Draw();
}

void PK_Card::SetVisible(bool set) {
	if (set) { image->SetAnimeSub(card); } //true�Ȃ�\���摜��\�̕��ɕύX
	else { image->SetAnimeSub(52); } //false�Ȃ痠����
}
void PK_Card::SetMarking(bool set) { markingImage->SetRunDraw(set); } //true�Ń}�[�L���O�\�����s���悤�ɂ���

const Cmp_Transform* PK_Card::ReadTransform() const { return image->ReadTranform(); }
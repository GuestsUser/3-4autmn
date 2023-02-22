#include "DxLib.h"

#include "PK_Card.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/ComponentArray.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"

#include <deque>

PK_Card::PK_Card() :card(0), drawMode(DrawMode::front), cmp(ComponentArray()) {
	int* handle = new int[54];
	LoadDivGraph("Resource/image/poker_card.png", 54, 13, 5, 120, 150, handle); //�J�[�h�摜�ǂݍ���
	image = new Cmp_Image(*handle, 53); //�J�[�h�摜�i�[

	markingImage= new Cmp_Image(*new int(LoadGraph("Resource/image/poker_card_marking.png")), 1); //�}�[�L���O�摜���i�[

	Reset(); //�����ڂ̏�����
}
PK_Card::~PK_Card() { //new�����摜�n�͏I���Ƌ��ɍ폜
	delete image;
	delete markingImage;
}

void PK_Card::Reset() {
	SetDrawMode(DrawMode::back); //�J�[�h�𗠑��\����
	SetMarking(false); //�}�[�L���O�͔�\����
}

void PK_Card::Place(int x, int y) {
	image->EditTranform()->EditPos().SetXYZ(x, y, 0);
	markingImage->EditTranform()->EditPos().SetXYZ(x, y, 0);
}

void PK_Card::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~���߂�����Ύ��s���Ȃ�
	cmp.Update();
}


void PK_Card::Draw() {
	if (!GetRunDraw()) { return; } //���s�֎~���߂�����Ύ��s���Ȃ�

	switch (drawMode) {
	case PK_Card::DrawMode::back:image->SetAnimeSub(52); break; //���w��Ȃ�J�[�h�̎�ޖ�킸�Y�����𗠂̕��Ɏw��
	case PK_Card::DrawMode::front: image->SetAnimeSub(card); break; //�\�����[�h���\�w��̏ꍇ�摜�Y���������݃J�[�h�ɐݒ�
	case PK_Card::DrawMode::fold: image->SetAnimeSub(53); break; //fold�\���̏ꍇ�D�F�J�[�h����ޖ�킸�\������
	}
	
	image->Draw();
	markingImage->Draw();

	cmp.Draw();
}

void PK_Card::SetMarking(bool set) { markingImage->SetRunDraw(set); } //true�Ń}�[�L���O�\�����s���悤�ɂ���

const Cmp_Transform* PK_Card::ReadTransform() const { return image->ReadTranform(); }
Cmp_Transform* PK_Card::EditTransform() { return image->EditTranform(); }

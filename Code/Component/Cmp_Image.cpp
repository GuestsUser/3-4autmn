#include "DxLib.h"

#include "Cmp_Image.h"
#include "Component.h"
#include "Cmp_Transform.h"
#include "../OriginMath.h"

#include <deque>

void DelImage(int* gh, int len) { //�摜�̍폜�A�O�����J�������Ȃ��������炱����ɋL��
	if (gh == nullptr) { return; } //��Ȃ牽�����Ȃ�
	if (len == 1) { DeleteGraph(*gh); delete gh; return; } //�v�f����Ȃ�P�̗p�폜
	for (int i = 0; i < len; ++i) { DeleteGraph(gh[i]); } //�z����
	delete[] gh; //�����Ȃ�z��p�폜
}

void Cmp_Image::SetImage(int& setGh, int setLen) {
	DelImage(gh, length); //�O�̂��ߍ폜�֐���ʂ�m���ɉ摜����̏�Ԃɂ���
	gh = &setGh;
	length = setLen;
}

Cmp_Image::Cmp_Image(int& setGh, int setLen, Cmp_Transform* setTs, int setUse) :gh(nullptr), length(1), cmp(std::deque<Component*>()), ts(setTs), use(setUse), isSelfTs(false), drawPivotHorizon(OriginMath::HorizonPivot::center), drawPivotVertical(OriginMath::VerticalPivot::center) {
	SetImage(setGh, setLen); 
	if (setTs == nullptr) { ts = new Cmp_Transform(); isSelfTs = true; } //Transform���󂯎��Ȃ������ꍇ
}

Cmp_Image::~Cmp_Image() {
	DelImage(gh, length);
	for (Component* get : cmp) { delete get; } //�i�[����Ă��R���|�[�l���g�̍폜
	if (isSelfTs) { delete ts; } //Transform���ȊǗ��������ꍇ�폜���Ă���
}

void Cmp_Image::Update() {
	if (!GetRunUpdate()) { return; } //false�̏ꍇ���s���Ȃ�
	for (Component* get : cmp) { get->Update(); }
}



void Cmp_Image::Draw() {
	if (!GetRunDraw()) { return; } //false�̏ꍇ���s���Ȃ�
	for (Component* get : cmp) { get->Draw(); }

	Vector3 pos[4]; //�g�k��]�ό`���_�ێ��pVector3
	int* sizeX = nullptr; //�摜�T�C�Y�i�[�v
	int* sizeY = nullptr;
	int sub = length > 1 ? sub = gh[use] : sub = *gh; //�z��Ȃ�draw_sub�Y�����̈ʒu�̉摜���g�p

	GetGraphSize(sub, sizeX, sizeY); //�T�C�Y�擾
	OriginMath::VertexModification(pos, Vector3(*sizeX, *sizeY), *ts, drawPivotHorizon, drawPivotVertical); //��]�A�g���K�p�������_���W���i�[

	DrawModiGraph(pos[0].GetX(), pos[0].GetY(), pos[1].GetX(), pos[1].GetY(), pos[2].GetX(), pos[2].GetY(), pos[3].GetX(), pos[3].GetY(), sub, true); //�`��
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255); //�ǉ��������ŘM����\��������̂ŕ`�ʌ㏉�������Ă���
}


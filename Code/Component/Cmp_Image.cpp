#include "DxLib.h"

#include "Cmp_Image.h"
#include "Component.h"
#include "Cmp_Transform.h"
#include "../OriginMath.h"

#include <deque>

void DelImage(int* gh, int len) { //�摜�̍폜�A�O�����J�������Ȃ��������炱����ɋL��
	if (len == 1) { delete gh; } //�v�f����Ȃ�P�̗p�폜
	else { delete[] gh; } //�����Ȃ�z��p�폜�A�z��ŃG���[���o��ꍇnullptr�̔z��폜�������̋��ꂪ����̂�nullptr�`�F�b�N��p�ӂ���
}

void Cmp_Image::SetImage(int& setGh, int setLen) {
	DelImage(gh, length); //�O�̂��ߍ폜�֐���ʂ�m���ɉ摜����̏�Ԃɂ���
	gh = &setGh;
	length = setLen;
}

Cmp_Image::Cmp_Image(int& setGh, int setLen, Cmp_Transform* setTs, int setUse) :gh(nullptr), length(1), cmp(std::deque<Component*>()), ts(setTs), use(setUse), isSelfTs(false) {
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



	//�g��A��]��K�p�����摜�T�C�Y���o������------------------------------
	Vector3 pos[4] = { Vector3(),Vector3(),Vector3(),Vector3() };
	int originSizeX, originSizeY;
	GetGraphSize(*gh, &originSizeX, &originSizeY);
	float sizeX = originSizeX * ts->ReadScale().GetX();
	float sizeY = originSizeY * ts->ReadScale().GetY();

	//�摜�̒[4�_�ʒu
	float x[] = { -sizeX / 2,sizeX / 2 };
	float y[] = { -sizeY / 2,sizeY / 2 };
	float point[] = { x[0],y[0],x[1],y[0],x[1],y[1],x[0],y[1] }; //����A�E��A�E���A�����摜�T�C�Y
	Quaternion modify = OriginMath::Rad2Quaternion(ts->ReadRotate()); //��]�̃N�H�[�^�j�I����

	for (int i = 0; i < 4; i++) {
		pos[i].SetXYZ(point[i * 2] , point[i * 2 + 1] , 0);
		pos[i] = OriginMath::PointRotationQuaternion(pos[i], modify); //���������N�H�[�^�j�I���Ɋ�Â��ό`
		pos[i] += ts->ReadPos(); //���݈ʒu�����Z���Ďw��ʒu�Ɏ����Ă���
	}
	//----------------------------------------------------------------



	//�`�ʏ���--------------------------------------------------------
	int sub = length > 1 ? sub = gh[use] : sub = *gh; //�z��Ȃ�draw_sub�Y�����̈ʒu�̉摜���g�p
	Vector3 local = ts->ReadPos();
	DrawModiGraph(pos[0].GetX(), pos[0].GetY(), pos[1].GetX(), pos[1].GetY(), pos[2].GetX(), pos[2].GetY(), pos[3].GetX(), pos[3].GetY(), sub, true);
	//----------------------------------------------------------------
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255); //�ǉ��������ŘM����\��������̂ŕ`�ʌ㏉�������Ă���
}

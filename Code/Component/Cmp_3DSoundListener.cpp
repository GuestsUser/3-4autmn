#include "DxLib.h"
#include "Cmp_3DSoundListener.h"

#include "Cmp_Transform.h"
#include "OriginMath.h"

#include "GetKey.h"

Cmp_Transform Cmp_3DSoundListener::ts = Cmp_Transform();
SoundSystemCoordinateData::Type Cmp_3DSoundListener::coordinateType = SoundSystemCoordinateData::Type::twoDimension;

void StateUpdate(Cmp_Transform& ts, const Vector3& front, const Vector3& up) { //�󂯎����transform�ɉ����ă��X�i�[�ɓK�؂ȕ����ƈʒu��ݒ�
	Quaternion q = OriginMath::Rad2Quaternion(ts.ReadRotate()); //�ێ��p�x���N�H�[�^�j�I���ɕϊ�
	Vector3 direction = OriginMath::PointRotationQuaternion(front, q); //�����̒P�ʃx�N�g�����p�x�ɍ��킹�ĕό`

	VECTOR dxPos = VGet(ts.ReadPos().GetX(), ts.ReadPos().GetY(), ts.ReadPos().GetZ()); //Vector��dx���C�u�����`����VECTOR�ɕϊ���������
	VECTOR dxDirection = VGet(direction.GetX(), direction.GetY(), direction.GetZ());
	Set3DSoundListenerPosAndFrontPosAndUpVec(dxPos, VAdd(dxPos, dxDirection), VGet(up.GetX(), up.GetY(), up.GetZ())); //���X�i�[��ݒ�
}

void Cmp_3DSoundListener::SetUp() { StateUpdate(ts, SoundSystemCoordinateData::GetFrontCoordinate(coordinateType), SoundSystemCoordinateData::GetUpCoordinate(coordinateType)); } //���X�i�[�����X�V

void Cmp_3DSoundListener::SetPos(const Vector3& pos) {
	ts.EditPos() = pos; //transform�ֈʒu��ݒ�
	SetUp(); //���X�i�[�����X�V
}
void Cmp_3DSoundListener::SetRotate(const Vector3& rotate) {
	ts.EditRotate() = rotate; //transform�֊p�x��ݒ�
	SetUp(); //���X�i�[�����X�V
}
void Cmp_3DSoundListener::SetCoordinateType(const SoundSystemCoordinateData::Type& set) {
	coordinateType = set; //���W�n�w���ύX����
	SetUp(); //���X�i�[�����X�V
}

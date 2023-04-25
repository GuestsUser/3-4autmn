#include "DxLib.h"
#include "Cmp_3DSoundListener.h"

#include "Cmp_Transform.h"
#include "OriginMath.h"

#include "GetKey.h"

Cmp_Transform Cmp_3DSoundListener::ts = Cmp_Transform();
SoundSystemCoordinateData::Type Cmp_3DSoundListener::coordinateType = SoundSystemCoordinateData::Type::twoDimension;

void StateUpdate(Cmp_Transform& ts, const Vector3& front, const Vector3& up) { //受け取ったtransformに応じてリスナーに適切な方向と位置を設定
	Quaternion q = OriginMath::Rad2Quaternion(ts.ReadRotate()); //保持角度をクォータニオンに変換
	Vector3 direction = OriginMath::PointRotationQuaternion(front, q); //向きの単位ベクトルを角度に合わせて変形

	VECTOR dxPos = VGet(ts.ReadPos().GetX(), ts.ReadPos().GetY(), ts.ReadPos().GetZ()); //Vectorをdxライブラリ形式のVECTORに変換したもの
	VECTOR dxDirection = VGet(direction.GetX(), direction.GetY(), direction.GetZ());
	Set3DSoundListenerPosAndFrontPosAndUpVec(dxPos, VAdd(dxPos, dxDirection), VGet(up.GetX(), up.GetY(), up.GetZ())); //リスナーを設定
}

void Cmp_3DSoundListener::SetUp() { StateUpdate(ts, SoundSystemCoordinateData::GetFrontCoordinate(coordinateType), SoundSystemCoordinateData::GetUpCoordinate(coordinateType)); } //リスナー情報を更新

void Cmp_3DSoundListener::SetPos(const Vector3& pos) {
	ts.EditPos() = pos; //transformへ位置を設定
	SetUp(); //リスナー情報を更新
}
void Cmp_3DSoundListener::SetRotate(const Vector3& rotate) {
	ts.EditRotate() = rotate; //transformへ角度を設定
	SetUp(); //リスナー情報を更新
}
void Cmp_3DSoundListener::SetCoordinateType(const SoundSystemCoordinateData::Type& set) {
	coordinateType = set; //座標系指定を変更する
	SetUp(); //リスナー情報を更新
}

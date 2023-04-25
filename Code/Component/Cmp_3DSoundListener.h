#pragma once
#include "Component.h"
#include "Cmp_Transform.h"
#include "3DSoundSystemCoordinateData.h"

class Cmp_3DSoundListener :public Component { //3d空間上でサウンドを聞き取る位置を設定した物
	static Cmp_Transform ts;
	static SoundSystemCoordinateData::Type coordinateType; //空間設定に使用する座標系を指定する為の変数
public:
	void Update() {}

	static void SetUp(); //最初にこれを呼び出す事で保持する初期情報をリスナーに設定し、このコンポーネントが正常動作するようにする
	static void SetPos(const Vector3& pos); //3d空間上のサウンド聞き取り位置を設定
	static void SetRotate(const Vector3& rotate); //3d空間上でサウンドを聞く為に向いている方向を変更、ラジアン角指定
	static void SetCoordinateType(const SoundSystemCoordinateData::Type& set); //座標系指定を変更する

	static const Cmp_Transform* const ReadTransform() { return &ts; } //3d空間上の位置回転を読み取り専用形式で受け取り
	static Cmp_Transform* EditTransform() { return &ts; } //3d空間上の位置回転を書き換え可能形式で受け取り、これによる編集可能はSetUpを呼ばないと反映されないので使用は非奨励

private:
	//実体精製禁止
	Cmp_3DSoundListener() = delete;
	Cmp_3DSoundListener(Cmp_3DSoundListener&) = delete;
};
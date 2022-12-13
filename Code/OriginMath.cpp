#include "OriginMath.h"
#include "Component/Cmp_Transform.h"
#include <cmath>

double OriginMath::MPI = 3.14159265359; //static変数の数値設定
double OriginMath::Deg2Rad = MPI / 180;
double OriginMath::Rad2Deg = 180 / MPI;

const Vector3 operator*(const Vector3& l, const Vector3& r) { return Vector3(l.GetX() * r.GetX(), l.GetY() * r.GetY(), l.GetZ() * r.GetZ()); }
const Vector3 operator/(const Vector3& l, const Vector3& r) { return Vector3(l.GetX() / r.GetX(), l.GetY() / r.GetY(), l.GetZ() / r.GetZ()); }

Vector3 operator*=(Vector3& l, const Vector3& r) {
	l = l * r;
	return l;
}
Vector3 operator/=(Vector3& l, const Vector3& r) {
	l = l / r;
	return l;
}

Vector3::Vector3(const Quaternion& q) :x(q.ReadAxis().x), y(q.ReadAxis().y), z(q.ReadAxis().z) {}

Vector3 WToImaginaryMul(const float& single, const Vector3& queue) { //実数と虚数部の計算
	Vector3 ans;

	//実数を全ての値が同じベクトルとして内積
	ans.SetX(queue.GetX() * single);
	ans.SetY(queue.GetY() * single);
	ans.SetZ(queue.GetZ() * single);
	return ans;
}
Quaternion ImaginaryMul(const Vector3& q1, const Vector3& q2) { //クォータニオン虚数部計算
	return Quaternion(q1.GetY() * q2.GetZ() - q1.GetZ() * q2.GetY(), q1.GetZ() * q2.GetX() - q1.GetX() * q2.GetZ(), q1.GetX() * q2.GetY() - q1.GetY() * q2.GetX(), -(q1.GetX() * q2.GetX() + q1.GetY() * q2.GetY() + q1.GetZ() * q2.GetZ()));
}

Quaternion OriginMath::QuaternionMul(const Quaternion& ql, const Quaternion& qr) {//クォータニオン積、qlに左辺、qrに右辺
	Vector3 imag1 = WToImaginaryMul(ql.GetW(), qr.ReadAxis());
	Vector3 imag2 = WToImaginaryMul(qr.GetW(), ql.ReadAxis());
	Quaternion imag3 = ImaginaryMul(ql.ReadAxis(), qr.ReadAxis());
	Vector3 imaginary = Vector3(imag1.GetX() + imag2.GetX() + imag3.ReadAxis().GetX(), imag1.GetY() + imag2.GetY() + imag3.ReadAxis().GetY(), imag1.GetZ() + imag2.GetZ() + imag3.ReadAxis().GetZ());

	return Quaternion(imaginary.GetX(), imaginary.GetY(), imaginary.GetZ(), ql.GetW() * qr.GetW() + imag3.GetW());

}
Vector3 OriginMath::PointRotationQuaternion(const Vector3& xyz, const Quaternion& q) { //右手系、qに一切の回転が加わってない状態の中点からをxyzとし、qに回転、xyzに距離を入れると距離を3次元回転してくれる
	Quaternion conj = Quaternion(-q.ReadAxis().GetX(), -q.ReadAxis().GetY(), -q.ReadAxis().GetZ(), q.GetW());//qの共役クォータニオン
	Quaternion xyzw = Quaternion(xyz);
	Quaternion edit = QuaternionMul(q, xyzw);//q*p*q共役  の形
	return Vector3(QuaternionMul(edit, conj)); //EditAxisの参照をそのまま返すと受け取り先で情報が消えてしまうので値渡しの型に直す
}

Quaternion OriginMath::Rad2Quaternion(const Vector3& angle) {
	Quaternion x = Quaternion(sin(angle.GetX() / 2), 0, 0, cos(angle.GetX() / 2));
	Quaternion y = Quaternion(0, sin(angle.GetY() / 2), 0, cos(angle.GetY() / 2));
	Quaternion z = Quaternion(0, 0, sin(angle.GetZ() / 2), cos(angle.GetZ() / 2));

	Quaternion xy = QuaternionMul(x, y);
	return QuaternionMul(xy, z);
}

void OriginMath::VertexModification(Vector3 pos[4], const Vector3& size, const Cmp_Transform& ts, HorizonPivot hp, VerticalPivot vp) {
	float sizeX = size.GetX() * ts.ReadScale().GetX();
	float sizeY = size.GetY() * ts.ReadScale().GetY();

	//頂点作成
	float x[] = { -sizeX / 2 - (sizeX / 2 * (int)hp), sizeX / 2 - (sizeX / 2 * (int)hp) }; //pivotに合わせて画像サイズを変形
	float y[] = { -sizeY / 2 - (sizeY / 2 * (int)vp), sizeY / 2 - (sizeY / 2 * (int)vp) };
	float point[] = { x[0],y[0],x[1],y[0],x[1],y[1],x[0],y[1] }; //左上、右上、右下、左下頂点
	Quaternion modify = OriginMath::Rad2Quaternion(ts.ReadRotate()); //回転のクォータニオン化

	Vector3 local = ts.ReadPos();
	local.SetXYZ(local.GetX() + size.GetX() / 2 * (int)hp, local.GetY() + size.GetY() / 2 * (int)vp, 0);//pivotに合わせて現在座標が表示の中心に来るようxyを調整

	for (int i = 0; i < 4; i++) {
		pos[i].SetXYZ(point[i * 2], point[i * 2 + 1], 0);
		pos[i] = OriginMath::PointRotationQuaternion(pos[i], modify); //距離情報をクォータニオンに基づき変形
		pos[i] += local; //現在位置を加算して指定位置に持ってくる
	}
}


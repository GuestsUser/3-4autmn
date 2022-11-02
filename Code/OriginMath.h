#pragma once
class Quaternion;

class Vector3 { //座標情報を3つ纏めて扱えるようにした物
private:
	float x, y, z;
public:
	Vector3(float gx = 0, float gy = 0, float gz = 0) :x(gx), y(gy), z(gz) {} //初期値を其々設定する形式のコンストラクタ、設定は全て省く事ができる
	Vector3(const Vector3& pos) :x(pos.x), y(pos.y), z(pos.z) {} //コピーコンストラクタ、相手側の数値のアドレスを取ったりせず、値をコピーするのでオーバーフローは問題ない
	Vector3(const Quaternion& q); //クォータニオンからVector3情報を取り出して初期化する事もできる

	float GetX() const { return x; } //xを取得
	float GetY() const { return y; } //yを取得
	float GetZ() const { return z; } //zを取得

	void SetX(float gx) { x = gx; } //xを設定
	void SetY(float gy) { y = gy; } //yを設定
	void SetZ(float gz) { z = gz; } //zを設定
	void SetXYZ(float gx, float gy, float gz) { //個々の数値設定が面倒な場合これで一気に設定
		x = gx;
		y = gy;
		z = gz;
	}

	Vector3 operator=(const Vector3& r) { //constを返り値に付けるとa=b=cの型の時、b=cの返り値がconstとなり、a=const dで、const指定のない本関数が呼べなくなってしまう都合上非const実装
		SetXYZ(r.x, r.y, r.z);
		return *this;
	}

	const Vector3 operator+() const { return *this; }
	const Vector3 operator-() const { return Vector3(-x, -y, -z); } //-Vector3の様に変数の前に-を付けると全ての数値をマイナスにできる

	const Vector3 operator+ (const Vector3& r) const { return Vector3(x + r.x, y + r.y, z + r.z); } //Vector3同士を加算できる
	const Vector3 operator- (const Vector3& r) const { return Vector3(x - r.x, y - r.y, z - r.z); } //Vector3同士の減算ができる

	Vector3 operator+= (const Vector3& r) { //Vector3の加算代入ができる
		(*this) = (*this) + r;
		return *this;
	}
	Vector3 operator-= (const Vector3& r) { //Vector3の減算代入ができる
		(*this) = (*this) - r;
		return *this;
	}
};

const Vector3 operator*(const Vector3& l, const Vector3& r);
template<typename T> const Vector3 operator*(const T& l, const Vector3& r) { return Vector3(l * r.GetX(), l * r.GetY(), l * r.GetZ()); }
template<typename T> const Vector3 operator*(const Vector3& l, const T& r) { return Vector3(l.GetX() * r, l.GetY() * r, l.GetZ() * r); }
const Vector3 operator/(const Vector3& l, const Vector3& r);
template<typename T> const Vector3 operator/(const T& l, const Vector3& r) { return Vector3(l / r.GetX(), l / r.GetY(), l / r.GetZ()); }
template<typename T> const Vector3 operator/(const Vector3& l, const T& r) { return Vector3(l.GetX() / r, l.GetY() / r, l.GetZ() / r); }

Vector3 operator*=(Vector3& l, const Vector3& r);
template<typename T> Vector3 operator*=(Vector3& l, const T& r) {
	l = l * r;
	return l;
}
Vector3 operator/=(Vector3& l, const Vector3& r);
template<typename T> Vector3 operator/=(Vector3& l, const T& r) {
	l = l / r;
	return l;
}

class Quaternion { //xyzにwの情報を加えたクォータニオン、内部的にはVector3とfloat型変数の2つを持つ事で実現
private:
	float w;
	Vector3 axis; //初期化後にインスタンスが消滅したらポインタに置き換え
public:
	Quaternion(float gx = 0, float gy = 0, float gz = 0, float gw = 0) :axis(Vector3(gx, gy, gz)), w(gw) {}
	Quaternion(const Vector3& pos, float gw = 0) :axis(pos), w(gw) {} //xyzをVector3で、qをfloatで初期化できる、qは省ける
	Quaternion(const Quaternion& q) :axis(q.axis), w(q.w) {} //コピーコンストラクタが使える

	float GetW() const { return w; } //wを取得
	const Vector3& ReadAxis() const { return axis; } //Vector3の情報を読み出す

	void SetW(float gw) { w = gw; } //wを設定
	Vector3& EditAxis() { return axis; } //Vector3を書き換え可能な形で取得する
};

class OriginMath { //演算に便利な機能纏め、このクラスの変数などが使用したい場合ファイルをインクルードし、OriginMath::使用したい変数や関数 の形式で使用可能
	OriginMath() {} //実体精製禁止

public:
	static double MPI; //円周率
	static double Deg2Rad; //デグリー角(45とか90とか)からラジアン角(1.27とか3.14)へ変更したい数値にこの値を掛けるとしてくれる
	static double Rad2Deg; //ラジアン角からデグリー角へ変更したい数値にこの値を掛けるとしてくれる

	static Quaternion QuaternionMul(const Quaternion& ql, const Quaternion& qr); //クォータニオン積、qlに左辺、qrに右辺
	static Quaternion Rad2Quaternion(const Vector3& angle); //ラジアン角をクォータニオン化
	static Vector3 PointRotationQuaternion(const Vector3& xyz, const Quaternion& q); //右手系、特定中点からの距離をxyzに、qに回転を入れると、xyzを3次元回転してくれる、xyzの値は回転で変形させてない物を使用する事
};

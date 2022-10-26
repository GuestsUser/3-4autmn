#pragma once
#include "../Code/OriginMath.h"
#include "../Code/Component/Component.h"

class Cmp_Transform :public Component { //詳細な画像描写に必要な情報を纏めた物
private:
	Vector3* xyz; //表示座標、左上(0,0)で管理
	Vector3* scale; //拡大率
	Vector3* rotate; //回転、0～2PIのラジアン角で管理
public:
	Cmp_Transform() :xyz(new Vector3()), scale(new Vector3(1, 1, 1)), rotate(new Vector3()) {}
	Cmp_Transform(const Cmp_Transform& cmp) :xyz(new Vector3(cmp.ReadPos())), scale(new Vector3(cmp.ReadScale())), rotate(new Vector3(cmp.ReadRotate())) {} //コピーコンストラクタ

	~Cmp_Transform() {
		delete xyz;
		delete scale;
		delete rotate;
	}

	void Update() {} //データ的な意味合いのコンポーネントなので何もしない
	void Draw() {} //Update同様何もしない

	const Vector3& ReadPos() const { return *xyz; } //位置の情報を読み取り
	const Vector3& ReadScale() const { return *scale; } //拡大率の情報を読み取り
	const Vector3& ReadRotate() const { return *rotate; } //回転の情報を読み取り

	Vector3& EditPos() { return *xyz; } //位置の情報を編集可能な状態で返す
	Vector3& EditScale() { return *scale; } //拡大率の情報を編集可能な状態で返す
	Vector3& EditRotate() { return *rotate; } //回転の情報を編集可能な状態で返す
};
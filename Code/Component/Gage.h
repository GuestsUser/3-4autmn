#pragma once
#include "Component.h"
#include "Cmp_Transform.h"

#include <deque>
#include <typeinfo>

class Cmp_Image;

class Gage :public Component {
	Cmp_Image* base; //ゲージのベース、空のゲージ画像
	Cmp_Image* full; //ゲージの実体表示用画像

	int vol; //ゲージの現在量、これを基にゲージを表示する、100が最大、0最小の表現、小数点は上手く保持できない可能性があったのでこの形を採用
	float iniSize; //ゲージ実体画像の初期x拡大率、これに対しvolを掛けて現在ゲージ伸縮を求める事でゲージの最大値を伸ばしたい等の際、予め画像を拡大してfullに渡す事でゲージ最大サイズを画像を作り直さず再設定できる

	std::deque<Component*> cmp; //追加機能
public:
	Gage(Cmp_Image& baseImgae, Cmp_Image& fullImage, int iniVol = 100);
	~Gage();

	void Reset();
	void FullReset();

	void Update();
	void Draw();

	float GetVol() const { return vol * 0.01; } //パーセンテージ形式に直して返す
	void SetVol(float set) { //値を設定、パーセンテージで受け取るので*100で整数に直す
		if (set > 1) { set = 1; } //リミットチェック、マイナス、若しくは100を超えないようにする
		if (set < 0) { set = 0; }
		vol = set * 100;
	}

	const Cmp_Image* ReadBaseGage() const { return base; } //空ゲージの画像オブジェクトを取得、読み取り専用
	const Cmp_Image* ReadFullGage() const { return full; } //ゲージ実体の画像オブジェクトを取得、読み取り専用

	float GetIniSize() { return iniSize; } //初期x拡大率を取得

	void SetCmp(Component* set) { cmp.push_back(set); } //追加機能の追加

	template<class T> T* EditCmp() const { //コンポーネント取得
		const type_info& master = typeid(T); //取得するコンポーネントの型を入れておく
		for (Component* get : cmp) {
			if (typeid(*get) == master) { return dynamic_cast<T*>(get); }
		}
		return nullptr;
	}
};
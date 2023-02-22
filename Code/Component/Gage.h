#pragma once
#include "Component.h"
#include "Cmp_Transform.h"
#include "../Code/Component/ComponentArray.h"

#include <deque>
#include <typeinfo>

class Cmp_Image;

class Gage :public Component {
	Cmp_Image* base; //ゲージのベース、空のゲージ画像
	Cmp_Image* full; //ゲージの実体表示用画像

	float vol; //ゲージの現在量
	float iniSize; //ゲージ実体画像の初期x拡大率、これに対しvolを掛けて現在ゲージ伸縮を求める事でゲージの最大値を伸ばしたい等の際、予め画像を拡大してfullに渡す事でゲージ最大サイズを画像を作り直さず再設定できる

	ComponentArray cmp; //追加機能
public:
	Gage(Cmp_Image& baseImgae, Cmp_Image& fullImage, int iniVol = 1);
	~Gage();

	void Reset();
	void FullReset();

	void Update();
	void Draw();

	float GetVol() const { return vol; }
	void SetVol(float set) { //値を設定
		if (set > 1) { set = 1; } //リミットチェック、マイナス、若しくは1を超えないようにする
		if (set < 0) { set = 0; }
		vol = set;
	}

	const Cmp_Image* ReadBaseGage() const { return base; } //空ゲージの画像オブジェクトを取得、読み取り専用
	const Cmp_Image* ReadFullGage() const { return full; } //ゲージ実体の画像オブジェクトを取得、読み取り専用

	float GetIniSize() { return iniSize; } //初期x拡大率を取得

	ComponentArray* EditAppendCmp() { return &cmp; } //追加機能集へのアクセスを渡す
	const ComponentArray* const ReadAppendCmp() { return &cmp; } //追加機能集へのアクセス、こちらは読み出し専用
};
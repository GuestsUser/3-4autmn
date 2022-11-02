#include "DxLib.h"

#include "Cmp_Image.h"
#include "Component.h"
#include "Cmp_Transform.h"
#include "../OriginMath.h"

#include <deque>

void DelImage(int* gh, int len) { //画像の削除、外部公開したくなかったからこちらに記す
	if (len == 1) { delete gh; } //要素が一つなら単体用削除
	else { delete[] gh; } //複数なら配列用削除、配列でエラーが出る場合nullptrの配列削除が原因の恐れがあるのでnullptrチェックを用意する
}

void Cmp_Image::SetImage(int& setGh, int setLen) {
	DelImage(gh, length); //念のため削除関数を通り確実に画像が空の状態にする
	gh = &setGh;
	length = setLen;
}

Cmp_Image::Cmp_Image(int& setGh, int setLen, Cmp_Transform* setTs, int setUse) :gh(nullptr), length(1), cmp(std::deque<Component*>()), ts(setTs), use(setUse), isSelfTs(false) {
	SetImage(setGh, setLen); 
	if (setTs == nullptr) { ts = new Cmp_Transform(); isSelfTs = true; } //Transformを受け取らなかった場合
}

Cmp_Image::~Cmp_Image() {
	DelImage(gh, length);
	for (Component* get : cmp) { delete get; } //格納されてたコンポーネントの削除
	if (isSelfTs) { delete ts; } //Transform自己管理だった場合削除しておく
}

void Cmp_Image::Update() {
	if (!GetRunUpdate()) { return; } //falseの場合実行しない
	for (Component* get : cmp) { get->Update(); }
}



void Cmp_Image::Draw() {
	if (!GetRunDraw()) { return; } //falseの場合実行しない
	for (Component* get : cmp) { get->Draw(); }



	//拡大、回転を適用した画像サイズを出す処理------------------------------
	Vector3 pos[4] = { Vector3(),Vector3(),Vector3(),Vector3() };
	int originSizeX, originSizeY;
	GetGraphSize(*gh, &originSizeX, &originSizeY);
	float sizeX = originSizeX * ts->ReadScale().GetX();
	float sizeY = originSizeY * ts->ReadScale().GetY();

	//画像の端4点位置
	float x[] = { -sizeX / 2,sizeX / 2 };
	float y[] = { -sizeY / 2,sizeY / 2 };
	float point[] = { x[0],y[0],x[1],y[0],x[1],y[1],x[0],y[1] }; //左上、右上、右下、左下画像サイズ
	Quaternion modify = OriginMath::Rad2Quaternion(ts->ReadRotate()); //回転のクォータニオン化

	for (int i = 0; i < 4; i++) {
		pos[i].SetXYZ(point[i * 2] , point[i * 2 + 1] , 0);
		pos[i] = OriginMath::PointRotationQuaternion(pos[i], modify); //距離情報をクォータニオンに基づき変形
		pos[i] += ts->ReadPos(); //現在位置を加算して指定位置に持ってくる
	}
	//----------------------------------------------------------------



	//描写処理--------------------------------------------------------
	int sub = length > 1 ? sub = gh[use] : sub = *gh; //配列ならdraw_sub添え字の位置の画像を使用
	Vector3 local = ts->ReadPos();
	DrawModiGraph(pos[0].GetX(), pos[0].GetY(), pos[1].GetX(), pos[1].GetY(), pos[2].GetX(), pos[2].GetY(), pos[3].GetX(), pos[3].GetY(), sub, true);
	//----------------------------------------------------------------
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255); //追加処理等で弄られる可能性があるので描写後初期化しておく
}

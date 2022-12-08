#include "DxLib.h"

#include "Cmp_Image.h"
#include "Component.h"
#include "Cmp_Transform.h"
#include "../OriginMath.h"

#include <deque>

void DelImage(int* gh, int len) { //画像の削除、外部公開したくなかったからこちらに記す
	if (gh == nullptr) { return; } //空なら何もしない
	if (len == 1) { DeleteGraph(*gh); delete gh; return; } //要素が一つなら単体用削除
	for (int i = 0; i < len; ++i) { DeleteGraph(gh[i]); } //配列解放
	delete[] gh; //複数なら配列用削除
}

void Cmp_Image::SetImage(int& setGh, int setLen) {
	DelImage(gh, length); //念のため削除関数を通り確実に画像が空の状態にする
	gh = &setGh;
	length = setLen;
}

Cmp_Image::Cmp_Image(int& setGh, int setLen, Cmp_Transform* setTs, int setUse) :gh(nullptr), length(1), cmp(std::deque<Component*>()), ts(setTs), use(setUse), isSelfTs(false), drawPivotHorizon(OriginMath::HorizonPivot::center), drawPivotVertical(OriginMath::VerticalPivot::center) {
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

	Vector3 pos[4]; //拡縮回転変形頂点保持用Vector3
	int* sizeX = nullptr; //画像サイズ格納要
	int* sizeY = nullptr;
	int sub = length > 1 ? sub = gh[use] : sub = *gh; //配列ならdraw_sub添え字の位置の画像を使用

	GetGraphSize(sub, sizeX, sizeY); //サイズ取得
	OriginMath::VertexModification(pos, Vector3(*sizeX, *sizeY), *ts, drawPivotHorizon, drawPivotVertical); //回転、拡大を適用した頂点座標を格納

	DrawModiGraph(pos[0].GetX(), pos[0].GetY(), pos[1].GetX(), pos[1].GetY(), pos[2].GetX(), pos[2].GetY(), pos[3].GetX(), pos[3].GetY(), sub, true); //描写
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255); //追加処理等で弄られる可能性があるので描写後初期化しておく
}


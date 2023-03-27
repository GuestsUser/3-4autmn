#pragma once
#include "Component.h"
#include "ComponentArray.h"
#include <deque>

class Cmp_Image;
class Cmp_Transform;

class PK_Card :public Component { //カードに必要な変数群を纏めたクラス
public:
	enum class DrawMode { back, front, fold }; //表示モード、backは背面表示、frontは表側表示、foldはfold用の灰色表示

private:
	Cmp_Image* image; //カード画像
	Cmp_Image* markingImage; //マーキング用画像
	int card; //カード画像から目的の画像を取り出す添え字変数
	DrawMode drawMode; //表示モード格納変数

	ComponentArray cmp;
public:
	PK_Card();
	~PK_Card();

	void Reset(); //新しいラウンドを開始する時呼び出す、見た目を初期状態(マーキングなし、裏側表示)に戻す
	void FullReset() { Reset(); } //Resetと内容は同じ

	void Place(int x, int y); //カードを配置する

	const Cmp_Transform* ReadTransform() const; //座標系情報を読み取り専用形式で取得
	Cmp_Transform* EditTransform(); //座標系情報を編集可能な状態で取得

	void Update();
	void Draw();

	int GetCard() const { return card; } //imageで使用するカード添え字を返す

	void SetCard(int number) { card = number; } //imageで使用する添え字を渡してカードの強さと種類を設定する
	void SetMarking(bool set); //trueでカードにマーキングを表示

	void SetDrawMode(DrawMode set) { drawMode = set; } //表示形式の設定


	ComponentArray* EditAppendCmp() { return &cmp; } //追加機能集へのアクセスを渡す
	const ComponentArray* const ReadAppendCmp() { return &cmp; } //追加機能集へのアクセス、こちらは読み出し専用
};
#pragma once
#include "../Code/Component/Component.h"
#include <deque>

class Cmp_Image;
class Cmp_Transform;

class PK_Card :public Component { //カードに必要な変数群を纏めたクラス
	Cmp_Image* image; //カード画像
	Cmp_Image* markingImage; //マーキング用画像
	int card; //カード画像から目的の画像を取り出す添え字変数

	std::deque<Component*> cmp;
public:
	PK_Card();
	~PK_Card();

	void Reset(); //新しいラウンドを開始する時呼び出す、見た目を初期状態(マーキングなし、裏側表示)に戻す
	void Place(int x, int y); //カードを配置する

	const Cmp_Transform* ReadTransform() const; //座標系情報を読み取り専用形式で取得

	void Update() {}
	void Draw();

	int GetCard() const { return card; } //imageで使用するカード添え字を返す

	void SetCard(int number) { card = number; } //imageで使用する添え字を渡してカードの強さと種類を設定する
	void SetVisible(bool set); //falseだと画面上では裏返しで表示される、trueでカードが分かる表で表示
	void SetMarking(bool set); //trueでカードにマーキングを表示

	void SetCmp(Component* set) { cmp.push_back(set); } //追加機能の追加
	template<class T> T* EditCmp() const { //コンポーネント取得
		const type_info& master = typeid(T); //取得するコンポーネントの型を入れておく
		for (Component* get : cmp) {
			if (typeid(*get) == master) { return dynamic_cast<T*>(get); }
		}
		return nullptr;
	}
};
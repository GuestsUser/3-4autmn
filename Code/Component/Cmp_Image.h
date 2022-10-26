#pragma once
#include "Component.h"
#include <deque>

class Cmp_Transform;

class Cmp_Image :public Component { //Drawを呼び出す事で画像描写を行う、指定座標に画像中央を持って行き、拡大率や回転に応じて変形描写する

	int* gh; //グラフィックハンドル、受け取った物を保持するだけ
	int length; //グラフィックハンドルの要素数、動的配列じゃないので一緒に受け取る必要あり
	int use; //配列グラフィックの場合どの要素を描写に使うか指定する変数
	bool isSelfTs; //Transformコンポーネントをコンストラクタで省いた場合これをtrueにしてTransformの削除等はこちらで行う

	Cmp_Transform* ts; //描写位置や回転、拡大率の参照
	std::deque<Component*> cmp; //画像描写に際してやっておきたい追加処理等あればこちらに追加

public:
	Cmp_Image(int& setGh, int setLen, Cmp_Transform* setTs = nullptr, int setUse = 0); //そちらで行ったら画像読み込みのハンドルを受け取る形で動作する、序に対応するTransformも入れる
	~Cmp_Image(); //削除する際は同時に管理画像も削除する、追加処理を入れたcmpの削除も行う

	void Update(); //Imageに追加したコンポーネントのUpdateを実行する
	void Draw(); //Imageに追加したコンポーネントのDrawを実行する、追加コンポーネントのDrawはImageの描写処理を行う前に行われる


	void SetImage(int& setGh, int setLen); //ハンドルとサイズを受け取る、要素が1つなら*(new int(ハンドル))、配列ならハンドル受け取りに使った変数の先頭に*を付けて渡す、要素が1でもsetLenには1を入れる、画像アドレスへの参照を渡したら後はこちらで削除等の管理を行う、画像が既に入っていた場合元の画像は削除する

	const Cmp_Transform* ReadTranform() const { return ts; } //読み取り専用形式でTransformを取得
	Cmp_Transform* EditTranform() { return ts; } //書き換え可能な形式でTransformを取得
	const int GetAnimesub() const { return use; } //画像描写に使用する添え字を取得
	void SetAnimeSub(int set) { use = set; } //画像描写に使用する添え字を設定
};

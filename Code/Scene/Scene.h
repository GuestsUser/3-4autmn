#pragma once

class Scene { //このクラスを継承してシーン処理をUpdateに、描写処理をDrawに定義する
	Scene* next; //シーン遷移する場合次シーン実体、そのままの場合自身、ウィンドウを閉じる場合nullptrが入る
public:
	Scene() :next(this) {} //初期化時に自身を入れておく
	virtual ~Scene() {} //継承可能なクラスはデストラクタに仮想関数指定がないと親クラスのデストラクタしか呼び出されないのでvirtual指定をしている
	
	virtual void Update() = 0; //毎フレーム実行する処理関数、実装必須
	virtual void Draw() {} //毎フレーム実行する描写関数

	bool SetNext(Scene* set){ //シーンチェンジ用、引数に次シーンの実体を入れる
		if (next != this) { return false; } //既に次シーンの指定がなされている場合失敗
		next = set; //次シーンを設定
		return true; //成功を返す
	}
	Scene* GetNext() { return next; } //次シーンの取得
};
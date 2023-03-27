#pragma once

class Component { //これを継承したクラスにオブジェクトへの追加機能などを書くと汎用性の高いプログラムにできる
private:
	bool isUpdate; //trueでUpdateを実行
	bool isDraw; //trueでDrawを実行

public:
	Component() :isUpdate(true), isDraw(true) {}
	virtual ~Component() {  }

	virtual void Update() = 0;
	virtual void Draw() {}

	virtual void FullReset() {} //コンポーネントを初期化せずゲームを再スタートする際に使用するリセット
	virtual void Reset() {} //ゲームの1ピリオドが終了した時、次に移行する為実行するリセット

	bool GetRunUpdate() const { return isUpdate; }
	bool GetRunDraw() const { return isDraw; }

	void SetRunUpdate(bool set) { isUpdate = set; }
	void SetRunDraw(bool set) { isDraw = set; }
	
};
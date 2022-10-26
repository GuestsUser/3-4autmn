#pragma once

class Component { //これを継承したクラスにオブジェクトへの追加機能などを書くと汎用性の高いプログラムにできる
private:
	bool isUpdate; //trueでUpdateを実行
	bool isDraw; //trueでDrawを実行
public:
	Component() :isUpdate(true), isDraw(true) {}
	virtual ~Component() = 0;

	virtual void Update() = 0;
	virtual void Draw() {}

	bool GetRunUpdate() { return isUpdate; }
	bool GetRunDraw() { return isDraw; }

	void SetRunUpdate(bool set) { isUpdate = set; }
	void SetRunDraw(bool set) { isDraw = set; }
};
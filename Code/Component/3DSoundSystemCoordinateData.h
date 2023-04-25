#pragma once
#include "OriginMath.h"

#include <unordered_map>

class SoundSystemCoordinateData { //3dサウンドのリスナーに設定する座標系情報を纏めたクラス
public:
	enum class Type { twoDimension, threeDimension }; //座標タイプを指定する為の列挙型

private:
	//実体精製禁止
	SoundSystemCoordinateData() = delete;
	SoundSystemCoordinateData(const SoundSystemCoordinateData&) = delete;

	static std::unordered_map<Type, Vector3> front; //角度(0,0,0)の時何処を向いているかを正規化された数値で表す
	static std::unordered_map<Type, Vector3> up; //3d空間上での上方向、2dでいう所の奥方向を正規化された数値で表す

public:
	static void SetUp(); //変数の初期化を行い使用可能にする、複数回呼び出しても意味はないが問題ない

	static Vector3 GetFrontCoordinate(Type sub) { return front[sub]; } //subで指定されたfrontデータを取得
	static Vector3 GetUpCoordinate(Type sub) { return up[sub]; } //subで指定されたupデータを取得
};
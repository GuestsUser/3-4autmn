#pragma once
#include "Component.h"
#include "OriginMath.h"

#include <string>



class Title_Select_Explain_PageScrollExplain :public Component { //ページスクロールが可能である事を表示する為の追加機能
	std::string str; //表示メッセージ
	Vector3 pos; //表示位置
	Vector3 iniColor; //メッセージの初期色
	Vector3 finalColor; //メッセージの最終色

	int count; //時間経過記録
	int limit; //メッセージがiniColor→finalColor→iniColorと1ループするまでの時間、フレーム単位指定
public:
	Title_Select_Explain_PageScrollExplain();

	void Update(); //countを経過させる
	void Draw(); //メッセージ描写を行う

	void FullReset() { Reset(); }
	void Reset(); //時間の開始位置をランダム化する
};
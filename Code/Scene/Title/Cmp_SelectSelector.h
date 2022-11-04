#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Scene/Scene.h"

#include <deque>

class Button;

class Cmp_SelectSelector :public Component { //セレクト画面でゲームをセレクトした時、ゲームの説明へ処理を飛ばす為のButton用追加機能
	int count; //Updateが実行されてからのカウント
	int limit; //countがこの値になったら実行シーンを交換する

	Scene** gameRef; //実際に実行を行っているシーンを格納する変更の参照(これで上手く動くか、若しくはScene*型でもいいのかテストしたい)
	Scene* run; //クリックされたら実行する説明シーン
	std::deque<Button*> group; //ボタングループ、基本的にボタンの集まりはSceneに属してるのでこちらでは削除管理を行わない

public:
	Cmp_SelectSelector(Scene* set, Scene** ref, std::deque<Button*>& setArray, int setLimit = 30) :run(set), gameRef(ref), group(setArray), count(0),limit(setLimit) { }

	void Update();

	const int GetRunTiming() const { return limit; } //シーンを移し替える処理を実行するタイミングを返す関数
};
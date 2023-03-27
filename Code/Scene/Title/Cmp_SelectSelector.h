#pragma once
#include "../Code/Component/Component.h"

#include <deque>
#include <functional>

class Scene;
class Button;

class Cmp_SelectSelector :public Component { //ボタンをクリックした時、gameRefにrunを入れる又はsceneCreatorで新たなシーンを作りgameRefへセットするButton用追加機能
	int count; //Updateが実行されてからのカウント
	int limit; //countがこの値になったら実行シーンを交換する

	Scene** gameRef; //実際に実行を行っているシーンを格納する変数の参照
	Scene* run; //クリックされたら実行する説明シーン
	std::function<Scene* ()> sceneCreator; //実行ゲームシーンを作成する関数ポインタ
public:
	Cmp_SelectSelector(Scene* set, Scene** ref, int setLimit = 30) :run(set), sceneCreator(nullptr), gameRef(ref), count(0), limit(setLimit) { }
	Cmp_SelectSelector(std::function<Scene* ()> sceneCreator, Scene** ref, int setLimit = 30) :run(nullptr), sceneCreator(sceneCreator), gameRef(ref), count(0), limit(setLimit) { }

	void Update();
	void Reset() { count = 0; } //再利用できるようcountを0に戻す
	void FullReset() { Reset(); } //Resetと同様

	const int GetRunTiming() const { return limit; } //シーンを移し替える処理を実行するタイミングを返す関数
};
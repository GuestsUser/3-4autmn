#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Scene/Scene.h"

class Cmp_SelectSelector :public Component {
	int count; //Updateが実行されてからのカウント
	int limit; //countがこの値になったら実行シーンを交換する

	Scene** gameRef; //実際に実行を行っているシーンを格納する変更の参照(これで上手く動くか、若しくはScene*型でもいいのかテストしたい)
	Scene* run; //クリックされたら実行する説明シーン

public:
	Cmp_SelectSelector(Scene* set, Scene** ref, int setLimit = 30) :run(set), gameRef(ref), count(0),limit(setLimit) { }
	~Cmp_SelectSelector();

	void Update();
};
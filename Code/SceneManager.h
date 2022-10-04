#pragma once
class Scene;

class SceneManager { //シーン管理用クラス、メインに一つ作ってUpdateとDrawを呼び出す事で使用する
	Scene* run; //実行するシーン実体が入っている
public:
	SceneManager(Scene* ini) :run(ini) {} //最初に読み込みたいシーンのインスタンスを引数に入れる
	//~SceneManager();

	bool Update(); //実行するシーンの処理を実行する、ウィンドウを閉じる場合返り値がfalseになる
	void Draw(); //実行シーンの描写を行う
};
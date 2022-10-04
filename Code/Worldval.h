#pragma once
#include <unordered_map>
#include <string>

//シーンを跨いだ値保持クラス
//実体はprivate変数でstaticとして確保しているので名前空間解決演算子からアクセスする
//WorldVal::Set("test",new int(4)); こんな感じ、new intの方の型は好きな型が使える
//int get=WorldVal::Get<int>("test"); こんな風に取り出す、<int>の部分は取り出す型に合わせて変える
//WorldVal::Del("test"); これで"test"の値を削除できる
class WorldVal {
	static std::unordered_map<std::string, void*>* gloval; //Setで受け取ったkeyのコピーをキーとしてない場合キーが消滅する恐れあり
public:
	static void SetUp() { if (gloval == nullptr) { gloval = new std::unordered_map<std::string, void*>(); } } //値を保持する内部変数が空だった場合精製
	static void Destruct(); //ウィンドウを閉じる時、全消去のつもりで呼び出す

	template<class T> static T* Get(const std::string& key) {
		auto itr = gloval->find<std::string>(key);
		if (itr != gloval->end()) { return static_cast<T*>(itr->second); } //要素が見つかった場合目標の型にキャストして返す
		return nullptr; //見つからなかったらnullptrで返す
	}
	static void Set(const std::string& key, void* date) { (*gloval)[key] = date; } 
	static void Del(const std::string& key) {
		auto itr=gloval->find<std::string>(key);
		if (itr != gloval->end()) { //要素が見つかった場合だけ消す 
			delete itr->second; //void*のデストラクタを呼び出す
			gloval->erase(itr); //要素を削除する
		}
	}

	//実体精製禁止
	WorldVal() = delete;
	WorldVal(const WorldVal&) = delete;
};
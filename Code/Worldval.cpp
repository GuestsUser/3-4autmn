#include "Worldval.h"
#include <unordered_map>
#include <string>

std::unordered_map<std::string, void*>* WorldVal::gloval = nullptr; //static変数定義

void WorldVal::Destruct() {
	for (auto itr : *gloval) { delete itr.second; } //保持する全てのvoid*を削除
	gloval->clear(); //配列を空に
	delete gloval; //消す
}
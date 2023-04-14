#pragma once
#include "Cmp_PK_Pause.h"
#include <deque>

class Button;
class Cmp_Image;


class Cmp_PK_Pause::DataSetting {
public:
	static void BackPlace(Cmp_Image& back); //背景を正しい位置へ配置する
	static void ButtonNameImageSet(std::deque<Button*>& button); //ボタンに表示される名前を設定する
	static void ButtonAppendCmpSet(Cmp_PK_Pause& pause, std::deque<Button*>& button); //各ボタンの押された時の機能を設定

private:
	//実体精製禁止
	DataSetting() = delete;
	DataSetting(const DataSetting&) = delete;
};
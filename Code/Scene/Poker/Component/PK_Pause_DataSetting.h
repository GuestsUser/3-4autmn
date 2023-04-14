#pragma once
#include "Cmp_PK_Pause.h"
#include <deque>

class Button;
class Cmp_Image;


class Cmp_PK_Pause::DataSetting {
public:
	static void BackPlace(Cmp_Image& back); //�w�i�𐳂����ʒu�֔z�u����
	static void ButtonNameImageSet(std::deque<Button*>& button); //�{�^���ɕ\������閼�O��ݒ肷��
	static void ButtonAppendCmpSet(Cmp_PK_Pause& pause, std::deque<Button*>& button); //�e�{�^���̉����ꂽ���̋@�\��ݒ�

private:
	//���̐����֎~
	DataSetting() = delete;
	DataSetting(const DataSetting&) = delete;
};
#pragma once
#include "CPU.h"
#include "../Code/Component/Component.h"

class CPU::DataPlace {
public:
	static void Run(CPU& parent, int sub); //parent��sub�ɉ������ʒu�֔z�u����

	//���̐����֎~
	DataPlace() = delete;
	DataPlace(const DataPlace&) = delete;
};
#pragma once
#include "PK_CPU.h"
#include "Component.h"

class PK_CPU::DataPlace {
public:
	static void Run(PK_CPU& parent, int sub); //parent��sub�ɉ������ʒu�֔z�u����

private:
	//���̐����֎~
	DataPlace() = delete;
	DataPlace(const DataPlace&) = delete;
};
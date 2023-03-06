#pragma once
#include "CPU.h"
#include "../Code/Component/Component.h"

class CPU::DataPlace {
public:
	static void Run(CPU& parent, int sub); //parent‚ğsub‚É‰‚¶‚½ˆÊ’u‚Ö”z’u‚·‚é

	//À‘Ì¸»‹Ö~
	DataPlace() = delete;
	DataPlace(const DataPlace&) = delete;
};
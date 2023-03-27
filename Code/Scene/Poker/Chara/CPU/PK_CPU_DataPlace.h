#pragma once
#include "PK_CPU.h"
#include "Component.h"

class PK_CPU::DataPlace {
public:
	static void Run(PK_CPU& parent, int sub); //parent‚ğsub‚É‰‚¶‚½ˆÊ’u‚Ö”z’u‚·‚é

	//À‘Ì¸»‹Ö~
	DataPlace() = delete;
	DataPlace(const DataPlace&) = delete;
};
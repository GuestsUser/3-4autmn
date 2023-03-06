#pragma once
#include "CPU.h"
#include "../Code/Component/Component.h"

class CPU::DataPlace {
public:
	static void Run(CPU& parent, int sub); //parentをsubに応じた位置へ配置する

	//実体精製禁止
	DataPlace() = delete;
	DataPlace(const DataPlace&) = delete;
};
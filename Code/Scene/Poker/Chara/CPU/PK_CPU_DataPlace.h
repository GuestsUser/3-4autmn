#pragma once
#include "PK_CPU.h"
#include "Component.h"

class PK_CPU::DataPlace {
public:
	static void Run(PK_CPU& parent, int sub); //parentをsubに応じた位置へ配置する

	//実体精製禁止
	DataPlace() = delete;
	DataPlace(const DataPlace&) = delete;
};
#pragma once
#include "./../Scene.h"

class SR_Result : public Scene{ 
private:
	int Result;
public:
	SR_Result();
	void Update();
	void Draw();
};

#include "Cmp_SelectSelector.h"
#include "../Code/Scene/Scene.h"

void Cmp_SelectSelector::Update() {
	if (count > limit) {
		*gameRef = run; 
		count = 0;

		SetRunUpdate(false);
		SetRunDraw(false);
		return;
	}
	++count;
}

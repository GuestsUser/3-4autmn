#include "Worldval.h"
#include <unordered_map>
#include <string>

std::unordered_map<std::string, void*>* WorldVal::gloval = nullptr; //static•Ï”’è‹`

void WorldVal::Destruct() {
	for (auto itr : *gloval) { delete itr.second; } //•Û‚·‚é‘S‚Ä‚Ìvoid*‚ğíœ
	gloval->clear(); //”z—ñ‚ğ‹ó‚É
	delete gloval; //Á‚·
}
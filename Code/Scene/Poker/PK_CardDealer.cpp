#include "PK_CardDealer.h"
#include "PK_Card.h"

#include <deque>
#include <numeric>
#include <random>

PK_CardDealer::PK_CardDealer() :deck(std::deque<int>(52)), gen(std::mt19937()), top(0) { gen.seed((std::random_device())()); }

void PK_CardDealer::Reset() {
	top = 0; //RD‚Ìã‚ğ0‚É–ß‚·
	std::iota(deck.begin(), deck.end(), 0); //0`52‚Ì’l‚ğŠe—v‘f‚ÉŠi”[
	std::shuffle(deck.begin(), deck.end(), gen); //‘ã“ü‚³‚ê‚Ä‚¢‚é’l‚ğƒ‰ƒ“ƒ_ƒ€ŒğŠ·
}

int PK_CardDealer::DeckDraw() {
	++top; //RD‚ğˆø‚­‚Ì‚Å1‚Â‘‚â‚µ‚ÄŸ‚Ì“Y‚¦š‚Ö
	return deck[top - 1]; //¡‰ñ‚ÌRD‚Ì”’l‚ğ•Ô‚·
}





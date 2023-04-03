#include "PK_CardDealer.h"
#include "PK_Card.h"

#include <deque>
#include <numeric>
#include <random>

PK_CardDealer::PK_CardDealer() :deck(std::deque<int>(52)), gen(std::mt19937()), top(0) { gen.seed((std::random_device())()); }

void PK_CardDealer::Reset() {
	top = 0; //�R�D�̏��0�ɖ߂�
	std::iota(deck.begin(), deck.end(), 0); //0�`52�̒l���e�v�f�Ɋi�[
	std::shuffle(deck.begin(), deck.end(), gen); //�������Ă���l�������_������
}

int PK_CardDealer::DeckDraw() {
	++top; //�R�D�������̂�1���₵�Ď��̓Y������
	return deck[top - 1]; //����̎R�D�̐��l��Ԃ�
}





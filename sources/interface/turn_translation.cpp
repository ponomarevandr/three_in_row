#include "turn_translation.h"

#include "graphics/players.h"


namespace Interface {

std::pair<size_t, uint8_t> turnToUser(size_t index) {
	return std::make_pair(index / 3, static_cast<uint8_t>(index % 3 + 1));
}

size_t turnToProgram(size_t index_whole, uint8_t player) {
	return index_whole * 3 + player - 1;
}

std::wstring turnToString(size_t index) {
	std::pair<size_t, uint8_t> turn = turnToUser(index);
	return std::to_wstring(turn.first + 1) + Graphics::player_symbols[turn.second];
}

}
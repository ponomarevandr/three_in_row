#include "turn_translation.h"

#include "graphics/players.h"


namespace Interface {

std::pair<size_t, uint8_t> turnToUser(size_t index) {
	if (index == 0)
		return std::make_pair(0, 0);
	return std::make_pair((index + 2) / 3, static_cast<uint8_t>((index + 2) % 3 + 1));
}

size_t turnToProgram(size_t index_whole, uint8_t player) {
	if (index_whole == 0)
		return 0;
	return index_whole * 3 - 2 + player - 1;
}

std::wstring turnToString(size_t index) {
	std::pair<size_t, uint8_t> turn = turnToUser(index);
	if (turn.first == 0)
		return L"0";
	return std::to_wstring(turn.first) + Graphics::player_symbols[turn.second];
}

}
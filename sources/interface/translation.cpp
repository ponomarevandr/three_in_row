#include "translation.h"


namespace Interface {

std::pair<size_t, size_t> turnToUser(size_t index) {
	if (index == 0)
		return std::make_pair(0, 0);
	return std::make_pair((index + 2) / 3, (index + 2) % 3);
}

size_t turnToProgram(size_t whole, size_t third) {
	if (whole == 0)
		return 0;
	return whole * 3 - 2 + third;
}

std::wstring turnToString(size_t index) {
	std::pair<size_t, size_t> turn = turnToUser(index);
	if (turn.second == 0)
		return std::to_wstring(turn.first);
	return std::to_wstring(turn.first) + L" " + std::to_wstring(turn.second) + L"/3";
}

}
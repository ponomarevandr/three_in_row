#include "player_functions.h"

#include <array>


namespace ThreeInRow {

uint8_t playerNext(uint8_t player) {
	return static_cast<uint8_t>(player + 1) & (
		static_cast<uint8_t>(0) - static_cast<uint8_t>(player < 2)
	);
}

uint8_t whoseTurn(const Position& position) {
	std::array<size_t, 3> count = { 0, 0, 0 };
	for (size_t i = 0; i < position.getWidth(); ++i) {
		for (size_t j = 0; j < position.getHeight(); ++j) {
			uint8_t value = position.getCell(i, j);
			if (value < 3)
				++count[value];
		}
	}
	if (count[2] < count[1])
		return 2;
	if (count[1] < count[0])
		return 1;
	return 0;
}

}
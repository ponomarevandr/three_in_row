#pragma once

#include <inttypes.h>
#include <vector>


namespace Game {

class Position {
private:
	size_t height = 0;
	size_t width = 0;
	std::vector<uint64_t> field;
	size_t scores[3];

public:
	Position() = default;
	Position(size_t height, size_t width);
	Position(size_t height, size_t width, std::vector<uint64_t>&& field);
	size_t getHeight() const;
	size_t getWidth() const;
	uint8_t getCell(size_t row, size_t column) const;
	void setCell(size_t row, size_t column, uint8_t value);
	bool isTurnPossible(size_t column) const;
	void makeTurn(size_t column, uint8_t player);
};

}
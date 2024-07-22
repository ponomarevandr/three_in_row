#include "position.h"


namespace Game {

Position::Position(size_t height, size_t width): height(height), width(width) {
	field.assign(((width + 31) >> 5) * height, 0);
}

Position::Position(size_t height, size_t width, std::vector<uint64_t>&& field):
	height(height), width(width), field(std::move(field)) {}

size_t Position::getHeight() const {
	return height;
}

size_t Position::getWidth() const {
	return width;
}

uint8_t Position::getCell(size_t row, size_t column) const {
	size_t index = ((width + 31) >> 5) * row + (column >> 5);
	return (field[index] >> ((column & 31) << 1) & 3);
}

void Position::setCell(size_t row, size_t column, uint8_t value) {
	size_t index = ((width + 31) >> 5) * row + (column >> 5);
	field[index] &= ~(3 << ((column & 31) << 1));
	field[index] |= static_cast<uint64_t>(value) << ((column & 31) << 1);
}

bool Position::isTurnPossible(size_t column) const {
	return getCell(height - 1, column) == 0;
}

void Position::makeTurn(size_t column, uint8_t player) {
	size_t row = height - 1;
	while (row > 0 && getCell(row - 1, column) == 0) {
		--row;
	}
	setCell(row, column, player);
}


}
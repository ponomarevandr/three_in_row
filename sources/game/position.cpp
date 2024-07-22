#include "position.h"

#include "debug/output.h"


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

size_t Position::getIndexOuter(size_t row, size_t column) const {
	return ((width + 31) >> 5) * row + (column >> 5);
}

size_t Position::getIndexInner(size_t column) const {
	return (column & 31) << 1;
}

uint8_t Position::getCell(size_t row, size_t column) const {
	return (field[getIndexOuter(row, column)] >> getIndexInner(column)) & 3;
}

void Position::setCell(size_t row, size_t column, uint8_t value) {
	size_t index_outer = getIndexOuter(row, column);
	size_t index_inner = getIndexInner(column);
	field[index_outer] &= ~(static_cast<uint64_t>(3) << index_inner);
	field[index_outer] |= static_cast<uint64_t>(value) << index_inner;
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
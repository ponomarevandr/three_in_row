#include "position.h"


namespace Game {

uint8_t nextPlayer(uint8_t player) {
	return player % 3 + 1;
}


Position::Position(size_t height, size_t width): height(height), width(width) {
	field.assign(((width + 31) >> 5) * height, 0);
	calculateScores();
}

std::vector<uint64_t> Position::takeField() {
	return std::move(field);
}

const std::vector<uint64_t>& Position::getField() const {
	return field;
}

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
	field[index_outer] &= ~(3ull << index_inner);
	field[index_outer] |= static_cast<uint64_t>(value) << index_inner;
}

bool Position::isTurnPossible(size_t column) const {
	return getCell(height - 1, column) == NO_PLAYER;
}

void Position::makeTurn(size_t column, uint8_t player) {
	size_t row = height - 1;
	while (row > 0 && getCell(row - 1, column) == NO_PLAYER) {
		--row;
	}
	for (size_t index = 0; index < triples_all.size(); index += 3) {
		uint8_t player_of_triple;
		size_t quantity;
		getQuantityOfTriple(Graphics::Point(column, row), triples_all, index,
			player_of_triple, quantity);
		if (player_of_triple == SEVERAL_PLAYERS || player_of_triple == INVALID_TRIPLE)
			continue;
		if (player_of_triple == NO_PLAYER) {
			scores[player - 1] += combination_scores[1];
			continue;
		}
		if (player_of_triple == player)
			scores[player - 1] += combination_scores[quantity + 1];
		scores[player_of_triple - 1] -= combination_scores[quantity];
	}
	setCell(row, column, player);
	--free_cells;
}

Position Position::makeTurnCopy(size_t column, uint8_t player) const {
	Position result = *this;
	result.makeTurn(column, player);
	return result;
}

void Position::unmakeTurn(size_t column) {
	size_t row = 0;
	while (row + 1 < height && getCell(row + 1, column) != NO_PLAYER) {
		++row;
	}
	uint8_t player = getCell(row, column);
	setCell(row, column, NO_PLAYER);
	++free_cells;
	for (size_t index = 0; index < triples_all.size(); index += 3) {
		uint8_t player_of_triple;
		size_t quantity;
		getQuantityOfTriple(Graphics::Point(column, row), triples_all, index,
			player_of_triple, quantity);
		if (player_of_triple == SEVERAL_PLAYERS || player_of_triple == INVALID_TRIPLE)
			continue;
		if (player_of_triple == NO_PLAYER) {
			scores[player - 1] -= combination_scores[1];
			continue;
		}
		if (player_of_triple == player)
			scores[player - 1] -= combination_scores[quantity + 1];
		scores[player_of_triple - 1] += combination_scores[quantity];
	}
}


const size_t Position::combination_scores[4] = { 0, 1, 3, 100'000'000 };

const std::vector<Graphics::Vector> Position::triples_center = {
	Graphics::LEFT, Graphics::Vector(), Graphics::RIGHT,
	Graphics::SOUTH_WEST, Graphics::Vector(), Graphics::NORTH_EAST,
	Graphics::DOWN, Graphics::Vector(), Graphics::UP,
	Graphics::SOUTH_EAST, Graphics::Vector(), Graphics::NORTH_WEST
};

const std::vector<Graphics::Vector> Position::triples_all = {
	Graphics::LEFT, Graphics::Vector(), Graphics::RIGHT,
	Graphics::SOUTH_WEST, Graphics::Vector(), Graphics::NORTH_EAST,
	Graphics::DOWN, Graphics::Vector(), Graphics::UP,
	Graphics::SOUTH_EAST, Graphics::Vector(), Graphics::NORTH_WEST,
	Graphics::Vector(), Graphics::RIGHT, Graphics::RIGHT * 2,
	Graphics::Vector(), Graphics::NORTH_EAST, Graphics::NORTH_EAST * 2,
	Graphics::Vector(), Graphics::UP, Graphics::UP * 2,
	Graphics::Vector(), Graphics::NORTH_WEST, Graphics::NORTH_WEST * 2,
	Graphics::Vector(), Graphics::LEFT, Graphics::LEFT * 2,
	Graphics::Vector(), Graphics::SOUTH_WEST, Graphics::SOUTH_WEST * 2,
	Graphics::Vector(), Graphics::DOWN, Graphics::DOWN * 2,
	Graphics::Vector(), Graphics::SOUTH_EAST, Graphics::SOUTH_EAST * 2
};

void Position::getQuantityOfTriple(const Graphics::Point& start,
		const std::vector<Graphics::Vector>& triples, size_t index,
		uint8_t& player, size_t& quantity) const {
	player = NO_PLAYER;
	quantity = 0;
	const Graphics::Rectangle box(Graphics::Point(), width - 1, height - 1);
	for (size_t i = index; i < index + 3; ++i) {
		Graphics::Point current = start + triples[i];
		if (!box.isPointInside(current)) {
			player = INVALID_TRIPLE;
			quantity = 0;
			return;
		}
		uint8_t current_player = getCell(current.y, current.x);
		if (current_player == NO_PLAYER)
			continue;
		if (player == NO_PLAYER) {
			player = current_player;
		} else if (player != current_player) {
			player = SEVERAL_PLAYERS;
			quantity = 0;
			return;
		}
		++quantity;
	}
}

void Position::calculateScores() {
	scores[0] = scores[1] = scores[2] = 1;
	free_cells = 0;
	for (size_t row = 0; row < height; ++row) {
		for (size_t column = 0; column < width; ++column) {
			for (size_t index = 0; index < triples_center.size(); index += 3) {
				uint8_t player;
				size_t quantity;
				getQuantityOfTriple(Graphics::Point(column, row), triples_center, index,
					player, quantity);
				if (player == 1 || player == 2 || player == 3)
					scores[player - 1] += combination_scores[quantity];
			}
			free_cells += getCell(row, column) == NO_PLAYER;
		}
	}
}


std::array<size_t, 3> Position::getScores() const {
	return scores;
}

uint8_t Position::getOutcome() const {
	for (size_t i = 0; i < 3; ++i) {
		if (scores[i] >= combination_scores[3])
			return i + 1;
	}
	if (free_cells == 0)
		return OUTCOME_DRAW;
	return OUTCOME_UNKNOWN;
}

bool Position::isCellWinning(size_t row, size_t column) const {
	for (size_t index = 0; index < triples_all.size(); index += 3) {
		uint8_t player;
		size_t quantity;
		getQuantityOfTriple(Graphics::Point(column, row), triples_all, index,
			player, quantity);
		if (quantity == 3)
			return true;
	}
	return false;
}

}
#include "position.h"


namespace Game {

Position::Position(size_t height, size_t width): height(height), width(width) {
	field.assign(((width + 31) >> 5) * height, 0);
	calculateScores();
}

Position::Position(size_t height, size_t width, std::vector<uint64_t>&& field):
		height(height), width(width), field(std::move(field)) {
	calculateScores();
}

std::vector<uint64_t> Position::takeField() {
	return std::move(field);
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
	for (size_t index = 0; index < triples_all.size(); index += 3) {
		uint8_t triple_player;
		size_t score;
		getScoreOfTriple(Graphics::Point(column, row), triples_all, index,
			triple_player, score);
		if (triple_player == 4)
			continue;
		if (triple_player == 0) {
			++scores[player - 1];
			continue;
		}
		if (triple_player == player) {
			if (score == 2) {
				scores[0] = scores[1] = scores[2] = 0;
				scores[player - 1] = 1;
				break;
			} else {
				++scores[player - 1];
				continue;
			}
		}
		scores[triple_player - 1] -= score;

	}
	setCell(row, column, player);
	--free_cells;
}


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

void Position::getScoreOfTriple(const Graphics::Point& start,
		const std::vector<Graphics::Vector>& triples, size_t index,
		uint8_t& player, size_t& score) const {
	player = 0;
	score = 0;
	for (size_t i = index; i < index + 3; ++i) {
		Graphics::Point current = start + triples[i];
		if (current.x < 0 || current.y < 0 || current.x >= width || current.y >= height) {
			player = 4;
			score = 0;
			return;
		}
		uint8_t current_player = getCell(current.y, current.x);
		if (current_player == 0)
			continue;
		if (player == 0) {
			player = current_player;
			score = 1;
			continue;
		}
		if (player != current_player) {
			player = 4;
			score = 0;
			return;
		}
		++score;
	}
}

void Position::calculateScores() {
	scores[0] = scores[1] = scores[2] = 1;
	free_cells = 0;
	for (size_t row = 0; row < height; ++row) {
		for (size_t column = 0; column < width; ++column) {
			for (size_t index = 0; index < triples_center.size(); index += 3) {
				uint8_t player;
				size_t score;
				getScoreOfTriple(Graphics::Point(column, row), triples_center, index,
					player, score);
				if (player != 0 && player != 4)
					scores[player - 1] += score;
				if (score == 3) {
					scores[0] = scores[1] = scores[2] = 0;
					scores[player - 1] = 1;
					return;
				}
			}
			free_cells += getCell(row, column) == 0;
		}
	}
}

std::array<size_t, 3> Position::getScores() const {
	return scores;
}

bool Position::isGameEnded() const {
	return free_cells == 0 || scores[0] == 0 || scores[1] == 0 || scores[2] == 0;
}


bool Position::isCellWinning(size_t row, size_t column) const {
	for (size_t index = 0; index < triples_all.size(); index += 3) {
		uint8_t player;
		size_t score;
		getScoreOfTriple(Graphics::Point(column, row), triples_all, index,
			player, score);
		if (score == 3)
			return true;
	}
	return false;
}


}
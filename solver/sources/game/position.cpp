#include "position.h"


namespace ThreeInRow {


Position::Position() {
	initialize(0, 0);
}

void Position::initialize(size_t width, size_t height) {
	this->width = width;
	this->height = height;
	field.resize(width + 2, height + 2);
	for (size_t i = 0; i < width + 2; ++i) {
		for (size_t j = 0; j < height + 2; ++j) {
			field.set(i, j, isCellBoundary(i, j) ? WALL : EMPTY);
		}
	}
	turns.clear();
	scores.clear();
	scores.emplace_back();
}

void Position::setCell(size_t user_i, size_t user_j, uint8_t value) {
	field.set(1 + user_i, 1 + user_j, value);
}

uint8_t Position::getCell(size_t user_i, size_t user_j) const {
	return field.get(1 + user_i, 1 + user_j);
}

void Position::setupScore() {
	scores.clear();
	scores.emplace_back();
	for (size_t i = 2; i < width; ++i) {
		for (size_t j = 2; j < height; ++j) {
			scores[0] += getCellScore(i, j, false);
		}
	}
}

bool Position::makeTurn(size_t user_i, uint8_t player) {
	size_t i = 1 + user_i;
	size_t j = getColumnTop(i) + 1;
	if (j == height + 2)
		return false;
	scores.push_back(scores.back());
	scores.back() -= getCellScore(i, j, true);
	field.set(i, j, player);
	scores.back() += getCellScore(i, j, true);
	turns.push_back(i);
	return true;
}

void Position::retractTurn() {
	size_t i = turns.back();
	field.set(i, getColumnTop(i), EMPTY);
	turns.pop_back();
	scores.pop_back();
}

const Score& Position::getScore() const {
	return scores.back();
}


bool Position::isCellBoundary(size_t i, size_t j) const {
	return i == 0 || j == 0 || i == width + 1 || j == height + 1;
}

size_t Position::getColumnTop(size_t i) const {
	size_t j = 1;
	while (j < height + 2 && field.get(i, j) != EMPTY) {
		++j;
	}
	return j - 1;
}

Score Position::getCellScore(int32_t i, int32_t j, bool is_extended) const {
	const int32_t* triple_offset;
	size_t triple_offset_size;
	if (is_extended) {
		triple_offset = TRIPLE_OFFSET_EXTENDED;
		triple_offset_size = std::size(TRIPLE_OFFSET_EXTENDED);
	} else {
		triple_offset = TRIPLE_OFFSET_BASIC;
		triple_offset_size = std::size(TRIPLE_OFFSET_BASIC);
	}
	Score score;
	for (size_t index = 0; index < triple_offset_size; index += 6) {
		const int32_t* vector = triple_offset + index;
		uint8_t player = EMPTY;
		uint8_t count = 0;
		for (size_t k = 0; k < 6; k += 2) {
			uint8_t value = field.get(i + vector[k], j + vector[k + 1]);
			if (value == EMPTY)
				continue;
			if (value == WALL || (value != player && player != EMPTY)) {
				player = EMPTY;
				break;
			}
			player = value;
			++count;
		}
		if (player == EMPTY)
			continue;
		score.score[player] += Score::COST[count];
	}
	return score;
}

}
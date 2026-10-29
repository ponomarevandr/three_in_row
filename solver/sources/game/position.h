#pragma once

#include "data_structures/array_2d.h"
#include "game/score.h"

#include <iostream>
#include <string>
#include <vector>


namespace ThreeInRow {

class Position {
public:
	static const uint8_t EMPTY = 3;
	static const uint8_t WALL = 4;

private:
	// Размер без учета фиктивной стенки на границе
	size_t width;
	size_t height;
	Array2D<uint8_t> field;
	std::vector<size_t> turns;
	std::vector<Score> scores;

public:
	Position();
	void initialize(size_t width, size_t height);
	void setCell(size_t user_i, size_t user_j, uint8_t value);	// Без учета стенки
	uint8_t getCell(size_t user_i, size_t user_j) const;		// Без учета стенки
	size_t getWidth() const;
	size_t getHeight() const;

	void setupScore();	// Нужно при нетривиальной начальной позиции
	bool makeTurn(uint8_t player, size_t user_i);
	void retractTurn();
	const Score& getScore() const;

	void fromStream(std::istream&);
	void toStream(std::ostream&) const;


private:
	bool isCellBoundary(size_t, size_t) const;
	size_t getColumnTop(size_t) const;
	Score getCellScore(int32_t i, int32_t j, bool is_extended) const;
	void parseHeaderLine(std::string string);

private:
	static constexpr int32_t TRIPLE_OFFSET_BASIC[] = {
		-1,  0,  0,  0,  1,  0,
		-1,  1,  0,  0,  1, -1,
		 0,  1,  0,  0,  0, -1,
		 1,  1,  0,  0, -1, -1,
	};
	static constexpr int32_t TRIPLE_OFFSET_EXTENDED[] = {
		-1,  0,  0,  0,  1,  0,
		-1,  1,  0,  0,  1, -1,
		 0,  1,  0,  0,  0, -1,
		 1,  1,  0,  0, -1, -1,
		 0,  0, -1,  0, -2,  0,
		 0,  0, -1,  1, -2,  2,
		 0,  0,  0,  1,  0,  2,
		 0,  0,  1,  1,  2,  2,
		 0,  0,  1,  0,  2,  0,
		 0,  0,  1, -1,  2, -2,
		 0,  0,  0, -1,  0, -2,
		 0,  0, -1, -1, -2, -2,
	};
	static constexpr char SYMBOLS[] = "xov.#";
};

}
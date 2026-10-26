#pragma once

#include <cstdint>
#include <array>


namespace ThreeInRow {

class Ratio;

/*
Структура для подсчета очков игроков; поддерживает также возможность прибавления/вычитания
для удобства обновления очков при изменении ячейки поля.
*/
struct Score {
	static constexpr uint32_t COST[4] = { 0, 1, 2, 1'000'000 };
	static const uint8_t NO_WINNER = 3;
	std::array<uint32_t, 3> score = { 1, 1, 1 };
	uint8_t winner = NO_WINNER;

	Score& operator+=(const Score&);
	Score& operator-=(const Score&);
	Score operator+(const Score&) const;
	Score operator-(const Score&) const;
	Ratio getRatio() const;
	static uint32_t getCost(uint8_t count);
};


struct Ratio {
	std::array<float, 3> ratio = { 0, 0, 0 };
	uint8_t winner = Score::NO_WINNER;
	std::array<float, 3> eval;

	void updateEval();
};

}
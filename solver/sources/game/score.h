#pragma once

#include <cstdint>
#include <array>


namespace ThreeInRow {

class Ratio;

/*
Класс для подсчета очков игроков; поддерживает также возможность прибавления/вычитания
для удобства обновления очков при изменении ячейки поля.
*/
class Score {
public:
	static constexpr uint32_t COST[4] = { 0, 1, 2, 1'000'000 };
	static const uint8_t NO_WINNER = 3;

private:
	std::array<uint32_t, 3> score = { 1, 1, 1 };
	uint8_t winner = NO_WINNER;

public:
	Score() = default;
	Score& operator+=(const Score&);
	Score& operator-=(const Score&);
	Score operator+(const Score&) const;
	Score operator-(const Score&) const;
	void addForPlayer(uint8_t player, uint8_t count);
	const std::array<uint32_t, 3>& getScore() const;
	uint8_t getWinner() const;
	Ratio createRatio() const;
};


class Ratio {
	friend class Score;
private:
	std::array<float, 3> ratio = { 0, 0, 0 };
	uint8_t winner = Score::NO_WINNER;
	std::array<float, 3> eval;

public:
	const std::array<float, 3>& getRatio() const;
	uint8_t getWinner() const;
	const std::array<float, 3>& getEval() const;

private:
	Ratio() = default;
	void updateEval();
};

}
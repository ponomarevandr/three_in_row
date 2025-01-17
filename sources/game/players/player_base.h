#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"


namespace Game {

class Player {
protected:
	Position position;
	bool is_ready = false;
	Estimation estimation;
	bool is_estimation_set = false;
	size_t turn_column;

public:
	Player() = default;
	virtual ~Player() = default;
	virtual bool tryMakeTurn();
	void setPosition(Position);
	void setEstimation(Estimation);
	size_t getTurnColumn() const;
};

}
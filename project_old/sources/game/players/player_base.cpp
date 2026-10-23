#include "player_base.h"


namespace Game {

bool Player::tryMakeTurn() {
	return is_ready;
}

void Player::setPosition(Position position) {
	this->position = std::move(position);
	is_ready = is_estimation_set = false;
}

void Player::setEstimation(Estimation estimation) {
	this->estimation = estimation;
	is_estimation_set = true;
}

size_t Player::getTurnColumn() const {
	return turn_column;
}

}
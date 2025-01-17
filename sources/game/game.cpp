#include "game.h"

#include "game/position.h"


namespace Game {

Game::Game(size_t height, size_t width, size_t estimation_time_ms_target, Players&& players):
		party(height, width, estimation_time_ms_target), players(std::move(players)) {
	this->players[0]->setPosition(party.getPosition());
}

bool Game::processEstimations() {
	if (!party.processEstimations())
		return false;
	if (party.getEstimations().size() == party.getPositions().size())
		players[party.getPlayerTurn() - 1]->setEstimation(party.getEstimations().back());
	return true;
}

bool Game::processTurn() {
	if (party.getOutcome() != OUTCOME_UNKNOWN)
		return false;
	Player& player_current = *players[party.getPlayerTurn() - 1];
	if (!player_current.tryMakeTurn())
		return false;
	if (!party.isTurnPossible(player_current.getTurnColumn()))
		return false;
	party.makeTurn(player_current.getTurnColumn());
	players[party.getPlayerTurn() - 1]->setPosition(party.getPosition());
	return true;
}

const Party& Game::getParty() const {
	return party;
}

}
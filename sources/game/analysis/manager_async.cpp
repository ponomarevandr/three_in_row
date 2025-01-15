#include "manager_async.h"


namespace Game {

void AnalysisManagerAsync::action() {
	if (!manager)
		return;
	manager->run();
}

void AnalysisManagerAsync::setup(const Position& position, uint8_t player_turn,
		size_t time_ms_target) {
	manager = std::make_unique<AnalysisManager>(position, player_turn, time_ms_target);
}

const Estimation& AnalysisManagerAsync::getResult() const {
	return manager->getResult();
}

size_t AnalysisManagerAsync::getTimeMsElapsed() const {
	return manager->getTimeMsElapsed();
}


AnalysisManagerAsync analysis_manager_async;

}
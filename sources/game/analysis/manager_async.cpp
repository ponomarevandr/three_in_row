#include "manager_async.h"


namespace Game {

void AnalysisManagerAsync::action() {
	if (!manager)
		return;
	manager->run();
	is_result_pending = true;
}

void AnalysisManagerAsync::setup(Position position, uint8_t player_turn, size_t time_ms_target) {
	this->position = std::move(position);
	manager = std::make_unique<AnalysisManager>(this->position, player_turn, time_ms_target);
}

bool AnalysisManagerAsync::isResultPending() const {
	return is_result_pending;
}

const Estimation& AnalysisManagerAsync::getResult() const {
	is_result_pending = false;
	return manager->getResult();
}

size_t AnalysisManagerAsync::getTimeMsElapsed() const {
	return manager->getTimeMsElapsed();
}


AnalysisManagerAsync analysis_manager_async;

}
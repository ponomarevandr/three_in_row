#pragma once

#include "thread/worker.h"
#include "game/position.h"
#include "game/estimators/estimation.h"
#include "game/analysis/manager.h"

#include <memory>


namespace Game {

class AnalysisManagerAsync: public Thread::Worker {
protected:
	std::unique_ptr<AnalysisManager> manager;
	Position position;
	mutable bool is_result_pending = false;

protected:
	void action() override;

public:
	AnalysisManagerAsync() = default;

	// Исключительно по готовности!
	void setup(Position position, uint8_t player_turn, size_t time_ms_target);
	bool isResultPending() const;
	const Estimation& getResult() const;
	size_t getTimeMsElapsed() const;
};

extern AnalysisManagerAsync analysis_manager_async;

}
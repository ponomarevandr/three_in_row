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

protected:
	void action() override;

public:
	AnalysisManagerAsync() = default;
	void setup(const Position& position, uint8_t player_turn, size_t time_ms_target);
	const Estimation& getResult() const;
	size_t getTimeMsElapsed() const;
};

extern AnalysisManagerAsync analysis_manager_async;

}
#include "analysis_manager.h"

#include "game/estimators/estimator_pruning.h"
#include "debug/output.h"

#include <sstream>


namespace Game {

AnalysisManager::AnalysisManager(const Position& position, uint8_t player_turn,
	size_t time_ms_target): position(position), player_turn(player_turn),
	time_ms_target(time_ms_target) {}

size_t AnalysisManager::getNextTimeMsApproximate() const {
	if (times_ms_runs.size() < 2 || times_ms_runs[times_ms_runs.size() - 2] == 0)
		return 0;
	double progression_multiplier = times_ms_runs.back() / times_ms_runs[times_ms_runs.size() - 2];
	return static_cast<size_t>(times_ms_runs.back() * progression_multiplier);
}

void AnalysisManager::run() {
	time_beginning = Clock::now();
	times_ms_runs.clear();
	size_t times_ms_sum = 0;
	size_t depth = 0;
	while (depth < 2 || times_ms_sum + getNextTimeMsApproximate() <= time_ms_target) {
		EstimatorPruning estimator(position, player_turn, depth);
		estimator.run();
		result = estimator.getResult();
		times_ms_runs.push_back(estimator.getTimeMsElapsed());
		times_ms_sum += times_ms_runs.back();
		if (result.player_winning != 4)
			break;
		++depth;
	}
	time_end = Clock::now();
	debugPrint();
}

const Estimation& AnalysisManager::getResult() const {
	return result;
}

size_t AnalysisManager::getTimeMsElapsed() const {
	size_t time_ms =
		std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_beginning).count();
	return time_ms;
}

void AnalysisManager::debugPrint() const {
	if (!DEBUG)
		return;
	std::stringstream out;
	out << "==========\n";
	out << "Depth and time elapsed:\n";
	for (size_t i = 0; i < times_ms_runs.size(); ++i) {
		out << i << " -- " << times_ms_runs[i] << "\n";
	}
	Debug::output.getStream() << out.str();
}

}
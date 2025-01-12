#include "analysis_manager.h"

#include "game/position.h"
#include "game/estimators/estimator_pruning.h"
#include "game/estimators/estimator_table.h"
#include "debug/output.h"

#include <sstream>
#include <string>


namespace Game {

AnalysisManager::AnalysisManager(const Position& position, uint8_t player_turn,
	size_t time_ms_target): position(position), player_turn(player_turn),
	time_ms_target(time_ms_target) {}

size_t AnalysisManager::getNextTimeMsApproximate(const std::vector<size_t>& times_ms) {
	if (times_ms.size() < 2 || times_ms[times_ms.size() - 2] == 0)
		return 0;
	double progression_multiplier = times_ms.back() / times_ms[times_ms.size() - 2];
	return static_cast<size_t>(times_ms.back() * progression_multiplier);
}

void AnalysisManager::run() {
	time_beginning = Clock::now();
	times_ms_pruning.clear();
	times_ms_table.clear();
	is_pruning_running = is_table_running = true;
	size_t times_ms_sum = 0;
	size_t depth = 0;
	while ((is_pruning_running || is_table_running) && result.outcome == OUTCOME_UNKNOWN) {
		is_pruning_running &= depth < 2 ||
			times_ms_sum + getNextTimeMsApproximate(times_ms_pruning) <= time_ms_target;
		if (is_pruning_running) {
			EstimatorPruning estimator_pruning(position, player_turn, depth);
			estimator_pruning.run();
			result = estimator_pruning.getResult();
			times_ms_pruning.push_back(estimator_pruning.getTimeMsElapsed());
			times_ms_sum += times_ms_pruning.back();
		}
		is_table_running &= depth < 2 ||
			times_ms_sum + getNextTimeMsApproximate(times_ms_table) <= time_ms_target;
		if (is_table_running) {
			EstimatorTable estimator_table(position, player_turn, depth);
			estimator_table.run();
			result = estimator_table.getResult();
			times_ms_table.push_back(estimator_table.getTimeMsElapsed());
			times_ms_sum += times_ms_table.back();
		}
		if (is_pruning_running && is_table_running &&
				(times_ms_pruning.back() >= 5 || times_ms_table.back() >= 5)) {
			if (times_ms_pruning.back() <= times_ms_table.back()) {
				is_table_running = false;
			} else {
				is_pruning_running = false;
			}
		}
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
	for (size_t i = 0; i < times_ms_pruning.size() || i < times_ms_table.size(); ++i) {
		out << i << ": ";
		out << (i < times_ms_pruning.size() ? std::to_string(times_ms_pruning[i]) : "--") << ", ";
		out << (i < times_ms_table.size() ? std::to_string(times_ms_table[i]) : "--") << "\n";
	}
	Debug::output.getStream() << out.str();
}

}
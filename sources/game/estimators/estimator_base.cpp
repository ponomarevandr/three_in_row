#include "estimator_base.h"

#include "debug/output.h"

#include <sstream>


namespace Game {

Estimator::Estimator(const Position& position, uint8_t player_turn, size_t depth_max):
	position_start(position), player_turn_start(player_turn), depth_max(depth_max) {}

void Estimator::run() {
	nodes_visited = 0;
	time_beginning = Clock::now();
	Position position_start_copy = position_start;
	result = estimatePosition(position_start_copy, player_turn_start, depth_max);
	time_end = Clock::now();
	debugPrint();
}

const Estimation& Estimator::getResult() const {
	return result;
}

std::string Estimator::getDebugName() const {
	return "Unspecified estimator";
}

void Estimator::debugPrint() const {
	if (!DEBUG)
		return;
	std::stringstream out;
	out << "==============================\n";
	out << getDebugName() << "\n";
	out << "depth: " << depth_max << "\n";
	out << "resulting estimation:" << "\n";
	out << result.values[0] << " " << result.values[1] << " " << result.values[2] << "\n";
	size_t time_ms =
		std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_beginning).count();
	out << "time elapsed:  " << time_ms << " ms\n";
	out << "nodes visited: " << nodes_visited << "\n";
	out << "time per node: " << static_cast<double>(time_ms) / nodes_visited << "ms \n";
	Debug::output.getStream() << out.str();
}

}
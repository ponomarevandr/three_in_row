#include "estimator_base.h"

#include "debug/output.h"

#include <sstream>


namespace Game {

Estimator::Estimator(Position position, uint8_t player_turn, uint16_t depth):
	position_start(std::move(position)), player_turn_start(player_turn), depth_max(depth) {}

void Estimator::run() {
	nodes_visited = 0;
	time_beginning = Clock::now();
	estimatePosition();
	time_end = Clock::now();
	debugPrint();
}

const Estimation& Estimator::getResult() const {
	return result;
}

size_t Estimator::getTimeMsElapsed() const {
	size_t time_ms =
		std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_beginning).count();
	return time_ms;
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
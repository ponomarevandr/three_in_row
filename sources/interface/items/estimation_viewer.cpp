#include "estimation_viewer.h"

#include "interface/scenes/scene_base.h"
#include "graphics/primitives.h"
#include "graphics/players.h"
#include "game/estimators/estimation.h"


namespace Interface {

EstimationViewer::EstimationViewer(Scene* scene, const Graphics::Point& position,
	const Game::Party* party, size_t* turn_shown): Item(scene, position), party(party),
	turn_shown(turn_shown) {}

void EstimationViewer::draw() const {
	Graphics::drawBox(
		Graphics::Rectangle(position, 30, 5),
		Graphics::Color::BLACK,
		Graphics::Color::GREY
	);
	drawString(
		L"Оценка",
		position + Graphics::Vector(13, 0),
		Graphics::Color::BLACK,
		Graphics::Color::GREY
	);

	std::array<size_t, 3> scores = party->getPositions()[*turn_shown].getScores();
	for (size_t i = 0; i < 3; ++i) {
		drawString(
			std::to_wstring(scores[i]),
			position + Graphics::Vector(1 + 10 * i, 1),
			Graphics::player_colors[i + 1],
			Graphics::Color::GREY
		);
	}
	if (*turn_shown < party->getEstimations().size()) {
		Game::Estimation estimation = party->getEstimations()[*turn_shown];
		for (size_t i = 0; i < 3; ++i) {
			drawString(
				std::to_wstring(estimation.values[i]),
				position + Graphics::Vector(1 + 10 * i, 3),
				Graphics::player_colors[i + 1],
				Graphics::Color::GREY
			);
		}
		if (estimation.outcome != Game::OUTCOME_UNKNOWN) {
			drawString(
				(
					L"Виден конец: " +
					std::to_wstring(estimation.outcome) +
					L"; ходов: " +
					std::to_wstring(estimation.turns_till_end)
				),
				position + Graphics::Vector(1, 4),
				Graphics::Color::BLACK,
				Graphics::Color::GREY
			);
		}
	} else {
		drawString(
			L"Вычисление...",
			position + Graphics::Vector(10, 3),
			Graphics::Color::BLACK,
			Graphics::Color::GREY
		);
	}
}

bool EstimationViewer::canBeActive() const {
	return false;
}

}
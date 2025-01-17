#include "turns_viewer.h"

#include "interface/scenes/scene_base.h"
#include "interface/input.h"
#include "graphics/primitives.h"
#include "graphics/players.h"

#include <string>
#include <algorithm>


namespace Interface {

TurnsViewer::TurnsViewer(Scene* scene, const Graphics::Point& position, size_t height,
	Game::Party* party, size_t* turn_explored): Item(scene, position), height(height),
	party(party), turn_explored(turn_explored) {}

void TurnsViewer::draw() const {
	for (size_t i = 0; i < 3; ++i) {
		drawSymbol(
			Graphics::player_symbols[i + 1],
			position + Graphics::Vector(4 + 5 * i, 0),
			Graphics::player_colors[i + 1],
			Graphics::Color::GREY
		);
	}
	const std::vector<size_t>& columns = party->getColumns();
	for (size_t i = 0; first_turn_shown + i < columns.size() + 1 && i < (height - 1) * 3; ++i) {
		Graphics::Color background_color = (
			isActive() && *turn_explored == first_turn_shown + i
		) ? Graphics::Color::YELLOW_DARK : Graphics::Color::GREY;
		std::wstring number_string =
			first_turn_shown + i < columns.size() ? std::to_wstring(columns[i] + 1) : L"";
		number_string.resize(4, L' ');
		Graphics::drawString(
			number_string,
			position + Graphics::Vector(4 + i % 3 * 5, 1 + i / 3),
			Graphics::player_colors[i % 3 + 1],
			background_color
		);
	}
	for (size_t i = 0; i < 3; ++i) {
		drawLine({
			position + Graphics::Vector(3 + i * 5, 1),
			position + Graphics::Vector(3 + i * 5, height - 1)
		}, Graphics::Color::BLACK, Graphics::Color::GREY);
	}
	for (size_t i = 0; i + 1 < height; ++i) {
		std::wstring number_string = std::to_wstring(first_turn_shown / 3 + 1 + i);
		Graphics::drawString(
			number_string,
			position + Graphics::Vector(3 - static_cast<int>(number_string.size()), 1 + i),
			Graphics::Color::BLACK,
			Graphics::Color::GREY
		);
	}
}

void TurnsViewer::updateFirstTurnShown() {
	first_turn_shown = std::min(first_turn_shown, *turn_explored / 3 * 3);
	first_turn_shown =
		(std::max(first_turn_shown / 3 + height - 2, *turn_explored / 3) - height + 2) * 3;
}

void TurnsViewer::process() {
	if (isActive()) {
		switch (scene->getKey()) {
		case KEY_LEFT:
			if (*turn_explored > 0)
				--(*turn_explored);
			break;
		case KEY_RIGHT:
			if (*turn_explored < party->getColumns().size())
				++(*turn_explored);
			break;
		case KEY_ENTER:
			if (*turn_explored != party->getColumns().size() && callback_revert)
				callback_revert();
			break;
		}
	}
	updateFirstTurnShown();
}

void TurnsViewer::setCallbackRevert(std::function<void()> callback_revert) {
	this->callback_revert = std::move(callback_revert);
}

}
#include "position_viewer.h"

#include "interface/scenes/scene_base.h"
#include "interface/input.h"
#include "graphics/primitives.h"
#include "graphics/players.h"
#include "game/position.h"

#include <array>
#include <string>


namespace Interface {

const Graphics::Color PositionViewer::cell_colors[2] = {
	Graphics::Color::WHITE,
	Graphics::Color::GREY,
};

const Graphics::Color PositionViewer::cell_colors_selected[2] = {
	Graphics::Color::YELLOW,
	Graphics::Color::YELLOW_DARK,
};

PositionViewer::PositionViewer(Scene* scene, const Graphics::Point& position, Game::Party* party,
	size_t* turn_explored, size_t* turn_shown): Item(scene, position), party(party),
	turn_explored(turn_explored), turn_shown(turn_shown) {}

void PositionViewer::draw() const {
	Graphics::drawBox(
		Graphics::Rectangle(position, party->getWidth() + 1, party->getHeight() + 2),
		Graphics::Color::BLACK,
		Graphics::Color::GREY
	);
	for (size_t i = 0; i < party->getWidth(); i += 3) {
		std::wstring number_string = std::to_wstring(i + 1);
		Graphics::drawString(
			number_string,
			position + Graphics::Vector(2 + i - number_string.size(), party->getHeight() + 1),
			Graphics::Color::BLACK,
			cell_colors[i & 1]
		);
	}

	Game::Position game_position =
		isActive() ? party->getPosition() : party->getPositions()[*turn_shown];
	for (size_t i = 0; i < party->getHeight(); ++i) {
		for (size_t j = 0; j < party->getWidth(); ++j) {
			Graphics::Point current =
				position + Graphics::Vector(1 + j, party->getHeight() - i);
			bool is_odd = (i + j) & 1;
			Graphics::Color background_color = cell_colors[is_odd];
			if (isActive()) {
				if (party->getOutcome() == Game::OUTCOME_UNKNOWN) {
					if (j == selected_column)
						background_color = cell_colors_selected[is_odd];
				} else {
					if (game_position.isCellWinning(i, j))
						background_color = cell_colors_selected[is_odd];
				}
			}
			uint8_t player = game_position.getCell(i, j);
			Graphics::drawSymbol(
				Graphics::player_symbols[player],
				current,
				Graphics::player_colors[player],
				background_color
			);
		}
	}

	std::wstring message;
	uint8_t message_player = party->getOutcome();
	Graphics::Color message_background_color = Graphics::Color::GREY;
	if (party->getOutcome() == Game::OUTCOME_UNKNOWN) {
		message_player = party->getPlayerTurn();
		message = L"Ход ";
	} else {
		if (message_player == 0) {
			message = L"Ничья";
			if (isActive())
				message_background_color = Graphics::Color::YELLOW_DARK;
		} else {
			message = L"Победа ";
		}
	}
	drawString(
		message,
		position + Graphics::Vector(1, party->getHeight() + 8),
		Graphics::Color::BLACK,
		message_background_color
	);
	if (message_player != 0) {
		drawSymbol(
			Graphics::player_symbols[message_player],
			position + Graphics::Vector(1 + message.size(), party->getHeight() + 8),
			Graphics::player_colors[message_player],
			Graphics::Color::GREY
		);
	}
}

void PositionViewer::process() {
	size_t turn_shown_new = isActive() ? party->getTurns().size() : *turn_explored;
	if (turn_shown_new != *turn_shown) {
		*turn_shown = turn_shown_new;
		scene->redrawNeeded();
	}
	if (!isActive() || party->getOutcome() != Game::OUTCOME_UNKNOWN)
		return;
	switch (scene->getKey()) {
	case KEY_LEFT:
		selected_column = (selected_column + party->getWidth() - 1) % party->getWidth();
		break;
	case KEY_RIGHT:
		selected_column = (selected_column + 1) % party->getWidth();
		break;
	case KEY_ENTER:
	case KEY_SPACE:
		if (party->isTurnPossible(selected_column)) {
			party->makeTurn(selected_column);
			*turn_explored = party->getTurns().size();
		}
		break;
	}
}

}
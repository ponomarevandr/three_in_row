#include "position_viewer.h"

#include "interface/input.h"
#include "graphics/primitives.h"
#include "game/position.h"
#include "game/estimators/estimation.h"

#include <array>
#include <string>


namespace Interface {

const Graphics::Color PositionViewer::player_colors[4] = {
	Graphics::Color::WHITE,
	Graphics::Color::BLACK,
	Graphics::Color::BLUE,
	Graphics::Color::GREEN
};

const wchar_t PositionViewer::player_symbols[4] = {L' ', L'x', L'o', L'▽'};

const Graphics::Color PositionViewer::cell_colors[2] = {
	Graphics::Color::WHITE,
	Graphics::Color::GREY,
};

const Graphics::Color PositionViewer::cell_colors_selected[2] = {
	Graphics::Color::YELLOW,
	Graphics::Color::YELLOW_DARK,
};

PositionViewer::PositionViewer(const Graphics::Point& position, Game::Party* party,
	size_t* explored_turn): Item(position), party(party), explored_turn(explored_turn) {}

void PositionViewer::draw(bool is_active) const {
	Graphics::drawBox(Graphics::Rectangle(position, party->getWidth() + 1, party->getHeight() + 2),
		Graphics::Color::BLACK, Graphics::Color::GREY);
	for (size_t i = 0; i < party->getWidth(); i += 3) {
		std::wstring number_string = std::to_wstring(i + 1);
		Graphics::drawString(number_string,
			position + Graphics::Vector(2 + i - number_string.size(), party->getHeight() + 1),
			Graphics::Color::BLACK, cell_colors[i & 1]);
	}

	Game::Position game_position = is_active ? party->getPosition() :
		party->getPositionOfTurn(*explored_turn);
	for (size_t i = 0; i < party->getHeight(); ++i) {
		for (size_t j = 0; j < party->getWidth(); ++j) {
			Graphics::Point current = position +
				Graphics::Vector(1 + j, party->getHeight() - i);
			bool is_odd = ((i + j) & 1) != 0;
			Graphics::Color background_color = is_active &&
				(party->isGameEnded() ? game_position.isCellWinning(i, j) : j == selected_column) ?
				cell_colors_selected[is_odd] : cell_colors[is_odd];
			uint8_t player = game_position.getCell(i, j);
			Graphics::drawSymbol(player_symbols[player], current, player_colors[player],
				background_color);
		}
	}

	std::array<size_t, 3> scores = game_position.getScores();
	for (size_t i = 0; i < 3; ++i) {
		drawString(std::to_wstring(scores[i]),
			position + Graphics::Vector(1 + 10 * i, party->getHeight() + 3),
			player_colors[i + 1], Graphics::Color::GREY);
	}
	Game::Estimation estimation = is_active ? party->getEstimation() :
		party->getEstimationOfTurn(*explored_turn);
	for (size_t i = 0; i < 3; ++i) {
		drawString(std::to_wstring(estimation.values[i]),
			position + Graphics::Vector(1 + 10 * i, party->getHeight() + 5),
			player_colors[i + 1], Graphics::Color::GREY);
	}
	if (estimation.outcome != Game::OUTCOME_UNKNOWN) {
		drawString(L"Виден конец: " + std::to_wstring(estimation.outcome) +
			L"; ходов: " + std::to_wstring(estimation.turns_till_end),
			position + Graphics::Vector(1, party->getHeight() + 6),
			Graphics::Color::BLACK, Graphics::Color::GREY);
	}

	std::wstring message;
	uint8_t message_player = party->isGameEnded() ? party->getPlayerWon() : party->getPlayerTurn();
	Graphics::Color message_background_color = Graphics::Color::GREY;
	if (party->isGameEnded()) {
		if (scores[0] == 1 && scores[1] == 1 && scores[2] == 1) {
			message = L"Ничья";
			message_player = 0;
			if (is_active)
				message_background_color = Graphics::Color::YELLOW_DARK;
		} else {
			message = L"Победа ";
		}
	} else {
		message = L"Ход ";
	}
	drawString(message, position + Graphics::Vector(1, party->getHeight() + 8),
		Graphics::Color::BLACK, message_background_color);
	if (message_player != 0) {
		drawSymbol(player_symbols[message_player],
			position + Graphics::Vector(1 + message.size(), party->getHeight() + 8),
			player_colors[message_player], Graphics::Color::GREY);
	}
}

void PositionViewer::processKey(int key) {
	if (party->isGameEnded())
		return;
	switch (key) {
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
			*explored_turn = party->getTurns().size() - 1;
		}
		break;
	}
}

}
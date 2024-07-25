#include "position_viewer.h"

#include "interface/input.h"
#include "graphics/primitives.h"
#include "game/position.h"

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

PositionViewer::PositionViewer(const Graphics::Point& position, Game::Party* party):
		Item(position), party(party) {}

void PositionViewer::draw(bool is_active) const {
	Graphics::drawBox(Graphics::Rectangle(Graphics::Point(0, 0), party->getWidth() + 1,
		party->getHeight() + 2), Graphics::Color::BLACK, Graphics::Color::GREY);
	for (size_t i = 0; i < party->getWidth(); i += 3) {
		std::wstring number_string = std::to_wstring(i + 1);
		Graphics::drawString(number_string,
			Graphics::Point(2 + i - number_string.size(), party->getHeight() + 1),
			Graphics::Color::BLACK, cell_colors[i & 1]);
	}
	for (size_t i = 0; i < party->getHeight(); ++i) {
		for (size_t j = 0; j < party->getWidth(); ++j) {
			Graphics::Point current = position +
				Graphics::Vector(j, party->getHeight() - i - 1);
			bool is_odd = ((i + j) & 1) != 0;
			Graphics::Color background_color = is_active && !party->isGameEnded() &&
				j == selected_column ? cell_colors_selected[is_odd] : cell_colors[is_odd];
			uint8_t player = party->getPosition().getCell(i, j);
			Graphics::drawSymbol(player_symbols[player], current, player_colors[player],
				background_color);
		}
	}
	std::array<size_t, 3> scores = party->getPosition().getScores();
	for (size_t i = 0; i < 3; ++i) {
		drawString(std::to_wstring(scores[i]),
			Graphics::Point(1 + 10 * i, party->getHeight() + 3),
			player_colors[i + 1], Graphics::Color::GREY);
	}
	std::wstring message;
	uint8_t message_player = party->getTurnPlayer();
	if (party->isGameEnded()) {
		if (scores[0] == 1 && scores[1] == 1 && scores[2] == 1) {
			message = L"Ничья";
			message_player = 0;
		} else {
			message = L"Победа ";
		}
	} else {
		message = L"Ход ";
	}
	drawString(message, Graphics::Point(1, party->getHeight() + 5),
		Graphics::Color::BLACK, Graphics::Color::GREY);
	if (message_player != 0) {
		drawSymbol(player_symbols[message_player],
			Graphics::Point(1 + message.size(), party->getHeight() + 5),
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
		if (party->isTurnPossible(selected_column))
			party->makeTurn(selected_column);
		break;
	}
}

}
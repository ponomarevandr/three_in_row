#include "position_viewer.h"

#include "interface/input.h"
#include "graphics/primitives.h"

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

PositionViewer::PositionViewer(const Graphics::Point& position): Item(position) {
	game_position = Game::Position(7, 35);
}

void PositionViewer::draw(bool is_active) const {
	Graphics::drawBox(Graphics::Rectangle(Graphics::Point(0, 0), game_position.getWidth() + 1,
		game_position.getHeight() + 2), Graphics::Color::BLACK, Graphics::Color::GREY);
	for (size_t i = 0; i < game_position.getWidth(); i += 3) {
		std::wstring number_string = std::to_wstring(i + 1);
		Graphics::drawString(number_string,
			Graphics::Point(2 + i - number_string.size(), game_position.getHeight() + 1),
			Graphics::Color::BLACK, cell_colors[i & 1]);
	}
	for (size_t i = 0; i < game_position.getHeight(); ++i) {
		for (size_t j = 0; j < game_position.getWidth(); ++j) {
			Graphics::Point current = position +
				Graphics::Vector(j, game_position.getHeight() - i - 1);
			bool is_odd = ((i + j) & 1) != 0;
			Graphics::Color background_color = is_active && !game_position.isGameEnded() &&
				j == selected_column ? cell_colors_selected[is_odd] : cell_colors[is_odd];
			uint8_t player = game_position.getCell(i, j);
			Graphics::drawSymbol(player_symbols[player], current, player_colors[player],
				background_color);
		}
	}
	std::array<size_t, 3> scores = game_position.getScores();
	for (size_t i = 0; i < 3; ++i) {
		drawString(std::to_wstring(scores[i]),
			Graphics::Point(1 + 10 * i, game_position.getHeight() + 3),
			player_colors[i + 1], Graphics::Color::GREY);
	}
	std::wstring message;
	uint8_t message_player = player_turn;
	if (game_position.isGameEnded()) {
		if (scores[0] == 1 && scores[1] == 1 && scores[2] == 1) {
			message = L"Ничья";
			message_player = 0;
		} else {
			message = L"Победа ";
		}
	} else {
		message = L"Ход ";
	}
	drawString(message, Graphics::Point(1, game_position.getHeight() + 5),
		Graphics::Color::BLACK, Graphics::Color::GREY);
	if (message_player != 0) {
		drawSymbol(player_symbols[message_player],
			Graphics::Point(1 + message.size(), game_position.getHeight() + 5),
			player_colors[message_player], Graphics::Color::GREY);
	}
}

void PositionViewer::processKey(int key) {
	if (game_position.isGameEnded())
		return;
	switch (key) {
	case KEY_LEFT:
		selected_column = (selected_column + game_position.getWidth() - 1) %
			game_position.getWidth();
		break;
	case KEY_RIGHT:
		selected_column = (selected_column + 1) % game_position.getWidth();
		break;
	case KEY_ENTER:
	case KEY_SPACE:
		if (game_position.isTurnPossible(selected_column)) {
			game_position.makeTurn(selected_column, player_turn);
			if (!game_position.isGameEnded())
				player_turn = player_turn % 3 + 1;
		}
		break;
	}
}

}
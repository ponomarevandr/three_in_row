#include "position_viewer.h"

#include "interface/input.h"
#include "graphics/primitives.h"
#include "graphics/screen.h"

#include <array>
#include <string>


namespace Interface {

PositionViewer::PositionViewer(const Graphics::Point& position): Item(position) {
	game_position = Game::Position(5, 7);
}

void PositionViewer::draw(bool is_active) const {
	for (size_t i = 0; i < game_position.getHeight(); ++i) {
		for (size_t j = 0; j < game_position.getWidth(); ++j) {
			Graphics::Point current = position +
				Graphics::Vector(j, game_position.getHeight() - i - 1);
			Graphics::Color background_color = is_active && j == selected_column ?
				Graphics::Color::YELLOW : Graphics::Color::WHITE;
			switch (game_position.getCell(i, j)) {
			case 0:
				Graphics::drawSymbol(L' ', current, Graphics::Color::WHITE, background_color);
				break;
			case 1:
				Graphics::drawSymbol(L'x', current, Graphics::Color::BLACK, background_color);
				break;
			case 2:
				Graphics::drawSymbol(L'o', current, Graphics::Color::BLUE, background_color);
				break;
			case 3:
				Graphics::drawSymbol(L'▽', current, Graphics::Color::GREEN, background_color);
				break;
			default:
				Graphics::drawSymbol(L'?', current, Graphics::Color::RED, background_color);
				break;
			}
		}
	}
	std::array<size_t, 3> scores = game_position.getScores();
	drawString(std::to_wstring(scores[0]), Graphics::Point(1, game_position.getHeight() + 2),
		Graphics::Color::BLACK, Graphics::Color::WHITE);
	drawString(std::to_wstring(scores[1]), Graphics::Point(1, game_position.getHeight() + 4),
		Graphics::Color::BLUE, Graphics::Color::WHITE);
	drawString(std::to_wstring(scores[2]), Graphics::Point(1, game_position.getHeight() + 6),
		Graphics::Color::GREEN, Graphics::Color::WHITE);
}

void PositionViewer::processKey(int key) {
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
			player_turn = player_turn % 3 + 1;
		}
		break;
	}
}

}
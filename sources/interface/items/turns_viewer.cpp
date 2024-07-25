#include "turns_viewer.h"

#include "interface/input.h"
#include "graphics/primitives.h"

#include <string>


namespace Interface {

const Graphics::Color TurnsViewer::player_colors[4] = {
	Graphics::Color::WHITE,
	Graphics::Color::BLACK,
	Graphics::Color::BLUE,
	Graphics::Color::GREEN
};

TurnsViewer::TurnsViewer(const Graphics::Point& position, Game::Party* party,
	size_t* explored_turn): Item(position), party(party), explored_turn(explored_turn) {}

void TurnsViewer::draw(bool is_active) const {
	const std::vector<size_t>& turns = party->getTurns();
	for (size_t i = 0; i < turns.size(); ++i) {
		Graphics::Color background_color = is_active && *explored_turn == i ?
			Graphics::Color::YELLOW_DARK : Graphics::Color::GREY;
		if (i == 0) {
			Graphics::drawString(std::wstring(15, L' '), position,
				Graphics::Color::BLACK, background_color);
		} else {
			std::wstring number_string = std::to_wstring(turns[i] + 1);
			number_string.resize(5, L' ');
			Graphics::drawString(number_string,
				position + Graphics::Vector((i - 1) % 3 * 5, 1 + (i - 1) / 3),
				player_colors[(i - 1) % 3 + 1], background_color);
		}
	}
}

void TurnsViewer::processKey(int key) {
	switch (key) {
	case KEY_LEFT:
		if (*explored_turn > 0)
			--(*explored_turn);
		break;
	case KEY_RIGHT:
		if (*explored_turn + 1 < party->getTurns().size())
			++(*explored_turn);
		break;
	}
}

}
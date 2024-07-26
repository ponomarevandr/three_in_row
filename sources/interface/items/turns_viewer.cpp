#include "turns_viewer.h"

#include "interface/input.h"
#include "interface/translation.h"
#include "graphics/primitives.h"

#include <string>
#include <algorithm>


namespace Interface {

const Graphics::Color TurnsViewer::player_colors[3] = {
	Graphics::Color::BLACK,
	Graphics::Color::BLUE,
	Graphics::Color::GREEN
};

const wchar_t TurnsViewer::player_symbols[3] = {L'x', L'o', L'▽'};

TurnsViewer::TurnsViewer(const Graphics::Point& position, int height, Game::Party* party,
	size_t* explored_turn): Item(position), height(height), party(party),
	explored_turn(explored_turn) {}

void TurnsViewer::updateFirstTurnShown() const {
	while (first_turn_shown > *explored_turn) {
		if (first_turn_shown == 1) {
			first_turn_shown = 0;
		} else {
			first_turn_shown -= 3;
		}
	}
	while (true) {
		std::pair<size_t, size_t> turn = turnToUser(first_turn_shown);
		turn.first += height - 1;
		if (turnToProgram(turn.first, turn.second) > *explored_turn)
			break;
		if (first_turn_shown == 0) {
			first_turn_shown = 1;
		} else {
			first_turn_shown += 3;
		}
	}
}

void TurnsViewer::draw(bool is_active) const {
	updateFirstTurnShown();
	for (size_t i = 0; i < 3; ++i) {
		drawSymbol(player_symbols[i], position + Graphics::Vector(4 + 5 * i, 0),
			player_colors[i], Graphics::Color::GREY);
	}
	const std::vector<size_t>& turns = party->getTurns();
	size_t line = 0;
	for (size_t i = first_turn_shown; i < turns.size() && line + 1 < height; ++i) {
		Graphics::Color background_color = is_active && *explored_turn == i ?
			Graphics::Color::YELLOW_DARK : Graphics::Color::GREY;
		if (i == 0) {
			Graphics::drawString(std::wstring(14, L'#'),
				position + Graphics::Vector(4, 1),
				Graphics::Color::BLACK, background_color);
			++line;
		} else {
			std::wstring number_string = std::to_wstring(turns[i] + 1);
			number_string.resize(4, L' ');
			size_t turn_third = turnToUser(i).second;
			Graphics::drawString(number_string,
				position + Graphics::Vector(4 + turn_third * 5, 1 + line),
				player_colors[turn_third], background_color);
			line += turn_third == 2;
		}
	}
	for (size_t i = 0; i < 3; ++i) {
		drawLine({
			position + Graphics::Vector(3 + i * 5, 1),
			position + Graphics::Vector(3 + i * 5, height - 1)
		}, Graphics::Color::BLACK, Graphics::Color::GREY);
	}
	for (size_t i = 0; i + 1 < height; ++i) {
		std::wstring number_string = std::to_wstring(turnToUser(first_turn_shown).first + i);
		Graphics::drawString(number_string,
			position + Graphics::Vector(3 - static_cast<int>(number_string.size()), 1 + i),
			Graphics::Color::BLACK, Graphics::Color::GREY);
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
	case KEY_ENTER:
		if (*explored_turn + 1 != party->getTurns().size() && callback_revert)
			callback_revert();
		break;
	}
}

void TurnsViewer::setCallbackRevert(std::function<void()>&& callback_revert) {
	this->callback_revert = callback_revert;
}

}
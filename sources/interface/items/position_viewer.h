#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "game/position.h"


namespace Interface {

class PositionViewer: public Item {
private:
	static const Graphics::Color player_colors[4];
	static const wchar_t player_symbols[4];
	static const Graphics::Color cell_colors[2];
	static const Graphics::Color cell_colors_selected[2];

private:
	Game::Position game_position;
	size_t selected_column = 0;
	uint8_t player_turn = 1;

public:
	PositionViewer(const Graphics::Point& position);
	void draw(bool is_active) const override;
	void processKey(int key) override;
};

}
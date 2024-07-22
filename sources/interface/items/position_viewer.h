#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "game/position.h"


namespace Interface {

class PositionViewer: public Item {
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
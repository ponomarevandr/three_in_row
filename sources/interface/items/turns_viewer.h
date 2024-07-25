#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "game/party.h"


namespace Interface {

class TurnsViewer: public Item {
private:
	static const Graphics::Color player_colors[4];

private:
	Game::Party* party;
	size_t* explored_turn;

public:
	TurnsViewer(const Graphics::Point& position, Game::Party* party, size_t* explored_turn);
	void draw(bool is_active) const override;
	void processKey(int key) override;
};

}
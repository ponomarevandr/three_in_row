#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "game/party.h"


namespace Interface {

class PositionViewer: public Item {
private:
	static const Graphics::Color cell_colors[2];
	static const Graphics::Color cell_colors_selected[2];

private:
	Game::Party* party;
	size_t* explored_turn;
	size_t selected_column = 0;

public:
	PositionViewer(Scene* scene, const Graphics::Point& position, Game::Party* party,
		size_t* explored_turn);
	void draw() const override;
	void process() override;
};

}
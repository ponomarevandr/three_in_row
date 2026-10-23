#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "game/party.h"

#include <functional>


namespace Interface {

class PositionViewer: public Item {
private:
	static const Graphics::Color cell_colors[2];
	static const Graphics::Color cell_colors_selected[2];

private:
	const Game::Party* party;
	size_t* turn_explored;
	size_t* turn_shown;
	size_t selected_column = 0;
	std::function<void(size_t)> callback_make_turn;

public:
	PositionViewer(Scene* scene, const Graphics::Point& position, const Game::Party* party,
		size_t* turn_explored, size_t* turn_shown);
	void draw() const override;
	void process() override;
	void setCallbackMakeTurn(std::function<void(size_t)>);
};

}
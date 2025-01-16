#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "game/party.h"

#include <functional>


namespace Interface {

class TurnsViewer: public Item {
private:
	size_t height;
	Game::Party* party;
	size_t* explored_turn;
	size_t first_turn_shown = 0;
	std::function<void()> callback_revert;

private:
	void updateFirstTurnShown();

public:
	TurnsViewer(Scene* scene, const Graphics::Point& position, size_t height, Game::Party* party,
		size_t* explored_turn);
	void draw() const override;
	void process() override;
	void setCallbackRevert(std::function<void()>);
};

}
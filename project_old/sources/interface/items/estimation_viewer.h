#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "game/party.h"


namespace Interface {

class EstimationViewer: public Item {
private:
	const Game::Party* party;
	size_t* turn_shown;

public:
	EstimationViewer(Scene* scene, const Graphics::Point& position, const Game::Party* party,
		size_t* turn_shown);
	void draw() const override;
	bool canBeActive() const override;
};

}
#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "game/party.h"

#include <functional>


namespace Interface {

class TurnsViewer: public Item {
private:
	static const Graphics::Color player_colors[3];
	static const wchar_t player_symbols[3];

private:
	int height;
	Game::Party* party;
	size_t* explored_turn;
	mutable size_t first_turn_shown = 0;
	std::function<void()> callback_revert;

private:
	void updateFirstTurnShown() const;

public:
	TurnsViewer(Scene* scene, const Graphics::Point& position, int height, Game::Party* party,
		size_t* explored_turn);
	void draw() const override;
	void process() override;
	void setCallbackRevert(std::function<void()>&&);
};

}
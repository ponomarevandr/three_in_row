#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "game/position.h"


namespace Interface {

class TurnsViewer: public Item {
private:
	static const Graphics::Color player_colors[4];

private:
	std::vector<size_t> turns;

public:
	explicit TurnsViewer(const Graphics::Point& position);
	void draw(bool is_active) const override;
	void processKey(int key) override;
};

}
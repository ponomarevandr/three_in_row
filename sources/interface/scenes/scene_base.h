#pragma once

#include "interface/items/item_base.h"

#include <vector>
#include <memory>


namespace Interface {

class Game;

class Scene {
protected:
	std::vector<std::unique_ptr<Item>> items;
	size_t active_index = 0;
	Game* game;

public:
	explicit Scene(Game*);
	virtual void draw() const;
	virtual void processKey(int key);
};

}
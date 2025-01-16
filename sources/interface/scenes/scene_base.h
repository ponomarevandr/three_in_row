#pragma once

#include "interface/items/item_base.h"

#include <vector>
#include <memory>


namespace Interface {

class Application;

class Scene {
protected:
	std::vector<std::unique_ptr<Item>> items;
	size_t active_index = 0;
	Application* application;

public:
	explicit Scene(Application*);
	virtual ~Scene() = default;
	virtual void draw() const;
	virtual void process();
	int getKey() const;
	void redrawNeeded();
	bool isItemActive(const Item*) const;
};

}
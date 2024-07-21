#pragma once

#include "graphics/geometry.h"


namespace Interface {

class Item {
protected:
	Graphics::Point position;

public:
	explicit Item(const Graphics::Point& position);
	virtual void draw(bool is_active) const;
	virtual void processKey(int key);
};

}
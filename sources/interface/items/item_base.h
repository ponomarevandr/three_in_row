#pragma once

#include "graphics/geometry.h"


namespace Interface {

class Scene;

class Item {
protected:
	Scene* scene;
	Graphics::Point position;

public:
	Item(Scene* scene, const Graphics::Point& position);
	virtual ~Item() = default;
	virtual void draw() const;
	virtual void process();
	virtual bool canBeActive() const;
	bool isActive() const;
};

}
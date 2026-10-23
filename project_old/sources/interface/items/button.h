#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"

#include <string>
#include <functional>


namespace Interface {

class Button: public Item {
protected:
	size_t width;
	std::wstring text;
	std::function<void()> callback;

public:
	Button(Scene* scene, const Graphics::Point& position, size_t width);
	void draw() const override;
	void process() override;
	void setText(const std::wstring&);
	void setCallback(std::function<void()>);
};

}
#pragma once

#include "interface/items/item_base.h"
#include "graphics/geometry.h"

#include <string>
#include <functional>


namespace Interface {

class Button: public Item {
protected:
	int width;
	int height;
	std::wstring text;
	std::function<void()> callback;

public:
	Button(const Graphics::Point& position, int width, int height);
	void draw(bool is_active) const override;
	void processKey(int key) override;
	void setText(const std::wstring&);
	void setCallback(std::function<void()>&&);
};

}
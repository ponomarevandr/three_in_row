#include "item_base.h"

#include "graphics/primitives.h"


namespace Interface {

Item::Item(const Graphics::Point& position): position(position) {}

void Item::draw(bool is_active) const {
	Graphics::Color foreground_color = is_active ? Graphics::Color::RED : Graphics::Color::BLACK;
	Graphics::drawSymbol(L'?', position, foreground_color, Graphics::Color::WHITE);
}

void Item::processKey(int key) {}

}
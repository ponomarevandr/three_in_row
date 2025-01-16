#include "item_base.h"

#include "interface/scenes/scene_base.h"
#include "graphics/primitives.h"


namespace Interface {

Item::Item(Scene* scene, const Graphics::Point& position): scene(scene), position(position) {}

void Item::draw() const {
	Graphics::Color foreground_color = isActive() ? Graphics::Color::RED : Graphics::Color::BLACK;
	Graphics::drawSymbol(L'?', position, foreground_color, Graphics::Color::WHITE);
}

void Item::process() {}

bool Item::canBeActive() const {
	return true;
}

bool Item::isActive() const {
	return scene->isItemActive(this);
}

}
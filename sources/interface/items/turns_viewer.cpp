#include "turns_viewer.h"

#include "interface/input.h"
#include "graphics/primitives.h"

#include <string>


namespace Interface {

const Graphics::Color TurnsViewer::player_colors[4] = {
	Graphics::Color::WHITE,
	Graphics::Color::BLACK,
	Graphics::Color::BLUE,
	Graphics::Color::GREEN
};

TurnsViewer::TurnsViewer(const Graphics::Point& position): Item(position) {}

void TurnsViewer::draw(bool is_active) const {}

void TurnsViewer::processKey(int key) {}


}
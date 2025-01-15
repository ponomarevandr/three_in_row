#include "button.h"

#include "interface/scenes/scene_base.h"
#include "interface/input.h"
#include "graphics/primitives.h"
#include "graphics/screen.h"


namespace Interface {

Button::Button(Scene* scene, const Graphics::Point& position, int width, int height):
	Item(scene, position), width(width), height(height) {}

void Button::draw() const {
	std::wstring edited_text = isActive() ? L"< " + text + L" >" : text;
	drawStringAtCenter(edited_text, Graphics::Rectangle(position, width, height),
		Graphics::Color::BLACK, Graphics::Color::GREY);
}

void Button::process() {
	if (!isActive())
		return;
	if (scene->getKey() == KEY_ENTER && callback)
		callback();
}

void Button::setText(const std::wstring& text) {
	this->text = text;
}

void Button::setCallback(std::function<void()>&& callback) {
	this->callback = callback;
}

}
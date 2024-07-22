#include "button.h"

#include "interface/input.h"
#include "graphics/primitives.h"
#include "graphics/screen.h"


namespace Interface {

Button::Button(const Graphics::Point& position, int width, int height): Item(position),
	width(width), height(height) {}

void Button::draw(bool is_active) const {
	std::wstring edited_text = is_active ? L"< " + text + L" >" : text;
	drawStringAtCenter(edited_text, Graphics::Rectangle(position, width, height),
		Graphics::Color::GREEN, Graphics::Color::BLACK);
}

void Button::processKey(int key) {
	if (key == KEY_ENTER && callback)
		callback();
}

void Button::setText(const std::wstring& text) {
	this->text = text;
}

void Button::setCallback(std::function<void()>&& callback) {
	this->callback = callback;
}

}
#include "application.h"

#include "graphics/screen.h"

#include <ncurses.h>


namespace Interface {

Application::Application() {
	Graphics::screenInitialize(REFRESH_RATE);
}

Application::~Application() {
	Graphics::screenFinalize();
}

void Application::run() {
	while (!scenes.empty()) {
		if (key != NO_KEY || is_redraw_needed) {
			scenes.back()->draw();
			Graphics::screenRefresh();
			is_redraw_needed = false;
		}
		key = getch();
		scenes.back()->process();
		scenes_popped.clear();
	}
}

void Application::pushScene(std::unique_ptr<Scene>&& scene) {
	scenes.push_back(std::move(scene));
}

void Application::popScene() {
	scenes_popped.push_back(std::move(scenes.back()));
	scenes.pop_back();
}

void Application::replaceScene(std::unique_ptr<Scene>&& scene) {
	popScene();
	pushScene(std::move(scene));
}

int Application::getKey() const {
	return key;
}

void Application::redrawNeeded() {
	is_redraw_needed = true;
}

}
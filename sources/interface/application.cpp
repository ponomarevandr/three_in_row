#include "application.h"

#include "interface/input.h"
#include "graphics/screen.h"


namespace Interface {

Application::Application() {
	Graphics::screenInitialize();
}

Application::~Application() {
	Graphics::screenFinalize();
}

void Application::run() {
	while (!scenes.empty()) {
		scenes.back()->draw();
		Graphics::screenRefresh();
		int key = getKey();
		scenes.back()->processKey(key);
	}
}

void Application::pushScene(std::unique_ptr<Scene>&& scene) {
	scenes.push_back(std::move(scene));
}

void Application::popScene() {
	scenes.pop_back();
}

void Application::replaceScene(std::unique_ptr<Scene>&& scene) {
	popScene();
	pushScene(std::move(scene));
}

}
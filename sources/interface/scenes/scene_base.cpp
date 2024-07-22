#include "scene_base.h"

#include "interface/application.h"
#include "interface/input.h"
#include "graphics/primitives.h"


namespace Interface {

Scene::Scene(Application* application): application(application) {}

void Scene::draw() const {
	Graphics::fillScreen(Graphics::Color::BLACK);
	for (size_t i = 0; i < items.size(); ++i) {
		items[i]->draw(i == active_index);
	}
}

void Scene::processKey(int key) {
	if (items.empty())
		return;
	switch (key) {
	case KEY_UP:
		active_index = (active_index + items.size() - 1) % items.size();
		break;
	case KEY_DOWN:
		active_index = (active_index + 1) % items.size();
		break;
	default:
		items[active_index]->processKey(key);
		break;
	}
}

}
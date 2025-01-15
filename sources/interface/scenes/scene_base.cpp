#include "scene_base.h"

#include "interface/application.h"
#include "interface/input.h"
#include "graphics/primitives.h"


namespace Interface {

Scene::Scene(Application* application): application(application) {}

void Scene::draw() const {
	Graphics::fillScreen(Graphics::Color::GREY);
	for (size_t i = 0; i < items.size(); ++i) {
		items[i]->draw();
	}
}

void Scene::process() {
	if (items.empty())
		return;
	switch (getKey()) {
	case KEY_UP:
		active_index = (active_index + items.size() - 1) % items.size();
		break;
	case KEY_DOWN:
		active_index = (active_index + 1) % items.size();
		break;
	}
	for (size_t i = 0; i < items.size(); ++i) {
		items[i]->process();
	}
}

int Scene::getKey() const {
	return application->getKey();
}

void Scene::redrawNeeded() {
	application->redrawNeeded();
}

bool Scene::isItemActive(const Item* item) const {
	if (items.empty())
		return false;
	return item == items[active_index].get();
}

}
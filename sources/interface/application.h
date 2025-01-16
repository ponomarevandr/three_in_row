#pragma once

#include "interface/scenes/scene_base.h"
#include "interface/input.h"

#include <vector>
#include <memory>


namespace Interface {

class Application {
private:
	static constexpr float REFRESH_RATE = 20.0f;

private:
	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<std::unique_ptr<Scene>> scenes_popped;
	int key = NO_KEY;
	bool is_redraw_needed = true;

public:
	Application();
	~Application();
	void run();
	void pushScene(std::unique_ptr<Scene>&&);
	void popScene();
	void replaceScene(std::unique_ptr<Scene>&&);
	int getKey() const;
	void redrawNeeded();
};

}
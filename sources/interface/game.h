#pragma once

#include "interface/scenes/scene_base.h"

#include <vector>
#include <memory>


namespace Interface {

class Game {
private:
	std::vector<std::unique_ptr<Scene>> scenes;

public:
	Game();
	~Game();
	void run();
	void pushScene(std::unique_ptr<Scene>&&);
	void popScene();
	void replaceScene(std::unique_ptr<Scene>&&);
};

}
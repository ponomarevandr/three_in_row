#include "interface/application.h"
#include "interface/scenes/scene_main_menu.h"
#include "interface/scenes/scene_game.h"

#include <memory>


int main() {
    Interface::Application application;
    application.pushScene(std::make_unique<Interface::SceneGame>(&application));
    application.run();
    return 0;
}

// xo▽
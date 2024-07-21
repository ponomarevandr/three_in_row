#include "interface/game.h"
#include "interface/scenes/scene_main_menu.h"

#include <memory>


int main() {
    Interface::Game game;
    game.pushScene(std::make_unique<Interface::SceneMainMenu>(&game));
    game.run();
    return 0;
}

// xo▽
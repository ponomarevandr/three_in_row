#include "game.h"

#include "graphics/screen.h"

#include <ncurses.h>


namespace Interface {

Game::Game() {
	Graphics::screenInitialize();
}

Game::~Game() {
	Graphics::screenFinalize();
}

void Game::run() {
	while (!scenes.empty()) {
		scenes.back()->draw();
		Graphics::screenRefresh();
		int key = getch();
		scenes.back()->processKey(key);
	}
}

void Game::pushScene(std::unique_ptr<Scene>&& scene) {
	scenes.push_back(std::move(scene));
}

void Game::popScene() {
	scenes.pop_back();
}

void Game::replaceScene(std::unique_ptr<Scene>&& scene) {
	popScene();
	pushScene(std::move(scene));
}

}
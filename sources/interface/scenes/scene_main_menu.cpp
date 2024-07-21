#include "scene_main_menu.h"

#include "interface/game.h"
#include "interface/items/button.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"

#include <memory>


namespace Interface {

SceneMainMenu::SceneMainMenu(Game* game): Scene(game) {
	auto button_play = std::make_unique<Button>(Graphics::Point(0, 10),
		Graphics::getScreenWidth() - 1, 0);
	button_play->setText(L"Играть");
	items.push_back(std::move(button_play));

	auto button_about = std::make_unique<Button>(Graphics::Point(0, 12),
		Graphics::getScreenWidth() - 1, 0);
	button_about->setText(L"Об игре");
	items.push_back(std::move(button_about));

	auto button_exit = std::make_unique<Button>(Graphics::Point(0, 14),
		Graphics::getScreenWidth() - 1, 0);
	button_exit->setText(L"Выход");
	button_exit->setCallback([this]() {
		this->game->popScene();
	});
	items.push_back(std::move(button_exit));
}

}
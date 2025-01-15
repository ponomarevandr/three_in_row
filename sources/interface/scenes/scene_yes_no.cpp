#include "scene_yes_no.h"

#include "interface/application.h"
#include "interface/items/button.h"
#include "graphics/geometry.h"
#include "graphics/primitives.h"
#include "graphics/screen.h"

#include <memory>


namespace Interface {

SceneYesNo::SceneYesNo(Application* application): Scene(application) {
	auto button_yes = std::make_unique<Button>(this,
		Graphics::Point(0, 10),
		Graphics::getScreenWidth() - 1
	);
	button_yes->setText(L"Да");
	button_yes->setCallback([this]() {
		this->application->popScene();
		if (this->callbacks[true])
			this->callbacks[true]();
	});
	items.push_back(std::move(button_yes));

	auto button_no = std::make_unique<Button>(this,
		Graphics::Point(0, 12),
		Graphics::getScreenWidth() - 1
	);
	button_no->setText(L"Нет");
	button_no->setCallback([this]() {
		this->application->popScene();
		if (this->callbacks[false])
			this->callbacks[false]();
	});
	items.push_back(std::move(button_no));

	active_index = 1;
}

void SceneYesNo::draw() const {
	Scene::draw();
	Graphics::drawString(
		question,
		Graphics::Point(2, 7),
		Graphics::Color::BLACK,
		Graphics::Color::GREY
	);
}

void SceneYesNo::setQuestion(const std::wstring& question) {
	this->question = question;
}

void SceneYesNo::setCallback(bool answer, std::function<void()> callback) {
	callbacks[answer] = std::move(callback);
}

}
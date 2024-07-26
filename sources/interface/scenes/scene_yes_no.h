#pragma once

#include "interface/scenes/scene_base.h"

#include <string>
#include <functional>


namespace Interface {

class SceneYesNo: public Scene {
protected:
	std::function<void()> callbacks[2];
	std::wstring question;

public:
	explicit SceneYesNo(Application*);
	void draw() const override;
	void setQuestion(const std::wstring&);
	void setCallback(bool answer, std::function<void()>&& callback);
};

}
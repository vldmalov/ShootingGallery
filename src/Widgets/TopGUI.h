#pragma once

#include "ImageWidget.h"
#include "TextWidget.h"

namespace UI {

class TopGUI: public GUI::Widget
{
	typedef GUI::Widget baseclass;
public:
	TopGUI(const std::string& name);
	TopGUI(const std::string& name, rapidxml::xml_node<>* elem);
	
	void Draw() override;
	void Update(float dt) override;
	
	void AcceptMessage(const Message& message) override;
	
	void Reset();
	void SetScore(const std::string& score);
	void SetTimer(const std::string& timer);
	
private:
	std::unique_ptr<ImageWidget> _scoreIcon;
	std::unique_ptr<TextWidget>  _scoreText;
	std::unique_ptr<TextWidget>  _timerText;
};

}

#pragma once

#include "ImageWidget.h"
#include "TextWidget.h"
#include "ButtonWidget.h"

namespace UI {

class TopGUI
{
public:
	TopGUI();
	
	void Draw();
	void Update(float dt);
	
	bool MouseDown(const IPoint &mouse_pos);
	void MouseUp(const IPoint &mouse_pos);
	
	void SetClientRect(const IRect& rect);
	
	void Reset();
	void SetScore(const std::string& score);
	void SetTimer(const std::string& timer);
	void SetOnMenuButtonCallback(buttonAction cb);
	
	TopGUI(const TopGUI&) = delete;
	TopGUI& operator=(const TopGUI&) = delete;
	
private:
	IRect _clientRect;
	std::unique_ptr<ImageWidget> _scoreIcon;
	std::unique_ptr<TextWidget>  _scoreText;
	std::unique_ptr<TextWidget>  _timerText;
	
	std::unique_ptr<ButtonWidget> _menuButton;
	std::unique_ptr<TextWidget>   _menuText;
};

}

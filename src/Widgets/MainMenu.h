#pragma once

#include "ImageWidget.h"
#include "TextWidget.h"
#include "ButtonWidget.h"

namespace UI {
	
enum class mainMenuState {
	PAUSE,
	COMPLETE_LEVEL,
	TIME_IS_OVER
};

class MainMenu
{
public:
	MainMenu();
	
	void Draw();
	
	bool MouseDown(const IPoint& mouse_pos);
	void MouseUp(const IPoint& mouse_pos);

	void Reset();
	void Show(const mainMenuState& state);
	void Hide();
	
	void setClientRect(const IRect& rect);
	
	void SetOnResumeGameCallback(buttonAction cb);
	void SetOnStartNewGameCallback(buttonAction cb);
	
private:
	IRect _clientRect;
	bool  _visible;
	std::unique_ptr<ImageWidget> _backgroundImage;
	std::unique_ptr<TextWidget>  _titleText;
	std::unique_ptr<ButtonWidget> _resumeGameButton;
	std::unique_ptr<TextWidget>   _resumeGameText;
	std::unique_ptr<ButtonWidget> _startNewGameButton;
	std::unique_ptr<TextWidget>   _startNewGameText;
};

}

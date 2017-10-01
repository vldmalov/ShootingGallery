#pragma once

#include "array"

class StretchBox;

namespace UI {
	
enum buttonState : int {
	BS_IDLE,
	BS_PUSHED
};
	
typedef std::function<void(void)> buttonAction;

class ButtonWidget : public GUI::Widget
{
	typedef GUI::Widget baseclass;
public:
	explicit ButtonWidget(const std::string& name);
	ButtonWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void SetTextureName(const std::string& texture_name, buttonState state);
	void SetStripesInfo(float left, float right, float top, float bottom);
	
	void SetAction(buttonAction cb);
	
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;
	
	void Draw() override;

private:
	void Init();
	
private:
	buttonState _currentState;
	std::array<std::shared_ptr<StretchBox>, 2> _stretchBoxes;
	buttonAction _callback;
};
	
}

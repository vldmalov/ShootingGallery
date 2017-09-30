#include "ButtonWidget.h"
#include "GUI/StretchBox.h"

namespace UI {
	
ButtonWidget::ButtonWidget(const std::string& name)
: baseclass(name)
, _currentState(buttonState::IDLE)
, _callback(nullptr)
{
	Init();
	Log::log.WriteDebug("ButtonWidget " + name + " has been constructed");
}
	
ButtonWidget::ButtonWidget(const std::string& name, rapidxml::xml_node<>* elem)
: baseclass(name, elem)
, _currentState(buttonState::IDLE)
, _callback(nullptr)
{
	Init();
	Log::log.WriteDebug("ButtonWidget " + name + " has been constructed");
}
	
void ButtonWidget::Init()
{
	_stretchBoxes[static_cast<int>(buttonState::IDLE)] = std::make_shared<StretchBox>();
	_stretchBoxes[static_cast<int>(buttonState::PUSHED)] = std::make_shared<StretchBox>();
}

void ButtonWidget::SetTextureName(const std::string& texture_name, const buttonState& state)
{
	Render::Texture* texture = Core::resourceManager.Get<Render::Texture>(texture_name);
	if(texture) {
		_stretchBoxes[static_cast<int>(state)]->SetTexture(texture);
	}
	else {
		Log::log.WriteWarn("ButtonWidget::SetTextureName: texture named " + texture_name + " doesn't exist!");
	}
}

	
void ButtonWidget::SetStripesInfo(float left, float right, float top, float bottom)
{
	_stretchBoxes[static_cast<int>(buttonState::IDLE)]->GenHorStripes(left, right);
	_stretchBoxes[static_cast<int>(buttonState::IDLE)]->GenVertStripes(top, bottom);
	
	_stretchBoxes[static_cast<int>(buttonState::PUSHED)]->GenHorStripes(left, right);
	_stretchBoxes[static_cast<int>(buttonState::PUSHED)]->GenVertStripes(top, bottom);
}
	
void ButtonWidget::SetAction(buttonAction cb)
{
	_callback = cb;
}
	
bool ButtonWidget::MouseDown(const IPoint& mouse_pos)
{
	if(getClientRect().Contains(mouse_pos))
	{
		_currentState = buttonState::PUSHED;
		return true;
	}
	
	return false;
}
	
void ButtonWidget::MouseUp(const IPoint& mouse_pos)
{
	if(_currentState == buttonState::PUSHED) {
		_currentState = buttonState::IDLE;
		
		if(getClientRect().Contains(mouse_pos)) {
			if(_callback) {
				_callback();
			}
		}
	}
}

void ButtonWidget::Draw()
{
	if(!isVisible()) {
		return;
	}
	
	baseclass::Draw();
	
	_stretchBoxes[static_cast<int>(_currentState)]->Draw(getClientRect());
}
	
}

#include "ButtonWidget.h"
#include "GUI/StretchBox.h"

namespace UI {
	
ButtonWidget::ButtonWidget(const std::string& name, rapidxml::xml_node<>* elem)
: baseclass(name, elem)
, _texture(nullptr)
, _stretchBox(std::make_shared<StretchBox>())
, _rect()
{
	Log::log.WriteDebug("ButtonWidget " + name + " has been constructed");
}

void ButtonWidget::SetRect(const IRect& rect)
{
	_rect = rect;
}

void ButtonWidget::SetTextureName(const std::string& texture_name)
{
	_texture = Core::resourceManager.Get<Render::Texture>(texture_name);
	
	Render::Texture* texture = Core::resourceManager.Get<Render::Texture>(texture_name);
	if(texture) {
		_stretchBox->SetTexture(texture);
		_stretchBox->GenHorStripes(36, 72);
		_stretchBox->GenVertStripes(128, 16);
	}
	else {
		Log::log.WriteWarn("ButtonWidget::SetTextureName: texture named " + texture_name + " doesn't exist!");
	}
}

void ButtonWidget::Draw()
{
	if(isVisible() && _stretchBox) {
		_stretchBox->Draw(_rect);
		//_texture->Draw();
	}
	
	baseclass::Draw();
}
	
}

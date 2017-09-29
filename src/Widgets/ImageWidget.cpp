#include "ImageWidget.h"
#include "GUI/StretchBox.h"

namespace UI {
	
ImageWidget::ImageWidget(const std::string& name)
: baseclass(name)
, _texture(nullptr)
{
	Log::log.WriteDebug("ImageWidget " + name + " has been constructed");
}
	
ImageWidget::ImageWidget(const std::string& name, rapidxml::xml_node<>* elem)
: baseclass(name, elem)
, _texture(nullptr)
{
	Log::log.WriteDebug("ImageWidget " + name + " has been constructed");
}

void ImageWidget::SetTextureName(const std::string& texture_name)
{
	_texture = Core::resourceManager.Get<Render::Texture>(texture_name);
	
	if(!_texture) {
		Log::log.WriteWarn("ImageWidget::SetTextureName: texture named " + texture_name + " doesn't exist!");
	}
}

void ImageWidget::Draw()
{
	baseclass::Draw();
	
	if(!isVisible()) {
		return;
	}
	
	if(_texture) {
		Render::device.PushMatrix();
		
		const IPoint& position = getPosition();
		Render::device.MatrixTranslate(position.x, position.y, 0.f);
		
		FPoint scale = GetScale();
		Render::device.MatrixScale(scale.x, scale.y, 1.f);
		
		_texture->Draw();
		
		Render::device.PopMatrix();
	}
}

FPoint ImageWidget::GetScale() const
{
	FPoint scale = FPoint(1.f, 1.f);
	
	if(_texture) {
		const IRect& textureRect = _texture->getBitmapRect();
		scale.x = static_cast<float>(getWidth()) / textureRect.Width();
		scale.y = static_cast<float>(getHeight()) / textureRect.Height();
	}
	
	return scale;
}
	
}

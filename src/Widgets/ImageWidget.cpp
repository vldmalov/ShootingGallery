#include "ImageWidget.h"
#include "GUI/StretchBox.h"

ImageWidget::ImageWidget(const std::string& name, rapidxml::xml_node<>* elem)
: baseclass(name, elem)
, _texture(nullptr)
, _outputRect()
, _scale(1.f, 1.f)
{
	std::cout << "ImageWidget " << name << " has been constructed" << std::endl;
}

void ImageWidget::SetOutputRect(const IRect& rect)
{
	_outputRect = rect;
	UpdateScale();
}

void ImageWidget::SetTextureName(const std::string& texture_name)
{
	_texture = Core::resourceManager.Get<Render::Texture>(texture_name);
	UpdateScale();
	
	if(!_texture) {
		std::cout << "ImageWidget::SetTextureName: texture named " << texture_name << " doesn't exist!" << std::endl;
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
		Render::device.MatrixTranslate(_outputRect.x, _outputRect.y, 0.f);
		Render::device.MatrixScale(_scale.x, _scale.y, 1.f);
		
		_texture->Draw();
		
		Render::device.PopMatrix();
	}
}

void ImageWidget::UpdateScale()
{
	_scale = FPoint(1.f, 1.f);
	
	if(!_texture) {
		return;
	}
		
	if(_outputRect != IRect()) {
		const IRect& textureRect = _texture->getBitmapRect();
		_scale.x = static_cast<float>(_outputRect.Width()) / textureRect.Width();
		_scale.y = static_cast<float>(_outputRect.Height()) / textureRect.Height();
	}
}

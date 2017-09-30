#include "TextWidget.h"

namespace UI {
	
const std::string DEFAULT_FONT = "arial";

TextWidget::TextWidget(const std::string& name)
: baseclass(name)
, _font(DEFAULT_FONT)
{

}

TextWidget::TextWidget(const std::string& name, rapidxml::xml_node<>* elem)
: baseclass(name, elem)
, _font(DEFAULT_FONT)
{
}
		
void TextWidget::SetCaption(const std::string& caption)
{
	_caption = caption;
}
	
void TextWidget::SetFont(const std::string& font)
{
	_font = font;
}
		
void TextWidget::Draw()
{
	baseclass::Draw();
	
	if(!isVisible()) {
		return;
	}
	
	Render::BindFont(_font);
	const IRect& widgetRect = getClientRect();
	Render::PrintString(widgetRect.x + widgetRect.Width()  / 2,
						widgetRect.y + widgetRect.Height() / 2,
						_caption, 1.0f, CenterAlign, CenterAlign, true);
}
	

	
}

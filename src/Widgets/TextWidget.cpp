#include "TextWidget.h"

namespace UI {
	

TextWidget::TextWidget(const std::string& name)
: baseclass(name)
{

}

TextWidget::TextWidget(const std::string& name, rapidxml::xml_node<>* elem)
: baseclass(name, elem)
{
}
		
void TextWidget::SetCaption(const std::string& caption)
{
	_caption = caption;
}
		
void TextWidget::Draw()
{
	baseclass::Draw();
	
	if(!isVisible()) {
		return;
	}
	
	Render::BindFont("textWidgetFont");
	const IRect& widgetRect = getClientRect();
	Render::PrintString(widgetRect.x + widgetRect.Width()  / 2,
						widgetRect.y + widgetRect.Height() / 2,
						_caption, 1.0f, CenterAlign, CenterAlign, true);
}
	

	
}

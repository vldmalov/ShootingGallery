#pragma once

namespace UI {
	
class ImageWidget : public GUI::Widget
{
	typedef GUI::Widget baseclass;
public:
	ImageWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void SetOutputRect(const IRect& rect);
	void SetTextureName(const std::string& texture_name);
	
	void Draw() override;
	
private:
	void UpdateScale();
	
private:
	Render::Texture* _texture;
	IRect _outputRect;
	FPoint _scale;
};
	
}

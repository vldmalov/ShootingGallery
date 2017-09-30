#pragma once

namespace UI {
	
class ImageWidget : public GUI::Widget
{
	typedef GUI::Widget baseclass;
public:
	ImageWidget(const std::string& name);
	ImageWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void SetTextureName(const std::string& texture_name);
	
	void Draw() override;
	
private:
	FPoint GetScale() const;
	
private:
	Render::Texture* _texture;
};
	
}

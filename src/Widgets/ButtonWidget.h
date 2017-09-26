#pragma once

class StretchBox;

class ButtonWidget : public GUI::Widget
{
	typedef GUI::Widget baseclass;
public:
	ButtonWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void SetRect(const IRect& rect);
	void SetTextureName(const std::string& texture_name);
	
	void Draw() override;
//	void Update(float dt) override;
//	void AcceptMessage(const Message& message) override;
	
private:
	Render::Texture* _texture;
	std::shared_ptr<StretchBox> _stretchBox;
	IRect _rect;
};

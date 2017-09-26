#pragma once

class Scene;

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
class SceneWidget : public GUI::Widget
{
public:
	SceneWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void setPlaygroundRect(const IRect& rect);

	void Draw() override;
	void Update(float dt) override;
	
	void AcceptMessage(const Message& message) override;
	
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;

private:
	std::shared_ptr<Scene> _scene;
};

#pragma once

namespace Scene {
	class Scene;
}

namespace UI {
	
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
	std::unique_ptr<Scene::Scene> _scene;
};

}

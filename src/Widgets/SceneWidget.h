#pragma once

namespace Scene {
	class Scene;
}

namespace UI {
	
class TopGUI;
class MainMenu;
enum class mainMenuState;
	
class SceneWidget : public GUI::Widget
{
public:
	SceneWidget(const std::string& name, rapidxml::xml_node<>* elem);

	void ResetScene();
	
	void Draw() override;
	void Update(float dt) override;
	
	void AcceptMessage(const Message& message) override;
	
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;
	
private:
	void ShowMenu(const mainMenuState& state);
	void HideMenu();
	
	void OnResumeGame();
	void OnStartNewGame();

private:
	std::unique_ptr<Scene::Scene> _scene;
	std::unique_ptr<TopGUI>		  _topGUI;
	std::unique_ptr<MainMenu>	  _mainMenu;
};

}

#include "SceneWidget.h"

#include "../../Scene/Scene.h"
#include "TopGUI.h"
#include "MainMenu.h"
#include "TimeUtils.h"

namespace UI {
	
SceneWidget::SceneWidget(const std::string& name, rapidxml::xml_node<>* elem)
: Widget(name)
, _scene(new Scene::Scene())
, _topGUI(new TopGUI())
, _mainMenu(new MainMenu())
{
}

void SceneWidget::ResetScene()
{
	_scene->SetRect(getClientRect());
	_scene->Reset();
	_scene->SetOnLevelCompleteCallback(std::bind(&SceneWidget::ShowMenu, this, mainMenuState::COMPLETE_LEVEL));
	_scene->SetOnLevelFailureCallback(std::bind(&SceneWidget::ShowMenu, this, mainMenuState::TIME_IS_OVER));
	
	_topGUI->SetClientRect(getClientRect());
	_topGUI->Reset();
	
	_mainMenu->setClientRect(getClientRect());
	_mainMenu->Reset();
	_mainMenu->SetOnResumeGameCallback(std::bind(&SceneWidget::OnResumeGame, this));
	_mainMenu->SetOnStartNewGameCallback(std::bind(&SceneWidget::OnStartNewGame, this));
	_mainMenu->Hide();
}

void SceneWidget::OnResumeGame()
{
	HideMenu();
}
	
void SceneWidget::OnStartNewGame()
{
	ResetScene();
}
	
	
void SceneWidget::ShowMenu(const mainMenuState& state)
{
	_mainMenu->Show(state);
}
	
void SceneWidget::HideMenu()
{
	_scene->SetPause(false);
	_mainMenu->Hide();
}


void SceneWidget::Draw()
{
	_scene->Draw();
	_topGUI->Draw();
	_mainMenu->Draw();
}

void SceneWidget::Update(float dt)
{
	_scene->Update(dt);
	_topGUI->Update(dt);
	
	_topGUI->SetScore(utils::lexical_cast(_scene->GetScore()));
	
	int secondsToEnd = math::ceil(_scene->GetTimeToEnd());
	_topGUI->SetTimer( Utils::FormatTime(secondsToEnd) );
}

bool SceneWidget::MouseDown(const IPoint &mouse_pos)
{
	if(_mainMenu->MouseDown(mouse_pos)) {
		return true;
	}
	
	return _scene->MouseDown(mouse_pos);
}

void SceneWidget::MouseMove(const IPoint &mouse_pos)
{
	_scene->MouseMove(mouse_pos);
}

void SceneWidget::MouseUp(const IPoint &mouse_pos)
{
	_mainMenu->MouseUp(mouse_pos);
	_scene->MouseUp(mouse_pos);
}

void SceneWidget::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void SceneWidget::KeyPressed(int keyCode)
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//

	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
	}
}

void SceneWidget::CharPressed(int unicodeChar)
{
	//
	// unicodeChar - Unicode код введённого символа
	//

	if (unicodeChar == L'p') {
		
		if(_scene->IsGameActive() && !_scene->GetPause()) {
			_scene->SetPause(true);
			ShowMenu(mainMenuState::PAUSE);
		}
	}
	
	if (unicodeChar == L'r') {
		if(_scene->IsGameActive() && !_scene->GetPause()) {
			_scene->Reset();
		}
	}
}

}

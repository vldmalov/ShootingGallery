#include "SceneWidget.h"

#include "../Scene/Scene.h"

namespace UI {
	
SceneWidget::SceneWidget(const std::string& name, rapidxml::xml_node<>* elem)
: Widget(name)
, _scene(new Scene::Scene())
{
}

void SceneWidget::setPlaygroundRect(const IRect& rect)
{
	_scene->setPlaygroundRect(rect);
}

void SceneWidget::Draw()
{
	_scene->Draw();
}

void SceneWidget::Update(float dt)
{
	_scene->Update(dt);
}

bool SceneWidget::MouseDown(const IPoint &mouse_pos)
{
	return _scene->MouseDown(mouse_pos);
}

void SceneWidget::MouseMove(const IPoint &mouse_pos)
{
	_scene->MouseMove(mouse_pos);
}

void SceneWidget::MouseUp(const IPoint &mouse_pos)
{
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

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}

}

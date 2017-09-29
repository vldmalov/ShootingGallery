#include "TopGUI.h"

namespace UI {

TopGUI::TopGUI(const std::string& name)
: baseclass(name)
, _scoreIcon(new ImageWidget("scoreIcon"))
, _scoreText(new TextWidget("scoreText"))
{
	Log::log.WriteDebug("TopGUI has been constructed");
}
	
TopGUI::TopGUI(const std::string& name, rapidxml::xml_node<>* elem)
: baseclass(name, elem)
, _scoreIcon(new ImageWidget("scoreIcon"))
, _scoreText(new TextWidget("scoreText"))
{
	Log::log.WriteDebug("TopGUI has been constructed");
};
	
void TopGUI::Reset()
{
	IRect topGUIRect = getClientRect();
	
	const IPoint scoreIconSize(60, 60);
	const IPoint scoreIconIndent(12, 12);
	const IPoint scoreTextIndent(14, 13);
	
	_scoreIcon->SetTextureName("Star");
	_scoreIcon->setClientRect(IRect(topGUIRect.x + scoreIconIndent.x ,
									topGUIRect.y + topGUIRect.Height() - scoreIconSize.y - scoreIconIndent.y,
									scoreIconSize.x, scoreIconSize.y));
	
    _scoreText->setClientRect(IRect(topGUIRect.x + scoreTextIndent.x ,
								    topGUIRect.y + topGUIRect.Height() - scoreIconSize.y - scoreTextIndent.y,
								    scoreIconSize.x, scoreIconSize.y));
}
	
void TopGUI::SetScore(const std::string& score)
{
	_scoreText->SetCaption(score);
}

void TopGUI::Draw()
{
	baseclass::Draw();
	
	if(!isVisible()) {
		return;
	}
	
	_scoreIcon->Draw();
	_scoreText->Draw();
}

void TopGUI::Update(float dt)
{
	_scoreIcon->Update(dt);
	_scoreText->Update(dt);
}

void TopGUI::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//
	
	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

}

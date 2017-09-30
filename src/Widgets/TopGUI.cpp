#include "TopGUI.h"

namespace UI {

TopGUI::TopGUI(const std::string& name)
: baseclass(name)
, _scoreIcon(new ImageWidget("scoreIcon"))
, _scoreText(new TextWidget("scoreText"))
, _timerText(new TextWidget("timerText"))
{
	Log::log.WriteDebug("TopGUI has been constructed");
}
	
TopGUI::TopGUI(const std::string& name, rapidxml::xml_node<>* elem)
: baseclass(name, elem)
, _scoreIcon(new ImageWidget("scoreIcon"))
, _scoreText(new TextWidget("scoreText"))
, _timerText(new TextWidget("timerText"))
{
	Log::log.WriteDebug("TopGUI has been constructed");
};
	
void TopGUI::Reset()
{
	IRect topGUIRect = getClientRect();
	
	const IPoint scoreIconSize(60, 60);
	const float  timerWidth = 60;
	const IPoint widgetsIndent(12, 12);
	
	const IRect scoreImageRect(topGUIRect.x + widgetsIndent.x ,
							   topGUIRect.y + topGUIRect.Height() - scoreIconSize.y - widgetsIndent.y,
							   scoreIconSize.x, scoreIconSize.y);
	
	_scoreIcon->SetTextureName("Star");
	_scoreIcon->setClientRect(scoreImageRect);
	
	IPoint scoreTextShift(2, -1);
	
	const IRect scoreTextRect(scoreImageRect.x + scoreTextShift.x, scoreImageRect.y + scoreTextShift.y,
							  scoreImageRect.Width(), scoreImageRect.Height());
	
    _scoreText->setClientRect(scoreTextRect);
	_scoreText->SetFont("topGUIText");
	
	const IRect timerRect(scoreTextRect.x + scoreTextRect.Width() + widgetsIndent.x,
						  scoreTextRect.y, timerWidth, scoreTextRect.Height());
	
	_timerText->setClientRect(timerRect);
	_timerText->SetFont("topGUIText");
}
	
void TopGUI::SetScore(const std::string& score)
{
	_scoreText->SetCaption(score);
}
	
void TopGUI::SetTimer(const std::string& timer)
{
	_timerText->SetCaption(timer);
}

void TopGUI::Draw()
{
	baseclass::Draw();
	
	if(!isVisible()) {
		return;
	}
	
	_scoreIcon->Draw();
	_scoreText->Draw();
	_timerText->Draw();
}

void TopGUI::Update(float dt)
{
	_scoreIcon->Update(dt);
	_scoreText->Update(dt);
	_timerText->Update(dt);
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

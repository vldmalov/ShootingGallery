#include "TopGUI.h"

namespace UI {

TopGUI::TopGUI()
: _clientRect()
, _scoreIcon(new ImageWidget("scoreIcon"))
, _scoreText(new TextWidget("scoreText"))
, _timerText(new TextWidget("timerText"))
, _menuButton(new ButtonWidget("menuButton"))
, _menuText(new TextWidget("menuText"))
{
	Log::log.WriteDebug("TopGUI has been constructed");
}
	
void TopGUI::Reset()
{
	const IPoint scoreIconSize(60, 60);
	const float  timerWidth = 60;
	const IPoint widgetsIndent(12, 12);
	
	const IRect scoreImageRect(_clientRect.x + widgetsIndent.x ,
							   _clientRect.y + _clientRect.Height() - scoreIconSize.y - widgetsIndent.y,
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
	
	const int leftSideIndent(92);
	const int menuButtonWidth(120);
	IRect menuButtonRect(_clientRect.x + _clientRect.Width() - menuButtonWidth - leftSideIndent,
						 timerRect.y + 6, menuButtonWidth, timerRect.Height() - 12);
	
	_menuButton->setClientRect(menuButtonRect);
	_menuButton->SetTextureName("buttonTexture", buttonState::IDLE);
	_menuButton->SetTextureName("buttonActiveTexture", buttonState::PUSHED);
	_menuButton->SetStripesInfo(16, 16, 16, 16);
	
	_menuText->setClientRect(menuButtonRect);
	_menuText->SetFont("topGUIText");
	_menuText->SetCaption("Menu");
}
	
void TopGUI::SetClientRect(const IRect& rect)
{
	_clientRect = rect;
}
	
void TopGUI::SetScore(const std::string& score)
{
	_scoreText->SetCaption(score);
}
	
void TopGUI::SetTimer(const std::string& timer)
{
	_timerText->SetCaption(timer);
}
	
void TopGUI::SetOnMenuButtonCallback(buttonAction cb)
{
	_menuButton->SetAction(cb);
}

void TopGUI::Draw()
{
	_scoreIcon->Draw();
	_scoreText->Draw();
	_timerText->Draw();
	_menuButton->Draw();
	_menuText->Draw();
}

void TopGUI::Update(float dt)
{
	_scoreIcon->Update(dt);
	_scoreText->Update(dt);
	_timerText->Update(dt);
	_menuButton->Update(dt);
	_menuText->Update(dt);
}
	
bool TopGUI::MouseDown(const IPoint &mouse_pos)
{
	if(_menuButton->isVisible())
		return _menuButton->MouseDown(mouse_pos);
	
	return false;
}

void TopGUI::MouseUp(const IPoint &mouse_pos)
{
	if(_menuButton->isVisible())
		_menuButton->MouseUp(mouse_pos);
}

}

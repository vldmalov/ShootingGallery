#include "MainMenu.h"

namespace UI {
	
const std::string MENU_CAPTIONS[] = {
	"Pause",
	"You win!",
	"You lose. Try again!"
};

MainMenu::MainMenu()
: _clientRect()
, _visible(false)
, _backgroundImage(new ImageWidget("menuPanel"))
, _titleText(new TextWidget("titleText"))
, _resumeGameButton(new ButtonWidget("resumeButton"))
, _resumeGameText(new TextWidget("resumeGame"))
, _startNewGameButton(new ButtonWidget("newGame"))
, _startNewGameText(new TextWidget("startNewGame"))
{
	Log::log.WriteDebug("MainMenu has been constructed");
}
	
void MainMenu::Reset()
{
	IPoint menuPanelSize(600, 320);
	
	const IRect menuPanelRect (_clientRect.x + (_clientRect.Width()  - menuPanelSize.x) / 2.f,
							   _clientRect.y + (_clientRect.Height() - menuPanelSize.y) / 2.f,
							   menuPanelSize.x, menuPanelSize.y);
	
	const float titleTopIndent(40.f);
	const float titleHeight(60.f);
	const IRect titleRect(menuPanelRect.x,
						  menuPanelRect.y + menuPanelRect.Height() - (titleTopIndent + titleHeight),
						  menuPanelRect.Width(), titleHeight);
	
	const float resumeBtnTopIndent(140.f);
	const IPoint buttonSize(320, 64);
	const IRect resumeBtnRect(menuPanelRect.x + (menuPanelRect.Width()  - buttonSize.x) / 2.f,
							  menuPanelRect.y + menuPanelRect.Height() - (resumeBtnTopIndent + buttonSize.y),
							  buttonSize.x, buttonSize.y);
	
	const int BUTTON_INDENT = 20;
	const IRect restartBtnRect(resumeBtnRect.x, resumeBtnRect.y - resumeBtnRect.Height() - BUTTON_INDENT,
							   resumeBtnRect.Width(), resumeBtnRect.Height());
	
	_backgroundImage->SetTextureName("menuPanel");
	_backgroundImage->setClientRect(menuPanelRect);
	
	_titleText->SetCaption("Main Menu");
	_titleText->SetFont("mainMenuCaption");
	_titleText->setClientRect(titleRect);
	
	_resumeGameButton->setClientRect(resumeBtnRect);
	_resumeGameButton->SetTextureName("buttonTexture", buttonState::IDLE);
	_resumeGameButton->SetTextureName("buttonActiveTexture", buttonState::PUSHED);
	_resumeGameButton->SetStripesInfo(16, 16, 16, 16);
	
	_resumeGameText->SetCaption("Resume game");
	_resumeGameText->SetFont("mainMenuButtonText");
	_resumeGameText->setClientRect(resumeBtnRect);
	
	_startNewGameButton->setClientRect(restartBtnRect);
	_startNewGameButton->SetTextureName("buttonTexture", buttonState::IDLE);
	_startNewGameButton->SetTextureName("buttonActiveTexture", buttonState::PUSHED);
	_startNewGameButton->SetStripesInfo(16, 16, 16, 16);
	
	_startNewGameText->SetCaption("Start new game");
	_startNewGameText->SetFont("mainMenuButtonText");
	_startNewGameText->setClientRect(restartBtnRect);
}
	
void MainMenu::setClientRect(const IRect& rect)
{
	_clientRect = rect;
}
	
void MainMenu::Show(const mainMenuState& state)
{
	_resumeGameButton->setVisible(state == mainMenuState::PAUSE);
	_resumeGameText->setVisible(state == mainMenuState::PAUSE);
	
	_titleText->SetCaption(MENU_CAPTIONS[static_cast<int>(state)]);

	_visible = true;
}
	
void MainMenu::Hide()
{
	_visible = false;
}
	
void MainMenu::SetOnResumeGameCallback(buttonAction cb)
{
	_resumeGameButton->SetAction(cb);
}
	
void MainMenu::SetOnStartNewGameCallback(buttonAction cb)
{
	_startNewGameButton->SetAction(cb);
}

void MainMenu::Draw()
{
	if(!_visible) {
		return;
	}
	
	_backgroundImage->Draw();
	_titleText->Draw();
	_resumeGameButton->Draw();
	_resumeGameText->Draw();
	_startNewGameButton->Draw();
	_startNewGameText->Draw();
}
	
bool MainMenu::MouseDown(const IPoint &mouse_pos)
{
	if(!_visible) {
		return false;
	}
	
	if(_resumeGameButton->isVisible())
		_resumeGameButton->MouseDown(mouse_pos);
	
	if(_startNewGameButton->isVisible())
		_startNewGameButton->MouseDown(mouse_pos);
	
	return true;
}

void MainMenu::MouseUp(const IPoint &mouse_pos)
{
	if(!_visible) {
		return;
	}
	
	if(_resumeGameButton->isVisible())
		_resumeGameButton->MouseUp(mouse_pos);
	
	if(_startNewGameButton->isVisible())
		_startNewGameButton->MouseUp(mouse_pos);
}

}

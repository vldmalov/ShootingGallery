#include "stdafx.h"
#include "TestAppDelegate.h"
#include "SceneWidget.h"
#include "ImageWidget.h"
#include "TextWidget.h"

enum {
	WINDOW_WIDTH = 1024,
	WINDOW_HEIGHT = 768
};

TestAppDelegate::TestAppDelegate()
{
}

void TestAppDelegate::GameContentSize(int deviceWidth, int deviceHeight, int &width, int &height)
{
	//
	// Здесь задаётся размер игрового экрана в логических единицах.
	//
	// Это значит, что и в оконном, и в полноэкранном режиме размер экрана
	// всегда будет равен WINDOW_WIDTH x WINDOW_HEIGHT "пикселей".
	//
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
}

void TestAppDelegate::ScreenMode(DeviceMode &mode)
{
	mode = DeviceMode::Windowed;
}

void TestAppDelegate::RegisterTypes()
{
	//
	// Чтобы можно было декларативно использовать виджет в xml по имени,
	// его необходимо зарегистрировать таким образом.
	//
	
	REGISTER_WIDGET_XML(UI::ImageWidget, "ImageWidget");
	REGISTER_WIDGET_XML(UI::TextWidget,  "TextWidget");
	REGISTER_WIDGET_XML(UI::SceneWidget, "SceneWidget");
}

void TestAppDelegate::LoadResources()
{
	//
	// Обычно в этом методе выполняется скрипт, в котором определяется,
	// какие ресурсы нужно загрузить и какой игровой слой положить на экран.
	//
	Core::LuaExecuteStartupScript("start.lua");
	
	// Нужно разобраться как пропертя виджетов зарегистрировать
	// для их выставления через Layers.xml
	IRect ScreenRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	Layer* bgLayer = Core::guiManager.getLayer("BackgroundLayer");
	if(bgLayer) {
		UI::ImageWidget* bgImageWidget = dynamic_cast<UI::ImageWidget*>(bgLayer->getWidget("BackgroundWidget"));
		if(bgImageWidget) {
			bgImageWidget->SetTextureName("background");
			bgImageWidget->setClientRect(ScreenRect);
		}
	}
	
	Layer* sceneLayer = Core::guiManager.getLayer("MainSceneLayer");
	if(sceneLayer) {
		UI::SceneWidget* sceneWidget = dynamic_cast<UI::SceneWidget*>(sceneLayer->getWidget("SceneWidget"));
		if(sceneWidget) {
			sceneWidget->setClientRect(ScreenRect);
			sceneWidget->ResetScene();
		}
	}
}

void TestAppDelegate::OnResourceLoaded() {
	if (Core::appInstance->AllResourcesLoaded()) {
		Core::appInstance->SetLoaded();
	}
}

void TestAppDelegate::OnPostDraw() {
	if (!Render::isFontLoaded("arial"))
		return;

	//
	// Перед вызовом метода Render::PrintString() нужно привязать нужный шрифт
	//
	Render::BindFont("arial");

	int dy = Render::getFontHeight();
	int x = Render::device.Width() - 5;
	int y = Render::device.Height() - 20;

	Render::PrintString(x, y, std::string("FPS: ") + utils::lexical_cast(Core::appInstance->GetCurrentFps()), 1.0f, RightAlign, BottomAlign);
	Render::PrintString(x, y -= dy, std::string("Video: ") + utils::lexical_cast(Render::device.GetVideoMemUsage() / WINDOW_WIDTH) + std::string("K"), 1.0f, RightAlign, BottomAlign);
	Render::PrintString(x, y -= dy, std::string("Audio: ") + utils::lexical_cast(Core::resourceManager.GetMemoryInUse<MM::AudioResource>() / WINDOW_WIDTH) + std::string("K"), 1.0f, RightAlign, BottomAlign);
	Render::PrintString(x, y -= dy, std::string("Animations: ") + utils::lexical_cast((Core::resourceManager.GetMemoryInUse<Render::StreamingAnimation>() + Core::resourceManager.GetMemoryInUse<Render::Animation>()) / WINDOW_WIDTH) + std::string("K"), 1.0f, RightAlign, BottomAlign);
	Render::PrintString(x, y -= dy, std::string("Textures: ") + utils::lexical_cast(Core::resourceManager.GetMemoryInUse<Render::Texture>() / WINDOW_WIDTH) + std::string("K"), 1.0f, RightAlign, BottomAlign);
	Render::PrintString(x, y -= dy, std::string("Particles: ") + utils::lexical_cast(Core::resourceManager.GetMemoryInUse<ParticleEffect>() / WINDOW_WIDTH) + std::string("K"), 1.0f, RightAlign, BottomAlign);
	Render::PrintString(x, y -= dy, std::string("Models: ") + utils::lexical_cast(Core::resourceManager.GetMemoryInUse<Render::ModelAnimation>() / WINDOW_WIDTH) + std::string("K"), 1.0f, RightAlign, BottomAlign);
}

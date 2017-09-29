#pragma once

namespace UI {
	
	class TextWidget : public GUI::Widget
	{
		typedef GUI::Widget baseclass;
	public:
		TextWidget(const std::string& name);
		TextWidget(const std::string& name, rapidxml::xml_node<>* elem);
		
		void SetCaption(const std::string& caption);
		
		void Draw() override;

	private:
		std::string _caption;
	};
	
}

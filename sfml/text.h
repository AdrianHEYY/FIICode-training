#pragma once
#include <string>
#include <SFML/Graphics.hpp>
namespace util
{
	class Text
	{
	public:
		Text(std::string txt);
		inline std::string getText() { return text.getString(); };
		inline void setText(std::string txt) { text.setString(txt); };
		void draw();
		//void update();
	private:
		sf::Text text;
		sf::Font font;
	};
}
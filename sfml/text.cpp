#include "text.h"
#include "window.h"
namespace util
{
	Text::Text(std::string txt)
	{
		font.loadFromFile("fonts/arial.ttf");
		text.setString(txt);
		text.setPosition(sf::Vector2f(0.0f, 0.0f));
	}
	void Text::draw()
	{
		win.draw(text);
	}

}
#include "health_bar.h"
#include "window.h"

namespace util {
	Health_Bar::Health_Bar(sf::RectangleShape* target, float max_health, float starting_health) 
		:max_health(max_health), current_health(starting_health), target(target)
	{
		max_health_sprite.setFillColor(sf::Color::Red);
		current_health_sprite.setFillColor(sf::Color::Green);

		max_health_sprite.setSize(base_size);
		subtractHealth(max_health - starting_health);
		
	}
	void Health_Bar::updatePosition() {
		sf::Vector2f position= target->getPosition() + sf::Vector2f(0.0f, target->getSize().y);
		position.x += (target->getSize().x/2.0f);
		position.x -= (max_health_sprite.getSize().x / 2.0f);

		max_health_sprite.setPosition(position);
		current_health_sprite.setPosition(position);
	}
	void Health_Bar::subtractHealth(float ammount)
	{
		current_health-=ammount;
		if (current_health < 0)
			current_health = 0;
		current_health_sprite.setSize(sf::Vector2f((base_size.x*current_health)/max_health,base_size.y));
	}
	void Health_Bar::draw() {
		win.draw(max_health_sprite);
		win.draw(current_health_sprite);
	}
}
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace util {
	class Health_Bar
	{
	public:
		Health_Bar(sf::RectangleShape* target, float max_health, float starting_health);
		
		inline float getHealth() { return current_health; };
		void setHealth(float health);
		void subtractHealth(float ammount) ;
		
		void updatePosition();
		void draw();

	private:
		sf::RectangleShape* target;

		float max_health;
		float current_health;

		/// <summary>
		/// ! NEUTILIZAT, INITIALIZEAZA-L !
		/// </summary>
		sf::RectangleShape over_health;
		sf::RectangleShape current_health_sprite;
		sf::RectangleShape max_health_sprite;

		const sf::Vector2f base_size = sf::Vector2f(50.0f, 10.0f);
	};
};
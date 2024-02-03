#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace util {
	bool collision(const sf::Vector2f& pos_1, const sf::Vector2f& size_1, const sf::Vector2f& pos_2, const sf::Vector2f& size_2);
}
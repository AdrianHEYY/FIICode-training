#pragma once

#include <SFML/Graphics.hpp>

#include <chrono>

class Player_Animation {
public:
	Player_Animation(sf::RectangleShape& sprite);
	void update(sf::Vector2f velocity, sf::RectangleShape& sprite);
private:
	std::string last_direction = "-D";
	unsigned int no_frames;
	unsigned int current_frame;
	long long milliseconds_frame = 140;

	std::chrono::high_resolution_clock::time_point time_since_start;

	unsigned int width, height, unit_width;

	sf::Texture up, down, left, right;
	sf::Texture down_left, down_right, up_left, up_right;

	sf::Texture* current_texture = nullptr;
};
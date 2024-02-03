#pragma once

#include <SFML/Graphics.hpp>
extern class Game;

class Weapon {
public:
	Weapon();
	virtual void draw();
	virtual void update();
	virtual void onClick();
	inline long long getTimeBetweenHits() { return time_between_hits; };
    inline float getDamage() { return damage; };
protected:
	Game* game;
	
	float damage;
	float area;

	long long time_between_hits;
	sf::Texture texture;
	sf::RectangleShape sprite;
};
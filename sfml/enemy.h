#pragma once

#include <SFML/Graphics.hpp>

extern class Game;

class Enemy{
public:
	Enemy(Game* game);
	void draw();
	void update();
	inline float get_health()  { return health; };
	inline float get_dmg() { return damage; };
	inline sf::Vector2f get_pos() { return enemy.getPosition(); };
	void subtract_health();
private:
	Game* game;
	int health;
	int damage;
	float move_speed;
	sf::RectangleShape enemy;
	sf::Texture texture;
	
};
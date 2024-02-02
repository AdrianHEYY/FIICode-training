#pragma once

#include "health_bar.h"
#include "window.h"
#include "dvd_logo.h"

extern class Game;

class Player {
public:
	Player(Game* game);
	void draw();
	void update();
	inline sf::Vector2f getPlayerPos() { return player.getPosition(); };
	inline sf::Vector2f getPlayerSize() { return player.getSize(); };
	void subtractHealth(float damage);
private:
	Game* game;

	util::Health_Bar hb;

	Dvd_Logo dl;

	sf::RectangleShape player;
	sf::Texture texture;
	sf::Vector2f velocity;
	float move_speed;
};
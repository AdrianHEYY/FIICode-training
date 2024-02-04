#pragma once

#include "health_bar.h"
#include "window.h"
#include "dvd_logo.h"

#include "player_animation.h"

#include<vector>

extern class Game;

class Player {
public:
	Player(Game* game);
	void draw();
	void update();
	void subtractHealth(float damage);
	void destroyWeapon();

	inline sf::Vector2f getPos() { return player.getPosition(); };
	inline sf::Vector2f getSize() { return player.getSize(); };
private:
	Game* game;

	util::Health_Bar hb;

	Weapon* weapon = nullptr;

	sf::RectangleShape player;
	sf::Texture texture;
	sf::Vector2f velocity;
	float move_speed;

	Player_Animation animation;
};
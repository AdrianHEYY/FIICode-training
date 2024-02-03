#pragma once

#include "enemy.h"
#include "player.h"

class Game { 
public:
	Game();
	void run_one();
	sf::Vector2f getPlayerPos();
	sf::Vector2f getPlayerSize();
	inline std::vector<std::unique_ptr<Enemy>>& getEnemies() { return enemies; };
	void hitPlayer(float damage);
	void destroyedWeapon(Weapon* weapon);
private:
	Player player;
	std::vector<std::unique_ptr<Enemy>> enemies;
};
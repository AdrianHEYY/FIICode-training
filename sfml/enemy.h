#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

extern class Game;
extern class Weapon;
enum enemy_types
{
	NON_BOSS,
	BOSS
};
enum enemy_archetype
{
	MELEE,
	RANGE,
	MAGE,
	SUPPORT
};

class Enemy{
public:
	Enemy(Game* game);
	~Enemy();
	
	void draw();
	void update();
	
	inline float get_health()  { return health; };
	inline float get_dmg() { return damage; };
    inline sf::Vector2f getPos() { return enemy.getPosition(); };
    inline sf::Vector2f getSize() { return enemy.getSize(); };
	inline bool isAlive() { return alive; };
	
	
	void takeDamage(Weapon* weapon);
	void weaponDestroyed(Weapon* weapon);

	

private:
	Game* game;
	bool alive = 1;
	float health;
	float damage;
	float move_speed;
	sf::RectangleShape enemy;
	enemy_types types;
	sf::Texture texture;

	std::map<Weapon*, std::chrono::high_resolution_clock::time_point> immune_to_weapon;
};
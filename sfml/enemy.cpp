#include "enemy.h"
#include "window.h"
#include "game.h"
#include "util.h"
#include "timer.h"

#include <random>
Enemy::Enemy(Game * game) 
	:game(game), move_speed(1.0f)
{
	health = rand() % 101;
	damage = rand() % 6;

	texture.loadFromFile("samples/enemy_texture.png");
	enemy.setTexture(&texture);

	enemy.setSize(sf::Vector2f(50.0f, 100.0f));
	enemy.setPosition(sf::Vector2f(rand() % win.getSize().x, rand() % win.getSize().y));
}

void Enemy::draw()
{
	win.draw(enemy);
}

void Enemy::update()
{
	sf::Vector2f player_pos = game->getPlayerPos();
	sf::Vector2f player_size = game->getPlayerSize();
	
	sf::Vector2f this_pos = enemy.getPosition();
	sf::Vector2f this_size = enemy.getSize();

	float ratio = 0.2f;
	float dist = 10.0f;
	
	double distance = sqrt(pow(this_pos.x - player_pos.x, 2) + pow(this_pos.y - player_pos.y, 2));
	double distX = player_pos.x - this_pos.x;
	double distY = player_pos.y - this_pos.y;
	double unghi = acos(distX / distance);

	const float PI = 3.1415926535;
	if (this_pos.y > player_pos.y) { 
		unghi = 2 * PI - unghi;
	}
	
	sf::Vector2f unitate = sf::Vector2f(cos(unghi), sin(unghi));
	unitate *= 5.0f * move_speed * delta_time;

	if(util::collision(this_pos, this_size, player_pos, player_size))
	{
		static util::Timer last_time_dealt_damage(1);

		unitate = -unitate;
		
		if (last_time_dealt_damage.getElapsed() >= 100) {
			game->hitPlayer(damage);
		}

	}

	sf::Vector2f new_pos = sf::Vector2f(enemy.getPosition().x + unitate.x, enemy.getPosition().y + unitate.y);

	enemy.setPosition(new_pos); 


}
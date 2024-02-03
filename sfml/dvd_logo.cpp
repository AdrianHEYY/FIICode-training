#include <iostream>
#include <math.h>
#include <random>

#include "dvd_logo.h"
#include "player.h"
#include "window.h"
#include "util.h"

#include "player.h"
#include "game.h"

Dvd_Logo::Dvd_Logo(Game* game, Player* owner, sf::Vector2f original_position)
	:timer(util::Timer(true)), owner(owner), game(game)
{
	damage = 10.0f;
	time_between_hits = 450;
	sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(win));
	
	float distance = sqrt(pow(mouse_pos.x - original_position.x, 2) + pow(mouse_pos.y - original_position.y, 2));
	float disX= (mouse_pos.x - original_position.x);
	if (distance == 0) distance = 1;
	float angle = acos(disX / distance);

	const float PI = 3.1415926535;
	if (mouse_pos.y > original_position.y) {
		angle = 2 * PI - angle;
	}

	velocity = sf::Vector2f(cos(angle), -sin(angle)) * 3.0f;
	std::cout << angle * 180 / PI << '\n';

	texture.loadFromFile("samples/dvd_logo.png");
	sprite.setTexture(&texture);
	sprite.setSize({ 100.0f, 50.0f });
	sprite.setPosition(original_position - sprite.getSize() / 2.0f);

	shader = new sf::Shader();
	shader->loadFromFile("shader.vert", "shader.frag");
	shader->setUniform("texture", texture);
}

void Dvd_Logo::draw() {
	win.draw(sprite, shader);
}

void Dvd_Logo::update() {
	shader->setUniform("time", int(timer.getElapsed()/10));
    
	sf::Vector2f position = sprite.getPosition();
	sf::Vector2f size = sprite.getSize();


	if ((velocity.x < 0 &&position.x - velocity.x < 0) || (velocity.x > 0 && position.x + size.x + velocity.x > win.getSize().x)) {
		velocity.x = -velocity.x;
		bounces_left--;
		if (bounces_left <= 0) {
			owner->destroyWeapon();
			return;
		}
	}
	if ((velocity.y<0&&position.y - velocity.y < 0)|| (velocity.y>0&&position.y + size.y + velocity.y > win.getSize().y)) {
		velocity.y = -velocity.y;
		bounces_left--;
		if (bounces_left <= 0) {
			owner->destroyWeapon();
			return;
		}
	}

	sprite.setPosition(sprite.getPosition() + velocity * projectile_speed);
	
	std::vector<std::unique_ptr<Enemy>> &enemies = game->getEnemies();
	for (int j = 0; j < enemies.size(); j++) {
		auto i = enemies[j].get();

		sf::Vector2f position = i->getPos();
		if (util::collision(i->getPos(), i->getSize(), sprite.getPosition(), sprite.getSize()) == 1) {
			i->takeDamage(this);
			if (i->isAlive() == 0) {
				enemies.erase(enemies.begin() + j);
			}
		}
	}
}

Dvd_Logo::~Dvd_Logo() {
	std::cout << "DVD DISTRUS\n";
	delete shader;
}
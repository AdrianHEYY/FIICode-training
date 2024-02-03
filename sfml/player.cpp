#include <SFML/Graphics.hpp>
#include <math.h>
#include "player.h"
#include "game.h"
#include "window.h"
#include <iostream>

Player::Player(Game* game)
	: game(game), move_speed(1.0f), hb(&player, 100.0f, 100.0f)
{
	texture.loadFromFile("samples/player_texture.png");
	sf::Vector2f middle = sf::Vector2f(win.getSize());
	player.setSize(sf::Vector2f(50.0f, 100.0f));
	middle.x -= player.getSize().x;
	middle.y -= player.getSize().y;
	middle.x /= 2;
	middle.y /= 2;
	player.setPosition(middle);
	player.setTexture(&texture);
	velocity = sf::Vector2f(0.0f, 0.0f);
}

void Player::draw() {
	if (weapon != nullptr)
		weapon->draw();
	win.draw(player);
	hb.draw();
}

void Player::subtractHealth(float damage) {
	hb.subtractHealth(damage);
}

void Player::update() {
	if (weapon != nullptr) {	
		weapon->update();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && weapon == nullptr) {
		weapon = new Dvd_Logo(game, this, player.getPosition() + player.getSize() / 2.0f);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y--;
		if (velocity.y < -3)
			velocity.y = -3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y++;
		if (velocity.y > 3)
			velocity.y = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x--;
		if (velocity.x < -3)
			velocity.x = -3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x++;
		if (velocity.x > 3)
			velocity.x = 3;
	}
	//sf::Vector2f normalization=velocity;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && velocity.x != 0)
	{
		velocity.x < 0 ? velocity.x++ : velocity.x--;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && velocity.y != 0)
	{
		velocity.y < 0 ? velocity.y++ : velocity.y--;
	}

	sf::Vector2f normalized = velocity;
	float length =sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	normalized.x /= (length + (length == 0));
	normalized.y /= (length + (length == 0));
	normalized.x *= 3;
	normalized.y *= 3;
	player.setPosition(player.getPosition() + normalized * move_speed * delta_time);


	hb.updatePosition();
}

void Player::destroyWeapon()
{
	game->destroyedWeapon(weapon);
	if (weapon != nullptr)
		delete weapon;
	weapon = nullptr;
}
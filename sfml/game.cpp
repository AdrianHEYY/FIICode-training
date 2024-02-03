#include "game.h"

#include "window.h"

Game::Game()
	:player(Player(this))
{
	enemies.push_back(std::make_unique<Enemy>(this)); 
}

void Game::run_one() {
	player.update();

	for (auto &i : enemies) {
		i->update();
		i->draw();
	}

	player.draw();
}

void Game::destroyedWeapon(Weapon* weapon) {
	for (auto &i : enemies) {
		i->weaponDestroyed(weapon);
	}
}

void Game::hitPlayer(float damage) {
	player.subtractHealth(damage);
}

sf::Vector2f Game::getPlayerPos() {
	return player.getPos();
}
sf::Vector2f Game::getPlayerSize() {
	return player.getSize();
}
#include <SFML/Graphics.hpp>

extern class Game;
class Weapon {
public:
	Weapon();
	virtual void draw();
	virtual void update();
	virtual void onClick();
protected:
	Game* game;
	
	float damage;
	float area;

	sf::Texture texture;
	sf::RectangleShape sprite;
};
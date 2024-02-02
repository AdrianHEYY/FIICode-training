#include <SFML/Graphics.hpp>

class Weapon {
public:
	Weapon();
	virtual void draw();
	virtual void update();
	virtual void onClick();
protected:
	float damage;
	sf::Texture texture;
	sf::RectangleShape sprite;
};
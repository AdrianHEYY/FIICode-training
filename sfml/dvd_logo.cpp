#include "dvd_logo.h"
#include "window.h"
#include <random>
#include <math.h>
#include <iostream>
#include "player.h"

Dvd_Logo::Dvd_Logo(Player* owner,sf::Vector2f original_position)
	:timer(util::Timer(true)), owner(owner)
{

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

	std::string vertex =
		"" \
		"	void main()" \
		"	{" \
		"		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; " \
		"		gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;" \
		"		gl_FrontColor = gl_Color; " \
		"	}";
	std::string fragment =
		"	uniform sampler2D texture;" \
		"	uniform int time;" \
		"	void main()" \
		"	{" \
		"		vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
		"		if (pixel.a != 0.0) {" \
		"			 int a = time - (time / 255) * 255;" \
		"			 float normalizedA = float(a) / 255.0;" \
		"			 int parte = time / 255;" \
		"			 parte = parte - (parte / 3) * 3;" \
		"			 if (parte == 0) {" \
		"				pixel = vec4(1.0 - normalizedA, normalizedA, 0.0, 1.0);" \
		"			 }" \
		"			 else if (parte == 1) {" \
		"				pixel = vec4(0.0, 1.0 - normalizedA, normalizedA, 1.0);" \
		"			 }" \
		"			 else if (parte == 2) {" \
		"				pixel = vec4(normalizedA, 0.0, 1.0 - normalizedA, 1.0);" \
		"			 }" \
		"		}" \
		"		gl_FragColor = pixel;" \
		"	};";
	shader = new sf::Shader();
	shader->loadFromMemory(vertex, fragment);
	shader->setUniform("texture", texture);
}

void Dvd_Logo::draw() {
	win.draw(sprite, shader);
}

void Dvd_Logo::update() {
	shader->setUniform("time", int(timer.getElapsed()/10));
    
	if (bounces_left <= 0) owner->destroyWeapon();
	
	sf::Vector2f position = sprite.getPosition();
	sf::Vector2f size = sprite.getSize();


	if ((velocity.x < 0 &&position.x - velocity.x < 0) || (velocity.x > 0 && position.x + size.x + velocity.x > win.getSize().x)) {
		velocity.x = -velocity.x;
		bounces_left--;
	}
	if ((velocity.y<0&&position.y - velocity.y < 0)|| (velocity.y>0&&position.y + size.y + velocity.y > win.getSize().y)) {
		velocity.y = -velocity.y;
		bounces_left--;
	}


	sprite.setPosition(sprite.getPosition() + velocity * projectile_speed);
}

Dvd_Logo::~Dvd_Logo() {
	delete shader;
}